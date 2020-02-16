#pragma once
#include <GLM/glm.hpp>

#include "Component.h"

class Transform : public Component
{
public:
	Transform::Transform() :
		Component(ComponentType::COM_TRANSFORM),
		m_position(glm::vec3(0.0f)),
		m_scale(glm::vec3(1.0f)),
		m_rotation(glm::vec3(0.0f))
	{ }
	~Transform() { }

	glm::vec3& Position()	{ return m_position; }
	glm::vec3& Scale()		{ return m_scale; }
	glm::vec3& Rotation()	{ return m_rotation; }

private:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
};

