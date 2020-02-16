#pragma once
#include <map>
#include <memory>
#include <typeindex>

#include "Asset.h"
#include "UID.h"
#include "Texture.h"
#include "TextureFactory.h"
#include "Model.h"
#include "ModelFactory.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "Material.h"
#include "MaterialFactory.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	template <class T> T& CreateAsset(const std::string& filePath = "") { }

	template <> Texture& CreateAsset<Texture>(const std::string& filePath)
	{
		Texture* texture = nullptr;
		int index;

		if (ContainsAsset<Texture>(filePath, index))
			texture = (Texture*)m_assets[typeid(Texture)][index];
		else
		{
			texture = m_textureFactory->Create(m_uidTexture.GetNextID(), filePath);
			m_assets[typeid(Texture)][texture->GetAssetID()] = texture;
		}
		return *texture;
	}

	template <> Model& CreateAsset<Model>(const std::string& filePath)
	{
		Model* model = nullptr;
		int index;

		if (ContainsAsset<Model>(filePath, index))
			model = (Model*)m_assets[typeid(Model)][index];
		else
		{
			model = m_modelFactory->Create(m_uidModel.GetNextID(), filePath);
			m_assets[typeid(Model)][model->GetAssetID()] = model;
		}
		return *model;
	}

	template <> Shader& CreateAsset<Shader>(const std::string& filePath)
	{
		Shader* shader = nullptr;
		int index;

		if (ContainsAsset<Shader>(filePath, index))
			shader = (Shader*)m_assets[typeid(Shader)][index];
		else
		{
			shader = m_shaderFactory->Create(m_uidShader.GetNextID(), filePath);
			m_assets[typeid(Shader)][shader->GetAssetID()] = shader;
		}
		return *shader;
	}

	template <> Material& CreateAsset<Material>(const std::string& filePath)
	{
		Material* material = nullptr;
		int index;

		if (ContainsAsset<Material>(filePath, index))
			material = (Material*)m_assets[typeid(Material)][index];
		else
		{
			material = m_materialFactory->Create(m_uidMaterial.GetNextID(), filePath);
			m_assets[typeid(Material)][material->GetAssetID()] = material;
		}
		return *material;
	}

private:
	std::map<std::type_index, std::map<unsigned int, Asset*>> m_assets;

	std::unique_ptr<TextureFactory> m_textureFactory;
	std::unique_ptr<ModelFactory> m_modelFactory;
	std::unique_ptr<ShaderFactory> m_shaderFactory;
	std::unique_ptr<MaterialFactory> m_materialFactory;

	UID m_uidTexture;
	UID m_uidModel;
	UID m_uidShader;
	UID m_uidMaterial;

	template <class T>
	bool ContainsAsset(const std::string& filePath, int& index)
	{
		index = -1;
		for (unsigned int i = 0; i < m_assets[typeid(T)].size(); i++)
			if (m_assets[typeid(T)][i]->GetPath() == filePath)
			{
				index = i;
				return true;
			}
		return false;
	}
};

