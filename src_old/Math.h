#pragma once
#include <GLM/glm.hpp>

namespace Math
{
	extern glm::vec3 Forward();
	extern glm::vec3 Forward(glm::vec3 rotation);

	extern glm::vec3 Up();
	extern glm::vec3 Up(glm::vec3 rotation);

	extern glm::vec3 Right();
	extern glm::vec3 Right(glm::vec3 rotation);

	extern glm::mat4 WorldModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	extern glm::mat3 NormalMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
};