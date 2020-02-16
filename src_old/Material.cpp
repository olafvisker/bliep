#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Logger.h"

void Material::Bind()
{
	m_shader->Bind();
	BindTextures();
}

void Material::Unbind()
{
	m_shader->Unbind();
}

void Material::BindTextures()
{
	unsigned int index = 0;
	for (auto const &t : m_textures)
	{
		t->Activate(index);
		t->Bind();
		if (t->GetType() == TextureType::TEX_NONE)
			Logger::Log(LogLevel::LOG_WARNING, "Textures '%s' has no specific type assigned.", t->GetPath().c_str());

		if (t->GetType() == TextureType::TEX_DIFFUSE)
		{
			SetTextureDiffuse(index++);
			continue;
		}

		if (t->GetType() == TextureType::TEX_SPECULAR)
		{
			SetTextureSpecular(index++);
			continue;
		}
	}
}

void Material::SetWorld(const glm::mat4& world)
{
	glUniformMatrix4fv(m_shader->GetUniform(MaterialDefinitions::WORLD), 1, GL_FALSE, glm::value_ptr(world));
}
void Material::SetProjection(const glm::mat4& projection)
{
	glUniformMatrix4fv(m_shader->GetUniform(MaterialDefinitions::PROJECTION), 1, GL_FALSE, glm::value_ptr(projection));
}
void Material::SetView(const glm::mat4& view)
{
	glUniformMatrix4fv(m_shader->GetUniform(MaterialDefinitions::VIEW), 1, GL_FALSE, glm::value_ptr(view));
}
void Material::SetViewPosition(const glm::vec3& viewPosition)
{
	glUniform3f(m_shader->GetUniform(MaterialDefinitions::VIEWPOSITION), viewPosition.x, viewPosition.y, viewPosition.z);
}
void Material::SetNormalMatrix(const glm::mat3& normalMatrix)
{
	glUniformMatrix3fv(m_shader->GetUniform(MaterialDefinitions::NORMALMATRIX), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void Material::SetTextureDiffuse(const GLuint& textureId)
{
	glUniform1ui(m_shader->GetUniform(MaterialDefinitions::TEX_DIFFUSE), textureId);
}
void Material::SetTextureSpecular(const GLuint& textureId)
{
	glUniform1ui(m_shader->GetUniform(MaterialDefinitions::TEX_SPECULAR), textureId);
}

void Material::SetShininess(const float& shininess)
{
	glUniform1f(m_shader->GetUniform(MaterialDefinitions::MAT_DEFINITION + MaterialDefinitions::MAT_SHININESS), shininess);
}

void Material::SetLightDirection(const std::string& lightTypeName, const glm::vec3& direction)
{
	glUniform3f(m_shader->GetUniform(lightTypeName + MaterialDefinitions::LIGHT_DIRECTION), direction.x, direction.y, direction.z);
}
void Material::SetLightAmbient(const std::string& lightTypeName, const glm::vec3& ambient)
{
	glUniform3f(m_shader->GetUniform(lightTypeName + MaterialDefinitions::LIGHT_AMBIENT), ambient.x, ambient.y, ambient.z);
}
void Material::SetLightDiffuse(const std::string& lightTypeName, const glm::vec3& diffuse)
{
	glUniform3f(m_shader->GetUniform(lightTypeName + MaterialDefinitions::LIGHT_DIFFUSE), diffuse.x, diffuse.y, diffuse.z);
}
void Material::SetLightSpecular(const std::string& lightTypeName, const glm::vec3& specular)
{
	glUniform3f(m_shader->GetUniform(lightTypeName + MaterialDefinitions::LIGHT_SPECULAR), specular.x, specular.y, specular.z);
}