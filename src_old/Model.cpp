#include "Model.h"
#include "Texture.h"

Model::~Model()
{
	for (auto& i : m_meshes)
		delete i;
}