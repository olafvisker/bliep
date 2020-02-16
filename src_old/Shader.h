#pragma once
#include <GL/glew.h>
#include <string>

#include "Asset.h"

class Shader : public Asset
{
	friend class ShaderFactory;
public:
	~Shader();

	GLuint GetProgram() { return m_program; }

	std::string GetName() { return m_name; }
	void SetName(const std::string& name) { m_name = name; }

	GLuint GetUniform(const std::string& name);

	void Bind();
	void Unbind();

private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

	std::string m_name;

	Shader(unsigned int id, const std::string& filePath) : Asset(id, filePath), m_name(filePath) { }
};
