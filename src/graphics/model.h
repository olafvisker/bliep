#pragma once
#include <vector>
#include <memory>

#include "../resource/asset.h"

namespace bliep {

    class Mesh;
    //class Material;

    class Model : public Asset{

        friend class ModelLoader;
        using Asset::Asset;

        public:
            ~Model();

            void AddMesh(std::unique_ptr<Mesh> mesh);
            std::vector<std::unique_ptr<Mesh>>& Meshes();

            //void AddMaterial(Material* material);
            //std::vector<Material*>& Materials();

        private:
            std::vector<std::unique_ptr<Mesh>> m_meshes;
            //std::vector<Material*> m_materials;
    };
}