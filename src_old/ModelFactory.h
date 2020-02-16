#pragma once
#include <string>

#include "Model.h"
#include "Factory.h"

class ModelFactory : public Factory
{
public:
	ModelFactory(ResourceManager* resourceManager) : Factory(resourceManager) { }
	~ModelFactory() { }

	Model* Create(unsigned int id, const std::string& filePath);
};

