#include "debug_systems.h"
#include "debug_components.h"
#include "components/transform.h"
#include "core/engine.h"
#include "math/math.h"

void CameraControllerSystem::Init() {
    Require<bliep::Transform>();
    Require<CameraController>();

    GetEngine().GetInput().LockCursor(true);
}

void CameraControllerSystem::Update() {
    for (auto& e : GetEntities()) {
        bliep::Transform* trans = e.GetComponent<bliep::Transform>();
        CameraController* cc = e.GetComponent<CameraController>();

        float f_input = (float)(GetEngine().GetInput().IsKeyDown(cc->forward) - GetEngine().GetInput().IsKeyDown(cc->backward));
        float u_input = (float)(GetEngine().GetInput().IsKeyDown(cc->up) - GetEngine().GetInput().IsKeyDown(cc->down));
        float s_input = (float)(GetEngine().GetInput().IsKeyDown(cc->right) - GetEngine().GetInput().IsKeyDown(cc->left));

        glm::vec3 input_vec = f_input * bliep::Math::Forward(trans->rotation)   +
                              u_input * bliep::Math::Up(trans->rotation)        +
                              s_input * bliep::Math::Right(trans->rotation);

        trans->position += input_vec * cc->movement_speed * bliep::Time::GetDelta();
        trans->rotation.y += GetEngine().GetInput().GetMouseDeltaX() * cc->rotation_speed * bliep::Time::GetDelta();
        trans->rotation.x -= GetEngine().GetInput().GetMouseDeltaY() * cc->rotation_speed * bliep::Time::GetDelta();

        if (trans->rotation.x > 89)  { trans->rotation.x = 89; }
        if (trans->rotation.x < -89) { trans->rotation.x = -89; }
    }
}