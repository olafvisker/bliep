#pragma once

namespace bliep {
    struct rectangle {
        int x, y, width, height;

        bool operator==(const rectangle& r) const { return (x == r.x && y == r.y && width == r.width && height == r.height); }
        bool operator!=(const rectangle& r) const { return (x != r.x || y != r.y || width != r.width || height != r.height); }

        rectangle() : x(0), y(0), width(0), height(0) { }
        rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) { }
    };
}