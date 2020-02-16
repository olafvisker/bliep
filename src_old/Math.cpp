#include <glm/gtc/matrix_transform.hpp>

#include "Math.h"

glm::vec3 Math::Forward()
{
	return glm::vec3(0, 0, -1);
}

glm::vec3 Math::Forward(glm::vec3 rotation)
{
	glm::vec3 forward;
	forward.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	forward.y = sin(glm::radians(rotation.x));
	forward.z = -cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	return glm::normalize(forward);
}

glm::vec3 Math::Up()
{
	return glm::vec3(0, 1, 0);
}

glm::vec3 Math::Up(glm::vec3 rotation)
{
	return glm::normalize(glm::cross(Forward(rotation), -Right(rotation)));
}

glm::vec3 Math::Right()
{
	return glm::vec3(1, 0, 0);
}

glm::vec3 Math::Right(glm::vec3 rotation)
{
	return glm::normalize(glm::cross(Forward(rotation), Up()));
}

glm::mat4 Math::WorldModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 transform;
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, rotation.x, glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, rotation.y, glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, rotation.z, glm::vec3(0.0, 0.0, 1.0));
	transform = glm::scale(transform, scale);
	return transform;
}

glm::mat3 Math::NormalMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat3 normalMatrix;
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(WorldModel(position, rotation, scale))));
	return normalMatrix;
}