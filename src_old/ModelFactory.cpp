#include "ModelFactory.h"

Model* ModelFactory::Create(unsigned int id, const std::string& filePath)
{
	Model* model = new Model(id, filePath);

	if (filePath == "")
		return model;
	return model;
}
