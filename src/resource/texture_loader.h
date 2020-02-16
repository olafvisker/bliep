#pragma once
#include <string>
#include <memory>

#include "asset_loader.h"

namespace bliep {
    class TextureLoader : public AssetLoader {
        public:
            std::unique_ptr<Asset> Load(const std::string& name, const std::string& filepath);        
    };
}