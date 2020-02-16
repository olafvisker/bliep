#pragma once
#include <GL/glew.h>
#include <string>

#include "Shader.h"
#include "Factory.h"

class ShaderFactory : public Factory
{
public:
	ShaderFactory(ResourceManager* resourceManager) : Factory(resourceManager) { }
	~ShaderFactory() { }

	Shader* Create(unsigned int id, const std::string& filePath);

private:
	std::string LoadShaderSource(const std::string& fileName);
	GLuint CreateShaderProgram(const std::string& text, unsigned int type);
	bool ShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
};

