#pragma once
#include <map>
#include <memory>
#include <string>
#include <typeindex>

#include "asset.h"
#include "asset_loader.h"
#include "../core/logger.h"

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/model.h"

//TODO: Finish implementing basepath

namespace bliep {
    class AssetManager {
        public:
            AssetManager();
            ~AssetManager() { }

            std::string GetBasePath() const;
            void SetBasePath(const std::string& path);

            template<typename T, typename L> void Register();

            template<typename T> T* Load(const std::string& name, const std::string& filepath);
            template<typename T> T* Get(const std::string& name);
            template<typename T> bool Has(const std::string& name);

        private:
            std::string m_base_path;
            
            //std::vector<Asset> m_assets;
            //std::map<std::type_index, std::map<std::string, std::unique_ptr<Asset>>> m_asset_ids;
            std::map<std::type_index, std::map<std::string, std::unique_ptr<Asset>>> m_assets;
            std::map<std::type_index, std::unique_ptr<AssetLoader>> m_loaders;
    };

    template<typename T, typename L> void AssetManager::Register() { 
        if (m_loaders.count(typeid(T))) { return; }
        m_loaders[typeid(T)] = std::unique_ptr<L>(new L());
    }

    template<typename T> T* AssetManager::Load(const std::string& name, const std::string& filepath) { 
        if (!m_loaders.count(typeid(T))) { LOGW << "No asset loader for asset '" << name << "' of type '" << typeid(T).name() << "'."; return nullptr; }
        if (m_assets[typeid(T)].count(name)) { LOGW << "Another asset of type '" << typeid(T).name() << "' was already loaded under the name '" << name << "'."; return nullptr; }
        m_assets[typeid(T)][name] = std::move(m_loaders[typeid(T)]->Load(name, filepath));
        return static_cast<T*>(m_assets[typeid(T)][name].get());
    }

    template<typename T> T* AssetManager::Get(const std::string& name) { 
        if (!Has<T>(name)) { return nullptr; }
        return static_cast<T*>(m_assets[typeid(T)][name].get());
    }   

    template<typename T> bool AssetManager::Has(const std::string& name) { 
        return m_assets.count(typeid(T)) && m_assets[typeid(T)].count(name);
    }
}