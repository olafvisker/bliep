#include <SOIL/SOIL.h>

#include "TextureFactory.h"
#include "Logger.h"

Texture* TextureFactory::Create(unsigned int id, const std::string& filePath)
{
	Texture* texture = new Texture(id, filePath);
	unsigned char* img = SOIL_load_image(filePath.c_str(), &texture->m_width, &texture->m_height, 
										&texture->m_channels, SOIL_LOAD_RGBA);

	if (img == NULL)
	{
		Logger::Log(LogLevel::LOG_ERROR, "Failed to load texture '%s' : '%s'.", filePath.c_str(), SOIL_last_result());
		return nullptr;
	}

	glGenTextures(1, &texture->m_texture);
	glBindTexture(GL_TEXTURE_2D, texture->m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->m_width, texture->m_height, GL_FALSE, GL_RGBA, GL_UNSIGNED_BYTE, img);

	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);

	Logger::Log(LogLevel::LOG_INFO, "Texture '%s' was loaded.", filePath.c_str());
	return texture;
}