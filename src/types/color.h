#pragma once
#include <glm/glm.hpp>

namespace bliep {
    struct color {
        float r;
        float g;
        float b;
        float a;

        bool operator==(const color& color) const { return (r == color.r && g == color.g && b == color.b && a == color.a); }
        bool operator!=(const color& color) const { return (r != color.r || g != color.g || b != color.b || a != color.a); }
        
        operator glm::vec3() { return glm::vec3(r, g, b); }
        operator glm::vec4() { return glm::vec4(r, g, b, a); }

        color(float red, float green, float blue, float alpha = 1.0) {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
    };
}