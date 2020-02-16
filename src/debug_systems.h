#pragma once
#include "ecs/system.h"

class CameraControllerSystem : public bliep::System {
    public:
        void Init();
        void Update();
};