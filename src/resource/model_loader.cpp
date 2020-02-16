#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <vector>

#include "model_loader.h"
#include "../graphics/model.h"
#include "../graphics/mesh.h"
#include "../core/logger.h"

namespace bliep {
    std::unique_ptr<Asset> ModelLoader::Load(const std::string& name, const std::string& filepath) {     
        std::unique_ptr<Model> model(new Model(name, filepath + ".obj"));
        
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filepath + ".obj", aiProcess_Triangulate | aiProcess_FlipUVs); 
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)  { LOGE << "Model '" << name << "' failed to load: " << importer.GetErrorString(); return nullptr; }

        ProcessNode(model.get(), scene->mRootNode, scene);
        return model;
    } 

    void ModelLoader::ProcessNode(Model* model, aiNode *node, const aiScene *scene) {
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *aimesh = scene->mMeshes[node->mMeshes[i]]; 
            model->AddMesh(std::unique_ptr<Mesh>(ProcessMesh(aimesh, scene)));			
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(model, node->mChildren[i], scene);
        }
    } 

    Mesh* ModelLoader::ProcessMesh(aiMesh *aimesh, const aiScene *scene) {
        Mesh* mesh = new Mesh();
        std::vector<glm::vec3> vertices;
        std::vector<unsigned> indices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        std::vector<glm::vec2> uvs;

        //std::vector<Texture> textures;

        bool has_normals = aimesh->HasNormals();
        bool has_tangents = aimesh->HasTangentsAndBitangents();
        bool has_uvs = aimesh->HasTextureCoords(0);

        for(unsigned int i = 0; i < aimesh->mNumVertices; i++) {
            glm::vec3 vertex(0.0);            
            glm::vec3 normal(0.0);
            glm::vec2 uv(0.0);
            glm::vec3 tangent(0.0);
            glm::vec3 bitangent(0.0);

            vertex.x = aimesh->mVertices[i].x;
            vertex.y = aimesh->mVertices[i].y;
            vertex.z = aimesh->mVertices[i].z;

            if (has_normals) {
                normal.x = aimesh->mNormals[i].x;
                normal.y = aimesh->mNormals[i].y;
                normal.z = aimesh->mNormals[i].z;
            }
            
            if(has_uvs) {
                uv.x = aimesh->mTextureCoords[0][i].x; 
                uv.y = aimesh->mTextureCoords[0][i].y;
            }

            if (has_tangents) {
                tangent.x = aimesh->mTangents[i].x;
                tangent.y = aimesh->mTangents[i].y;
                tangent.z = aimesh->mTangents[i].z;

                bitangent.x = aimesh->mBitangents[i].x;
                bitangent.y = aimesh->mBitangents[i].y;
                bitangent.z = aimesh->mBitangents[i].z;
            }

            vertices.push_back(vertex);
            normals.push_back(normal);
            uvs.push_back(uv);
            tangents.push_back(tangent);
            bitangents.push_back(bitangent);
        }
        
        for(unsigned int i = 0; i < aimesh->mNumFaces; i++) {
            aiFace face = aimesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 
        //...
        
        mesh->SetVertices(vertices);
        mesh->SetIndices(indices);
        mesh->SetNormals(normals);
        mesh->SetTangets(tangents);
        mesh->SetBitangents(bitangents);
        mesh->SetUVs(uvs);
        mesh->Build();
        
        return mesh;
    }  
}