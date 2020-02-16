#pragma once
#include "../ecs/system.h"

namespace bliep {
    class RenderSystem : public System {
        public:
            enum Sets {
                CAMERAS,
                OBJECTS,
            };

            void Init();
            void Draw();
    };
}