#include "../ecs/component.h"
#include "../types/rectangle.h"

namespace bliep {
    struct Camera : Component {
        float field_of_view     = 60.0f;
        float near_plane        = 0.1f;
        float far_plane         = 10000.0f;
        rectangle viewport;

        Camera() { }
        Camera(rectangle viewport) : viewport(viewport) { }
    };
}