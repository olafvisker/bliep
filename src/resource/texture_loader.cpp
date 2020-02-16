#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "texture_loader.h"
#include "../graphics/texture.h"
#include "../core/logger.h"

namespace bliep {
    std::unique_ptr<Asset> TextureLoader::Load(const std::string& name, const std::string& filepath) {     
        std::unique_ptr<Texture> texture(new Texture(name, filepath + ".png"));
        
        stbi_set_flip_vertically_on_load(true);  
        unsigned char* img_data = stbi_load(texture->GetPath().c_str(), &texture->m_width, &texture->m_height, &texture->m_channels, 4);
        
        if (img_data == NULL) {
            LOGW << "Failed to load texture '" << texture->GetPath() << "'.";
            return nullptr;
        }

        glGenTextures(1, &texture->m_texture);
        glBindTexture(GL_TEXTURE_2D, texture->m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->m_width, texture->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(img_data);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    } 
}