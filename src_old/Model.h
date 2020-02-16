#pragma once
#include <vector>

#include "Mesh.h"
#include "Material.h"
#include "Asset.h"

class Model : public Asset
{
	friend class ModelFactory;
public:
	~Model();

	void AddMesh(Mesh* mesh) { m_meshes.push_back(mesh); }
	std::vector<Mesh*>& Meshes() { return m_meshes; }

	void AddMaterial(Material* material) { m_materials.push_back(material); }
	std::vector<Material*>& Materials() { return m_materials; }

private:
	std::vector<Mesh*> m_meshes;
	std::vector<Material*> m_materials;

	Model(unsigned int id, const std::string& path) : Asset(id, path) { }
};