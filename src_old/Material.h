#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

#include "Asset.h"

class Shader;
class Texture;

class Material : public Asset
{
public:
	Material(unsigned int id, const std::string& filePath) : Asset(id, filePath) { }
	~Material() { }

	void SetShader(Shader* shader)	{ m_shader = shader; }
	Shader& GetShader()				{ return *m_shader; }

	std::vector<Texture*>& Textures()	{ return m_textures; }
	void AddTexture(Texture* texture)	{ m_textures.push_back(texture); }

	void Bind();
	void Unbind();

	void SetWorld(const glm::mat4& world);
	void SetProjection(const glm::mat4& projection);
	void SetView(const glm::mat4& view);
	void SetViewPosition(const glm::vec3& viewPosition);
	void SetNormalMatrix(const glm::mat3& normalMatrix);

	void SetTextureDiffuse(const GLuint& textureId);
	void SetTextureSpecular(const GLuint& textureId);

	void SetShininess(const float& shininess);

	void SetLightDirection(const std::string& lightTypeName, const glm::vec3& direction);
	void SetLightAmbient(const std::string& lightTypeName, const glm::vec3& ambient);
	void SetLightDiffuse(const std::string& lightTypeName, const glm::vec3& diffuse);
	void SetLightSpecular(const std::string& lightTypeName, const glm::vec3& specular);

private:
	Shader* m_shader;
	std::vector<Texture*> m_textures;

	void BindTextures();
};

namespace MaterialDefinitions
{
	const std::string WORLD = "world";
	const std::string PROJECTION = "projection";
	const std::string VIEW = "view";
	const std::string VIEWPOSITION = "viewPosition";
	const std::string NORMALMATRIX = "normalMatrix";

	const std::string TEX_DEFINITION = "textures.";
	const std::string TEX_DIFFUSE = TEX_DEFINITION + "diffuse";
	const std::string TEX_SPECULAR = TEX_DEFINITION + "specular";

	const std::string MAT_DEFINITION = "material.";
	const std::string MAT_SHININESS = "shininess";

	const std::string LIGHT_DIR_DEFINITION = "dirLight.";
	const std::string LIGHT_POINT_DEFINITION = "pointLight.";
	const std::string LIGHT_SPOT_DEFINITION = "spotLight.";

	const std::string LIGHT_DIRECTION = "direction";
	const std::string LIGHT_AMBIENT = "ambient";
	const std::string LIGHT_DIFFUSE = "diffuse";
	const std::string LIGHT_SPECULAR = "specular";
};

