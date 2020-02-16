#pragma once
#include <GLM/glm.hpp>
#include <string>

#include "Component.h"
#include "Material.h"

enum LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

class Light : public Component
{
public:
	Light() : Component(ComponentType::COM_LIGHT) 
	{
		SetType(LightType::LIGHT_DIRECTIONAL);
	}
	~Light() { }

	void SetType(LightType type) 
	{ 
		switch (type)
		{
			case LIGHT_DIRECTIONAL:
				m_lightTypeName = MaterialDefinitions::LIGHT_DIR_DEFINITION;
				break;
			case LIGHT_POINT:
				m_lightTypeName = MaterialDefinitions::LIGHT_POINT_DEFINITION;
				break;
			case LIGHT_SPOT:
				m_lightTypeName = MaterialDefinitions::LIGHT_SPOT_DEFINITION;
				break;
		}
		m_type = type; 
	}
	LightType GetType() { return m_type; }
	std::string GetLightTypeName() { return m_lightTypeName; }

	glm::vec3& Ambient() { return m_ambient; }
	glm::vec3& Diffuse() { return m_diffuse; }
	glm::vec3& Specular() { return m_specular; }

private:
	LightType m_type;
	std::string m_lightTypeName;

	glm::vec3 m_ambient		= glm::vec3(0.05f);
	glm::vec3 m_diffuse		= glm::vec3(1.0f);
	glm::vec3 m_specular	= glm::vec3(1.0f);
};