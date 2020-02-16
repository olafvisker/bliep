#pragma once
#include <GLM/glm.hpp>

#include "../ecs/component.h"

namespace bliep {
    struct Transform : Component {
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        Transform(glm::vec3 pos=glm::vec3(0.0f), glm::vec3 scale=glm::vec3(1.0f), glm::vec3 rot=glm::vec3(0.0f)) : position(pos), scale(scale), rotation(rotation) { }
    };
}