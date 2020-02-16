#include <string>

#include "Texture.h"
#include "Factory.h"

class TextureFactory : public Factory
{
public:
	TextureFactory::TextureFactory(ResourceManager* resourceManager) : Factory(resourceManager) { }
	~TextureFactory() { }

	Texture* Create(unsigned int id, const std::string& filePath);
};