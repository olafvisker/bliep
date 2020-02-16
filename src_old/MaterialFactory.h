#pragma once
#include <string>

#include "Material.h"
#include "Factory.h"

class MaterialFactory : public Factory
{
public:
	MaterialFactory::MaterialFactory(ResourceManager* resourceManager) : Factory(resourceManager) { }
	~MaterialFactory() { }

	Material* Create(unsigned int id, const std::string& filePath);
};

