#pragma once
#include <string>
#include <memory>
#include <assimp/scene.h>

#include "asset_loader.h"

namespace bliep {
    
    class Model;
    class Mesh;

    class ModelLoader : public AssetLoader {
        public:
            std::unique_ptr<Asset> Load(const std::string& name, const std::string& filepath);

        private:
            void ProcessNode(Model* model, aiNode* node, const aiScene* scene);
            Mesh* ProcessMesh(aiMesh* aimesh, const aiScene* scene);
    };
}