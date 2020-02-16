#pragma once
#include <string>
#include <memory>

#include "asset.h"

namespace bliep {
    class AssetLoader {
        public:
            virtual std::unique_ptr<Asset> Load(const std::string& name, const std::string& filepath) { return nullptr; };
    };
}