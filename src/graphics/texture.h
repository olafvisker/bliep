#pragma once
#include <GL/glew.h>

#include "../resource/asset.h"

namespace bliep {
    class Texture : public Asset {

        friend class TextureLoader;
        using Asset::Asset;

        public:
            ~Texture();

            GLuint GetId() const{ return m_texture; }

            void Bind(unsigned int unit);
            
        private:
            GLuint m_texture;

            int m_width;
            int m_height;
            int m_channels;
    };
}