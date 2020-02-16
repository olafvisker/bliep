#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>

#include "asset_loader.h"

namespace bliep {
    class ShaderLoader : public AssetLoader {
        public:
            std::unique_ptr<Asset> Load(const std::string& name, const std::string& filepath);
        
        private:
            std::string LoadShaderSource(const std::string& fileName);
            GLuint CreateShaderProgram(const std::string& text, unsigned int type);
            bool CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    };
}