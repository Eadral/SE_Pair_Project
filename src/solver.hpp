// Copyright 2020 Yucong Zhu
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "circle.hpp"
#include "error.hpp"
#include "line.hpp"
#include "point.hpp"

using std::vector;
using std::istream;
using std::ostream;
using std::endl;

inline double sgn(const double x) {
    return x < 0 ? -1 : 1;
}

// constexpr int kOptN = 500000;
constexpr int kMaxN = 5000000;

class Solver {
    istream &in_;
    ostream &out_;

    int n_;
    int n_line_;
    int n_circle_;

    vector<Line> lines_;
    vector<Circle> circles_;
    vector<Point> points_;


 public:
    Solver(istream &in, ostream &out)
        :in_(in), out_(out), n_(0), n_line_(0), n_circle_(0) {    }

    int Solve() {
        auto err = Input();
        if (err) return err;

        err = GetPointsInLines();
        if (err) return err;
        err = GetPointsInCircles();
        if (err) return err;
        err = GetPointsBetweenLinesAndCircles();
        if (err) return err;

        out_ << GetAns() << endl;

        return 0;
    }

    int GetAns() {
        Optimize();
        return points_.size();
    }

    int Input() {
        in_ >> n_;
        n_line_ = 0;
        n_circle_ = 0;
        auto number = n_;
        while (number--) {
            char type;
            in_ >> type;

            switch (type) {
            case 'L': {
                int x1, y1, x2, y2;
                in_ >> x1 >> y1 >> x2 >> y2;
                lines_.emplace_back(x1, y1, x2, y2);
                n_line_++;
            } break;
            case 'C': {
                int x, y, r;
                in_ >> x >> y >> r;
                circles_.emplace_back(x, y, r);
                n_circle_++;
            } break;
            default:
                return InvalidInput;
            }
        }
        return 0;
    }

    int GetPointsInLines() {
        for (auto i = 0; i < n_line_-1; i++) {
            for (auto j = i+1; j < n_line_; j++) {
                LineLineIntersect(lines_[i], lines_[j]);
            }
            if (points_.size() > kMaxN) Optimize();
            if (points_.size() > kMaxN) return MaxPointsExceed;
        }
        return 0;
    }


    int GetPointsInCircles() {
        for (auto i = 0; i < n_circle_-1; i++) {
            for (auto j = i+1; j < n_circle_; j++) {
                CircleCircleIntersect(circles_[i], circles_[j]);
            }
            if (points_.size() > kMaxN) Optimize();
            if (points_.size() > kMaxN) return MaxPointsExceed;
        }
        return 0;
    }


    int GetPointsBetweenLinesAndCircles() {
        for (auto i = 0; i < n_line_; i++) {
            for (auto j = 0; j < n_circle_; j++) {
                LineCircleIntersect(lines_[i], circles_[j]);
            }
            if (points_.size() > kMaxN) Optimize();
            if (points_.size() > kMaxN) return MaxPointsExceed;
        }
        return 0;
    }

    void Optimize() {
        sort(points_.begin(), points_.end());
        const auto new_end = unique(points_.begin(), points_.end());
        points_.erase(new_end, points_.end());
    }

    void LineLineIntersect(const Line& a, const Line& b) {
        // TODO(zyc): overflow
        const auto ax1 = static_cast<double>(a.x1);
        const auto ax2 = static_cast<double>(a.x2);
        const auto ay1 = static_cast<double>(a.y1);
        const auto ay2 = static_cast<double>(a.y2);
        const auto bx1 = static_cast<double>(b.x1);
        const auto bx2 = static_cast<double>(b.x2);
        const auto by1 = static_cast<double>(b.y1);
        const auto by2 = static_cast<double>(b.y2);
        const auto denominator =
            (ax1 - ax2) * (by1 - by2) - (bx1 - bx2) * (ay1 - ay2);
        if (denominator == 0) {
            return;
        }
        const auto x_numerator =
            ax1 * (ay2 * (bx1 - bx2) + bx2 * by1 - bx1 * by2) +
            ax2 * (ay1 * (-bx1 + bx2) - bx2 * by1 + bx1 * by2);
        const auto y_numerator =
            ax1 * ay2 * (by1 - by2) +
            ax2 * ay1*(-by1 + by2) + (ay1 - ay2) *(bx2 * by1 - bx1 * by2);

        auto x = x_numerator / denominator;
        auto y = y_numerator / denominator;

        points_.emplace_back(x, y);
    }

    void CircleCircleIntersect(const Circle& a, const Circle& b) {
        // TODO(zyc): optimize
        const auto r1 = static_cast<double>(a.r);
        const auto r2 = static_cast<double>(b.r);
        const auto x1 = static_cast<double>(a.x);
        const auto x2 = static_cast<double>(b.x);
        const auto y1 = static_cast<double>(a.y);
        const auto y2 = static_cast<double>(b.y);

        const auto dx = x2 - x1;
        const auto dy = y2 - y1;
        const auto lr = r1 + r2;
        const auto dr = abs(r1 - r2);
        const auto d = sqrt(dx * dx + dy * dy);

        if (d - lr <= kEps && d - dr >= -kEps) {
            const auto p = (r1 + r2 + d) / 2;
            const auto h = (2 / d) * sqrt(p * (p - r1) * (p - r2) * (p - d));

            const auto va = (r1 * r1 - r2 * r2 + d * d) / (2 * d);

            auto x0 = x1 + (va / d) * (x2 - x1);
            auto y0 = y1 + (va / d) * (y2 - y1);

            if (h <= kEps) {
                points_.emplace_back(x0, y0);
            } else {
                const auto xp = (h / d) * (y2 - y1);
                const auto yp = (h / d) * (x2 - x1);

                points_.emplace_back(x0 + xp, y0 - yp);
                points_.emplace_back(x0 - xp, y0 + yp);
            }
        }
    }

    void LineCircleIntersect(const Line& l, const Circle& c) {
        // TODO(zyc): overflow
        const auto x1 = static_cast<double>(l.x1) - static_cast<double>(c.x);
        const auto x2 = static_cast<double>(l.x2) - static_cast<double>(c.x);
        const auto y1 = static_cast<double>(l.y1) - static_cast<double>(c.y);
        const auto y2 = static_cast<double>(l.y2) - static_cast<double>(c.y);
        const auto r = static_cast<double>(c.r);

        const auto dx = x2 - x1;
        const auto dy = y2 - y1;
        const auto dr2 = dx * dx + dy * dy;
        const auto d = x1 * y2 - x2 * y1;

        const auto delta = r * r * dr2 - d * d;
        if (delta < -kEps) {
        } else if (abs(delta) <= kEps) {
            auto x = (d * dy) / dr2;
            auto y = (-d * dx) / dr2;
            x += c.x;
            y += c.y;
            points_.emplace_back(x, y);
        } else {
            const auto sqrt_delta = sqrt(delta);
            const auto x_p = sgn(dy) * dx * sqrt_delta;
            const auto y_p = abs(dy) * sqrt(delta);

            auto xc = (d * dy + x_p) / dr2;
            auto xd = (d * dy - x_p) / dr2;
            auto yc = (-d * dx + y_p) / dr2;
            auto yd = (-d * dx - y_p) / dr2;

            xc += c.x;
            xd += c.x;
            yc += c.y;
            yd += c.y;
            points_.emplace_back(xc, yc);
            points_.emplace_back(xd, yd);
        }
    }
};

