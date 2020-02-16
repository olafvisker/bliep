#include "asset_manager.h"
#include "shader_loader.h"
#include "texture_loader.h"
#include "model_loader.h"

namespace bliep {
    AssetManager::AssetManager() {
        Register<Shader, ShaderLoader>();
        Register<Texture, TextureLoader>();
        Register<Model, ModelLoader>();
    }

    std::string AssetManager::GetBasePath()               const{ return m_base_path; }
    void AssetManager::SetBasePath(const std::string& path)    { m_base_path = path; }
}