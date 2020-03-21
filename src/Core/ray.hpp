#pragma once

#include <tuple>

struct Ray {
    int x1, y1, x2, y2;
    int dx, dy, x2y1, x1y2, x2y1_x1y2;
    Ray(const int x1, const int y1, const int x2, const int y2) noexcept
        : x1(x1), y1(y1), x2(x2), y2(y2)
    {
        dx = (int)x1 - (int)x2;
        dy = (int)y1 - (int)y2;
        x2y1 = (int)x2 * (int)y1;
        x1y2 = (int)x1 * (int)y2;
        x2y1_x1y2 = x2y1 - x1y2;
    }

    friend bool operator==(const Ray& lhs, const Ray& rhs) {
        return std::tie(lhs.x1, lhs.y1, lhs.x2, lhs.y2) == std::tie(rhs.x1, rhs.y1, rhs.x2, rhs.y2);
    }

    friend bool operator!=(const Ray& lhs, const Ray& rhs) {
        return !(lhs == rhs);
    }
};