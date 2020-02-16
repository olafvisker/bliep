#include "MaterialFactory.h"

Material* MaterialFactory::Create(unsigned int id, const std::string& filePath)
{
	Material* material = new Material(id, filePath);

	if (filePath == "")
		return material;
	return material;
}
