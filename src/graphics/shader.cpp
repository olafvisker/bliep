#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

namespace bliep {
    Shader::~Shader() {
        for (unsigned int i = 0; i < NUM_SHADERS; i++) {
            glDetachShader(m_program, m_shaders[i]);
            glDeleteShader(m_shaders[i]);
        }
        glDeleteProgram(m_program);
    }

    void Shader::Bind() { glUseProgram(m_program); }
    void Shader::Unbind() { glUseProgram(0); }

    void Shader::SetBool(const std::string &name, bool value)           const{ glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value); }
    void Shader::SetInt(const std::string &name, int value)             const{ glUniform1i(glGetUniformLocation(m_program, name.c_str()), value); }
    void Shader::SetFloat(const std::string &name, float value)         const{ glUniform1f(glGetUniformLocation(m_program, name.c_str()), value); } 
    void Shader::SetVec3(const std::string &name, glm::vec3 value)      const{ glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr(value)); } 
    void Shader::SetVec4(const std::string &name, glm::vec4 value)      const{ glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr(value)); } 
    void Shader::SetMatrix(const std::string &name, glm::mat3 value)    const{ glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); } 
    void Shader::SetMatrix(const std::string &name, glm::mat4 value)    const{ glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); } 
}