#pragma once
#include <GL/glew.h>
#include <string>

#include "Asset.h"

enum TextureType
{
	TEX_NONE,
	TEX_DIFFUSE,
	TEX_SPECULAR,
};

class Texture : public Asset
{
	friend class TextureFactory;
public:
	~Texture();

	TextureType GetType()	{ return m_type; }
	int GetWidth()			{ return m_width; }
	int GetHeight()			{ return m_height; }
	int GetChannels()		{ return m_channels; }

	void SetType(TextureType type)	{ m_type = type; }

	void Activate(unsigned int unit);
	void Texture::Bind();

private:
	GLuint m_texture;

	TextureType m_type = TextureType::TEX_NONE;
	int m_width		= -1;
	int m_height	= -1;
	int m_channels	= -1;

	Texture(unsigned int id, const std::string& path) : Asset(id, path) { }
};

