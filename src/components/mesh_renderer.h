#pragma once
#include "../ecs/component.h"
#include "../graphics/mesh.h"
#include "../graphics/material.h"

namespace bliep {
    struct MeshRenderer : Component {
        Mesh* mesh;

        MeshRenderer(Mesh* mesh) : mesh(mesh) { }
    };
}