#include "material.h"
#include "shader.h"
#include "texture.h"
#include "../types/color.h"
#include "../core/logger.h"

namespace bliep {

    void Material::Bind() { 
        BindTextures();
        BindShader();
    }

    void Material::Unbind() {
        m_shader->Unbind();
    }

    Shader& Material::GetShader() const{ return *m_shader; }
    void Material::SetShader(Shader* shader) { m_shader = shader; BindShader(); }

    void Material::SetWorldModel(const glm::mat4 model)         { m_shader->SetMatrix(MaterialDefinitions::WORLDMODEL, model); }
    void Material::SetView(const glm::mat4 view)                { m_shader->SetMatrix(MaterialDefinitions::VIEW, view); }
    void Material::SetProjection(const glm::mat4 projection)    { m_shader->SetMatrix(MaterialDefinitions::PROJECTION, projection); }
    void Material::SetNormal(const glm::mat3& normal)           { m_shader->SetMatrix(MaterialDefinitions::NORMAL, normal); }
    void Material::SetViewPosition(const glm::vec3& position)   { m_shader->SetVec3(MaterialDefinitions::VIEWPOSITION, position); }

    void Material::SetDiffuse(Texture* diffuse)         { m_diffuse = diffuse; m_shader->SetInt(MaterialDefinitions::MAT_DIFFUSE, 0); }
    void Material::SetSpecular(Texture* specular)       { m_specular = specular; m_shader->SetInt(MaterialDefinitions::MAT_SPECULAR, 1); }
    void Material::SetShininess(const float shininess)  { m_shader->SetFloat(MaterialDefinitions::MAT_SHININESS, shininess); };

    void Material::BindShader() { m_shader->Bind();  }
    
    void Material::BindTextures() {
        if (m_diffuse)      { m_diffuse->Bind(0); }
        if (m_specular)     { m_specular->Bind(1); }
    }
}