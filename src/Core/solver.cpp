#include "solver.h"

inline int Solver::Solve() {
    try {
        auto err = Input();
        if (err) return err;

        err = GetPointsInLines();
        if (err) return err;
        err = GetPointsInCircles();
        if (err) return err;
        err = GetPointsBetweenLinesAndCircles();
        if (err) return err;
        out_ << GetAns() << endl;
    }
    catch (CoreException e) {
        std::cout << e.showExceptionMessage() << endl;
        return InvalidInput;
    }   
    return 0;
}

inline int Solver::GetAns() {
    Optimize();
    return static_cast<int>(points_.size());
}

inline int Solver::Input() {
    string line_;
    getline(in_, line_);
    std::cout << line_ << endl;
    if (!isDegital(line_)) {
        throw CoreException(WrongFormatOfN);
        return InvalidInput;
    }
    n_ = stoi(line_);
    if (n_ <= 0) {
        throw CoreException(InvalidValueOfN);
        return InvalidInput;
    }
    n_line_ = 0;
    n_circle_ = 0;
    auto number = n_;
    while (getline(in_, line_)) {
        char type = line_.at(0);
        switch (type) {
            case 'L': {
                vector<int> para = readPara(4, line_);
                checkPara(para);
                lines_.emplace_back(para.at(0), para.at(1), para.at(2), para.at(3));
                n_line_++;
            }
                    break;
            case 'R': {
                //int x1, y1, x2, y2;
                //
                //lines_.emplace_back(x1, y1, x2, y2);
                //n_line_++;
            }
                    break;
            case 'S': {
                //int x1, y1, x2, y2;
                //
                //lines_.emplace_back(x1, y1, x2, y2);
                //n_line_++;
            }
                    break;
            case 'C': {
                vector<int> para = readPara(3, line_);
                checkPara(para);
                circles_.emplace_back(para.at(0), para.at(1), para.at(2));
                n_circle_++;
            }
                    break;
            default:
                throw CoreException(WrongFormatOfObjectIdentifier);
        }
        n_--;
    }
    if (n_ > 0) {
        throw CoreException(ObjectInputTooLittle);
    }
    else if (n_ < 0) {
        throw CoreException(ObjectInputTooMuch);
    }
    //while (number--) {
    //    char type;
    //    in_ >> type;

    //    switch (type) {
        //case 'L': {
        //    int x1, y1, x2, y2;
        //    in_ >> x1 >> y1 >> x2 >> y2;
        //    lines_.emplace_back(x1, y1, x2, y2);
        //    n_line_++;
        //}
        //        break;
        //case 'C': {
        //    int x, y, r;
        //    in_ >> x >> y >> r;
        //    circles_.emplace_back(x, y, r);
        //    n_circle_++;
        //}
        //        break;
        //default:
        //    return InvalidInput;
        //}
    //}
    return 0;
}

inline int Solver::GetPointsInLines() {
    for (auto i = 0; i < n_line_ - 1; i++) {
        for (auto j = i + 1; j < n_line_; j++) {
            LineLineIntersect(lines_.at(i), lines_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsInCircles() {
    for (auto i = 0; i < n_circle_ - 1; i++) {
        for (auto j = i + 1; j < n_circle_; j++) {
            CircleCircleIntersect(circles_.at(i), circles_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsBetweenLinesAndCircles() {
    for (auto i = 0; i < n_line_; i++) {
        for (auto j = 0; j < n_circle_; j++) {
            LineCircleIntersect(lines_.at(i), circles_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline void Solver::Optimize() {
    sort(points_.begin(), points_.end());
    const auto new_end = unique(points_.begin(), points_.end());
    points_.erase(new_end, points_.end());
}

inline void Solver::LineLineIntersect(const Line& a, const Line& b) {
    const auto denominator =
        a.dx * b.dy - b.dx * a.dy;
    if (denominator == 0) {
        if (a.x2y1_x1y2 - b.x2y1_x1y2 == 0) {
            throw CoreException(InfiniteIntersectionsFound);
        }
        return;
    }
    const auto x_numerator =
        a.x1 * (a.y2 * b.dx + b.x2y1_x1y2) +
        a.x2 * (a.y1 * -b.dx - b.x2y1_x1y2);
    const auto y_numerator = (b.dy) * (-a.x2y1_x1y2)
        + (a.dy) * (b.x2y1_x1y2);

    auto x = (double)x_numerator / denominator;
    auto y = (double)y_numerator / denominator;

    points_.emplace_back(x, y);
}

inline void Solver::CircleCircleIntersect(const Circle& a, const Circle& b) {
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

    if (dx == 0 && dy == 0 && r1 == r2) {
        throw CoreException(InfiniteIntersectionsFound);
    }

    if (d - lr <= kEps && d - dr >= -kEps) {
        const auto p = (r1 + r2 + d) / 2;
        const auto h = (2 / d) * sqrt(p * (p - r1) * (p - r2) * (p - d));

        const auto va = (r1 * r1 - r2 * r2 + d * d) / (2 * d);

        auto x0 = x1 + (va / d) * (x2 - x1);
        auto y0 = y1 + (va / d) * (y2 - y1);

        if (h <= kEps) {
            points_.emplace_back(x0, y0);
        }
        else {
            const auto xp = (h / d) * (y2 - y1);
            const auto yp = (h / d) * (x2 - x1);

            points_.emplace_back(x0 + xp, y0 - yp);
            points_.emplace_back(x0 - xp, y0 + yp);
        }
    }
}

inline void Solver::LineCircleIntersect(const Line& l, const Circle& c) {
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
    }
    else if (abs(delta) <= kEps) {
        auto x = (d * dy) / dr2;
        auto y = (-d * dx) / dr2;
        x += c.x;
        y += c.y;
        points_.emplace_back(x, y);
    }
    else {
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

