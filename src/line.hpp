// Copyright 2020 Yucong Zhu
#pragma once

struct Line {
    int x1, y1, x2, y2;
    Line(const int x1, const int y1, const int x2, const int y2) noexcept
        : x1(x1), y1(y1), x2(x2), y2(y2) {}
};
