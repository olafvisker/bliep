#include <fstream>

#include "shader_loader.h"
#include "../graphics/shader.h"
#include "../core/logger.h"

namespace bliep {
    std::unique_ptr<Asset> ShaderLoader::Load(const std::string& name, const std::string& filepath) { 
        std::unique_ptr<Shader> shader(new Shader(name, filepath));
        shader->m_program = glCreateProgram();
        shader->m_shaders[0] = CreateShaderProgram(LoadShaderSource(filepath + ".vs"), GL_VERTEX_SHADER);
        shader->m_shaders[1] = CreateShaderProgram(LoadShaderSource(filepath + ".fs"), GL_FRAGMENT_SHADER);

        for(unsigned i = 0; i < shader->NUM_SHADERS; i++) {
            glAttachShader(shader->m_program, shader->m_shaders[i]);
        }

        glLinkProgram(shader->m_program);
        bool success = CheckShaderError(shader->m_program, GL_LINK_STATUS, true, "Shader program linking failed");
        
        if (!success) { return nullptr; }

        glValidateProgram(shader->m_program);
        success = CheckShaderError(shader->m_program, GL_VALIDATE_STATUS, true, "Shader program validation failed");
        
        if (!success) { return nullptr; }
		return shader;
    }

    unsigned ShaderLoader::CreateShaderProgram(const std::string& text, unsigned shader_type) {
        unsigned shader = glCreateShader(shader_type);

        if (shader == 0) { LOGE << "Shader creating failed!"; }
        
        const char* shader_source_strings[1];
        int shader_source_string_lengths[1];

        shader_source_strings[0] = text.c_str();
        shader_source_string_lengths[0] = text.length();

        glShaderSource(shader, 1, shader_source_strings, shader_source_string_lengths);
        glCompileShader(shader);

        CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed");

        return shader;
    }

    std::string ShaderLoader::LoadShaderSource(const std::string& filename) {
        std::ifstream file;
        file.open((filename).c_str());

        std::string output;
        std::string line;

        if (file.is_open()) {
            while (file.good()) {
                getline(file, line);
                output.append(line + "\n");
            }
        }
        else { LOGE << "Failed to load shader '" << filename << "', file not found."; }

        return output;
    }

    bool ShaderLoader::CheckShaderError(unsigned shader, unsigned flag, bool is_program, const std::string& error_msg) {
        int success = 0;
        GLchar error[1024] = { 0 };

        if (is_program) { glGetProgramiv(shader, flag, &success); }
        else            { glGetShaderiv(shader, flag, &success); }

        if (success) { return true; }

        if (is_program) { glGetProgramInfoLog(shader, sizeof(error), NULL, error); }
        else            { glGetShaderInfoLog(shader, sizeof(error), NULL, error); }

        LOGE << error_msg << " : " << error;
        return false;
    }
}