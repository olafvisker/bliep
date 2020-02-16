#pragma once
#include "glm/glm.hpp"

namespace bliep {
    namespace Math{
        glm::vec3 Forward();
        glm::vec3 Up();
        glm::vec3 Right();
        
        glm::vec3 Forward(const glm::vec3 rotation);
        glm::vec3 Up(const glm::vec3 rotation);
        glm::vec3 Right(const glm::vec3 rotation);

        glm::mat4 Matrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        glm::mat4 LookAt(glm::vec3 origin, glm::vec3 target, glm::vec3 up);
        glm::mat4 Projection(float fov, float aspect_ration, float near_plane, float far_plane);
        glm::mat3 Normal(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    }
}