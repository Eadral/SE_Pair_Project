// Copyright 2020 Yucong Zhu
#pragma once

struct Line {
    int x1, y1, x2, y2;
    int dx, dy, x2y1, x1y2, x2y1_x1y2;
    Line(const int x1, const int y1, const int x2, const int y2) noexcept
        : x1(x1), y1(y1), x2(x2), y2(y2) 
    {
        dx = (int)x1 - (int)x2;
        dy = (int)y1 - (int)y2;
        x2y1 = (int)x2 * (int)y1;
        x1y2 = (int)x1 * (int)y2;
        x2y1_x1y2 = x2y1 - x1y2;
    }
};
