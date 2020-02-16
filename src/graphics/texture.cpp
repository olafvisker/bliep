#include <assert.h>

#include "texture.h"

namespace bliep {
    Texture::~Texture() { glDeleteTextures(1, &m_texture); }

    void Texture::Bind(unsigned int unit) { 
        assert(unit >= 0 && unit < 32);
        glActiveTexture(GL_TEXTURE0 + unit); 
        glBindTexture(GL_TEXTURE_2D, m_texture); 
    }
}