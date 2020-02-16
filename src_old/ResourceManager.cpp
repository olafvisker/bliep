#include "ResourceManager.h"

ResourceManager::ResourceManager() :
m_textureFactory(new TextureFactory(this)),
m_modelFactory(new ModelFactory(this)),
m_shaderFactory(new ShaderFactory(this)),
m_materialFactory(new MaterialFactory(this))
{ }

ResourceManager::~ResourceManager()
{
	for (auto& i : m_assets)
	{
		for (auto& j : i.second)
		{
			if (typeid(i) == typeid(Texture))
				m_uidTexture.FreeID(j.second->GetAssetID());
			if (typeid(i) == typeid(Model))
				m_uidModel.FreeID(j.second->GetAssetID());
			if (typeid(i) == typeid(Shader))
				m_uidShader.FreeID(j.second->GetAssetID());
			if (typeid(i) == typeid(Material))
				m_uidMaterial.FreeID(j.second->GetAssetID());

			delete j.second;
		}
	}
}