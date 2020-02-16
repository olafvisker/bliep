#include "Shader.h"
#include "Logger.h"

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

GLuint Shader::GetUniform(const std::string& name)
{
	GLuint uni = glGetUniformLocation(m_program, name.c_str());
	if (uni == -1)
		Logger::Log(LogLevel::LOG_WARNING, "Shader '%s' does not contain uniform '%s'.", m_name.c_str(), name.c_str());
	return uni;
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Unbind()
{
	glUseProgram(0);
}
