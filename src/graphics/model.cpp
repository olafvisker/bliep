#include <vector>
#include <memory>

#include "model.h"
#include "mesh.h"
//#include "material.h"

namespace bliep {
    Model::~Model() { }

    void Model::AddMesh(std::unique_ptr<Mesh> mesh) { m_meshes.push_back(std::move(mesh)); }
    std::vector<std::unique_ptr<Mesh>>& Model::Meshes() { return m_meshes; }

    //void AddMaterial(Material* material) { m_materials.push_back(material); }
    //std::vector<Material*>& Materials() { return m_materials; }
}