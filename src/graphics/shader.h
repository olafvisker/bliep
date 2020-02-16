#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../resource/asset.h"

namespace bliep {
    class Shader : public Asset {
        
        friend class ShaderLoader;
        using Asset::Asset;

        public:
            ~Shader();

            GLuint GetProgram() const{ return m_program; }

            void Bind();
            void Unbind();

            void SetBool(const std::string &name, bool value) const;
            void SetInt(const std::string &name, int value) const;
            void SetFloat(const std::string &name, float value) const; 
            void SetVec3(const std::string &name, glm::vec3 value) const;     
            void SetVec4(const std::string &name, glm::vec4 value) const;     
            void SetMatrix(const std::string &name, glm::mat3 value) const; 
            void SetMatrix(const std::string &name, glm::mat4 value) const; 

        private:
            static const unsigned int NUM_SHADERS = 2;

            GLuint m_program;
            GLuint m_shaders[NUM_SHADERS];
    };
}