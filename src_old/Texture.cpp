#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Activate(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}