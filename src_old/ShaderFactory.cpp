#include <fstream>

#include "ShaderFactory.h"
#include "Logger.h"

Shader* ShaderFactory::Create(unsigned int id, const std::string& filePath)
{
	Shader* shader = new Shader(id, filePath);
	shader->m_program = glCreateProgram();
	shader->m_shaders[0] = CreateShaderProgram(LoadShaderSource(filePath + ".vs"), GL_VERTEX_SHADER);
	shader->m_shaders[1] = CreateShaderProgram(LoadShaderSource(filePath + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < shader->NUM_SHADERS; i++)
		glAttachShader(shader->m_program, shader->m_shaders[i]);

	glLinkProgram(shader->m_program);
	bool success = ShaderError(shader->m_program, GL_LINK_STATUS, true, "Error linking shader program");

	if (success)
	{
		glValidateProgram(shader->m_program);
		success = ShaderError(shader->m_program, GL_LINK_STATUS, true, "Invalid shader program");
	}
	else
		return nullptr;

	if (success)
		Logger::Log(LogLevel::LOG_INFO, "Shader '%s' was loaded.", filePath.c_str());
	else
		return nullptr;

	return shader;
}

std::string ShaderFactory::LoadShaderSource(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
		Logger::Log(LogLevel::LOG_ERROR, "Failed to load shader: %s.", fileName.c_str());

	return output;
}

GLuint ShaderFactory::CreateShaderProgram(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		Logger::Log(LogLevel::LOG_ERROR, "Failed to compile shader of type '%i'.", type);

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);
	ShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader");

	return shader;
}

bool ShaderFactory::ShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		Logger::Log(LogLevel::LOG_ERROR, "%s : '%s'.", errorMessage.c_str(), error);
		return false;
	}

	return true;
}