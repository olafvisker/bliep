#include <glm/gtc/matrix_transform.hpp>

#include "math.h"

namespace bliep {
    glm::vec3 Math::Forward()   { return glm::vec3(0, 0, -1); }
    glm::vec3 Math::Up()        { return glm::vec3(0, 1, 0); }
    glm::vec3 Math::Right()     { return glm::vec3(1, 0, 0); }

    glm::vec3 Math::Forward(const glm::vec3 rotation){
        glm::vec3 forward;
        forward.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        forward.y = sin(glm::radians(rotation.x));
        forward.z = -cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        return glm::normalize(forward);
    }

	
    glm::vec3 Math::Up(const  glm::vec3 rotation)      { return glm::normalize(glm::cross(Forward(rotation), -Right(rotation))); }
    glm::vec3 Math::Right(const  glm::vec3 rotation)   { return glm::normalize(glm::cross(Forward(rotation), Up())); }

    glm::mat4 Math::Matrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        glm::mat4 transform = glm::mat4();
        transform = glm::translate(transform, position);
        transform = glm::rotate(transform, rotation.x, glm::vec3(1.0, 0.0, 0.0));
        transform = glm::rotate(transform, rotation.y, glm::vec3(0.0, 1.0, 0.0));
        transform = glm::rotate(transform, rotation.z, glm::vec3(0.0, 0.0, 1.0));
        transform = glm::scale(transform, scale);
        return transform;
    }

    glm::mat4 Math::LookAt(glm::vec3 origin, glm::vec3 target, glm::vec3 up) {
        return glm::lookAt(origin, target, up);
    }

    glm::mat4 Math::Projection(float fov, float aspect_ration, float near_plane, float far_plane) {
        return glm::perspective(glm::radians(fov), aspect_ration, near_plane, far_plane);
    }

    glm::mat3 Math::Normal(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        return glm::mat3(glm::transpose(glm::inverse(Matrix(position, rotation, scale))));
    }
}