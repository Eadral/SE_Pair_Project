// Copyright 2020 Yucong Zhu
#pragma once
#include <tuple>

double constexpr kEps = 1e-10;

struct Point {
    double x, y;
    Point(const double x, const double y) noexcept : x(x), y(y) {}

    friend bool operator<(const Point& lhs, const Point& rhs) noexcept {
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


inline int dcmp(double a, double b) {
    if (abs(a - b) <= kEps)
        return 0;
    if (a < b) {
        return -1;
    }
    else {
        return 1;
    }
}
