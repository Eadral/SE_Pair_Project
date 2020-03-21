// Copyright 2020 Yucong Zhu
#pragma once
#include <tuple>

struct Circle {
    int x, y, r;
    Circle(const int x, const int y, const int r) noexcept : x(x), y(y), r(r) {}

    friend bool operator==(const Circle& lhs, const Circle& rhs) {
        return std::tie(lhs.x, lhs.y, lhs.r) == std::tie(rhs.x, rhs.y, rhs.r);
    }

    friend bool operator!=(const Circle& lhs, const Circle& rhs) {
        return !(lhs == rhs);
    }
};
