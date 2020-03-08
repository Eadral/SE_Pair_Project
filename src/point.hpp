// Copyright 2020 Yucong Zhu
#pragma once
#include <tuple>

double constexpr kEps = 1e-12;

struct Point {
    double x, y;
    Point(const double x, const double y) noexcept : x(x), y(y) {}

    // TODO(zyc): optimize
    friend bool operator<(const Point& lhs, const Point& rhs) {
        if (lhs == rhs)
            return false;
        if (abs(lhs.x - rhs.x) <= kEps)
            return lhs.y - rhs.y < kEps;
        else
            return lhs.x - rhs.x < kEps;
    }

    friend bool operator==(const Point& lhs, const Point& rhs) noexcept {
        return abs(lhs.x - rhs.x) <= kEps && abs(lhs.y - rhs.y) <= kEps;
    }
};
