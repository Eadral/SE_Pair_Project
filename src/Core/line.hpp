// Copyright 2020 Yucong Zhu
#pragma once

struct Line {
    long long x1, y1, x2, y2;
    long long dx, dy, x2y1, x1y2, x2y1_x1y2;
    Line(const int x1, const int y1, const int x2, const int y2) noexcept
        : x1(x1), y1(y1), x2(x2), y2(y2) 
    {
        dx = (long long)x1 - (long long)x2;
        dy = (long long)y1 - (long long)y2;
        x2y1 = (long long)x2 * (long long)y1;
        x1y2 = (long long)x1 * (long long)y2;
        x2y1_x1y2 = x2y1 - x1y2;
    }
};
