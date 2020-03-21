#include "solver.h"

inline int Solver::Solve() {
    try {
        auto err = Input();
        if (err) return err;

        err = GetPointsInLines();
        if (err) return err;
        err = GetPointsInRays();
        if (err) return err;
        err = GetPointsInSections();
        if (err) return err;
        err = GetPointsInCircles();
        if (err) return err;
        err = GetPointsBetweenLinesAndRays();
        if (err) return err;
        err = GetPointsBetweenLinesAndSections();
        if (err) return err;
        err = GetPointsBetweenLinesAndCircles();
        if (err) return err;
        err = GetPointsBetweenRaysAndSections();
        if (err) return err;
        err = GetPointsBetweenRaysAndCircles();
        if (err) return err;
        err = GetPointsBetweenSectionsAndCircles();
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
    while (getline(in_, line_)) {
        if (line_.size() != 0) break;
    }
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
    n_ray_ = 0;
    n_section_ = 0;
    n_circle_ = 0;
    auto number = n_;
    while (getline(in_, line_)) {
        if (line_.size() == 0) continue;
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
                vector<int> para = readPara(4, line_);
                checkPara(para);
                rays_.emplace_back(para.at(0), para.at(1), para.at(2), para.at(3));
                n_ray_++;
            }
                    break;
            case 'S': {
                vector<int> para = readPara(4, line_);
                checkPara(para);
                sections_.emplace_back(para.at(0), para.at(1), para.at(2), para.at(3));
                n_section_++;
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
    return 0;
}

inline bool Solver::PointOnRay(const double& x, const double& y, const Ray& r) {
    if (r.dx < 0) {
        return x >= static_cast<double>(r.x1);
    }
    else if (r.dx > 0) {
        return x <= static_cast<double>(r.x1);
    }
    else {
        if (r.dy < 0) {
            return y >= static_cast<double>(r.y1);
        }
        else if (r.dy > 0) {
            return y <= static_cast<double>(r.y1);
        }
    }
    return false;
}

inline bool Solver::PointOnSection(const double& x, const double& y, const Section& s) {
    if (s.dx < 0) {
        return static_cast<double>(s.x1) <= x && x <= static_cast<double>(s.x2);
    }
    else if (s.dx > 0) {
        return static_cast<double>(s.x2) <= x && x <= static_cast<double>(s.x1);
    }
    else {
        if (s.dy < 0) {
            return static_cast<double>(s.y1) <= y && y <= static_cast<double>(s.y2);
        }
        else if (s.dy > 0){
            return static_cast<double>(s.y2) <= y && y <= static_cast<double>(s.y1);
        }
    }
    return false;
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

inline int Solver::GetPointsInRays() {
    for (auto i = 0; i < n_ray_ - 1; i++) {
        for (auto j = i + 1; j < n_ray_; j++) {
            RayRayIntersect(rays_.at(i), rays_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsInSections() {
    for (auto i = 0; i < n_section_ - 1; i++) {
        for (auto j = i + 1; j < n_section_; j++) {
            SectionSectionIntersect(sections_.at(i), sections_.at(j));
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

inline int Solver::GetPointsBetweenLinesAndRays() {
    for (auto i = 0; i < n_line_; i++) {
        for (auto j = 0; j < n_ray_; j++) {
            LineRayIntersect(lines_.at(i), rays_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsBetweenLinesAndSections() {
    for (auto i = 0; i < n_line_; i++) {
        for (auto j = 0; j < n_section_; j++) {
            LineSectionIntersect(lines_.at(i), sections_.at(j));
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

inline int Solver::GetPointsBetweenRaysAndSections() {
    for (auto i = 0; i < n_ray_; i++) {
        for (auto j = 0; j < n_section_; j++) {
            RaySectionIntersect(rays_.at(i), sections_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsBetweenRaysAndCircles() {
    for (auto i = 0; i < n_ray_; i++) {
        for (auto j = 0; j < n_circle_; j++) {
            RayCircleIntersect(rays_.at(i), circles_.at(j));
        }
        if (points_.size() > kMaxN_) Optimize();
        if (points_.size() > kMaxN_) return MaxPointsExceed;
    }
    return 0;
}

inline int Solver::GetPointsBetweenSectionsAndCircles() {
    for (auto i = 0; i < n_section_; i++) {
        for (auto j = 0; j < n_circle_; j++) {
            SectionCircleIntersect(sections_.at(i), circles_.at(j));
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

inline void Solver::RayRayIntersect(const Ray& a, const Ray& b) {
    const auto denominator =
        a.dx * b.dy - b.dx * a.dy;
    if (denominator == 0) {
        if (a.x2y1_x1y2 - b.x2y1_x1y2 == 0) {
            if (a.dx * b.dx < 0 || a.dy * b.dy < 0) {
                if (a.x1 == b.x1 && a.y1 == b.y1) {
                    //same start point, different direction
                    points_.emplace_back(a.x1, a.y1);
                    return;
                }
                else if (a.dx * (b.x1 - a.x1) > 0 || a.dy * (b.y1 - a.y1) > 0) {
                    //never meet
                    return;
                }
            }
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

    if (PointOnRay(x, y, a) && PointOnRay(x, y, b)) {
        points_.emplace_back(x, y);
    } 
}

inline void Solver::SectionSectionIntersect(const Section& a, const Section& b) {
    const auto denominator =
        a.dx * b.dy - b.dx * a.dy;
    if (denominator == 0) {
        //TODO: modify exception condition
        if (a.x2y1_x1y2 - b.x2y1_x1y2 == 0) {
            if (a.dx != 0) {
                const auto a_xmin = std::min(a.x1, a.x2);
                const auto a_xmax = std::max(a.x1, a.x2);
                const auto b_xmin = std::min(b.x1, b.x2);
                const auto b_xmax = std::max(b.x1, b.x2);
                if (b_xmax < a_xmin || a_xmax < b_xmin) {
                    //never meet
                    return;
                }
                else if (b_xmax == a_xmin) {
                    if (a_xmin == a.x1) {
                        points_.emplace_back(a.x1, a.y1);
                    }
                    else {
                        points_.emplace_back(a.x2, a.y2);
                    }
                    return;
                }
                else if (a_xmax == b_xmin) {
                    if (a_xmax == a.x1) {
                        points_.emplace_back(a.x1, a.y1);
                    }
                    else {
                        points_.emplace_back(a.x2, a.y2);
                    }
                    return;
                }
                else {
                    throw CoreException(InfiniteIntersectionsFound);
                }
             }
            else {
                const auto a_ymin = std::min(a.y1, a.y2);
                const auto a_ymax = std::max(a.y1, a.y2);
                const auto b_ymin = std::min(b.y1, b.y2);
                const auto b_ymax = std::max(b.y1, b.y2);
                if (b_ymax < a_ymin || a_ymax < b_ymin) {
                    //never meet
                    return;
                }
                else if (b_ymax == a_ymin) {
                    if (a_ymin == a.y1) {
                        points_.emplace_back(a.x1, a.y1);
                    }
                    else {
                        points_.emplace_back(a.x2, a.y2);
                    }
                    return;
                }
                else if (a_ymax == b_ymin) {
                    if (a_ymax == a.y1) {
                        points_.emplace_back(a.x1, a.y1);
                    }
                    else {
                        points_.emplace_back(a.x2, a.y2);
                    }
                    return;
                }
                else {
                    throw CoreException(InfiniteIntersectionsFound);
                }
            }
        }
    }
    const auto x_numerator =
        a.x1 * (a.y2 * b.dx + b.x2y1_x1y2) +
        a.x2 * (a.y1 * -b.dx - b.x2y1_x1y2);
    const auto y_numerator = (b.dy) * (-a.x2y1_x1y2)
        + (a.dy) * (b.x2y1_x1y2);

    auto x = (double)x_numerator / denominator;
    auto y = (double)y_numerator / denominator;

    if (PointOnSection(x, y, a) && PointOnSection(x, y, b)) {
        points_.emplace_back(x, y);
    }
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

inline void Solver::LineRayIntersect(const Line& l, const Ray& r) {
    const auto denominator =
        l.dx * r.dy - r.dx * l.dy;
    if (denominator == 0) {
        if (l.x2y1_x1y2 - r.x2y1_x1y2 == 0) {
            throw CoreException(InfiniteIntersectionsFound);
        }
        return;
    }
    const auto x_numerator =
        l.x1 * (l.y2 * r.dx + r.x2y1_x1y2) +
        l.x2 * (l.y1 * -r.dx - r.x2y1_x1y2);
    const auto y_numerator = (r.dy) * (-l.x2y1_x1y2)
        + (l.dy) * (r.x2y1_x1y2);

    auto x = (double)x_numerator / denominator;
    auto y = (double)y_numerator / denominator;

    if (PointOnRay(x, y, r)) points_.emplace_back(x, y);
}

inline void Solver::LineSectionIntersect(const Line& l, const Section& s) {
    const auto denominator =
        l.dx * s.dy - s.dx * l.dy;
    if (denominator == 0) {
        if (l.x2y1_x1y2 - s.x2y1_x1y2 == 0) {
            throw CoreException(InfiniteIntersectionsFound);
        }
        return;
    }
    const auto x_numerator =
        l.x1 * (l.y2 * s.dx + s.x2y1_x1y2) +
        l.x2 * (l.y1 * -s.dx - s.x2y1_x1y2);
    const auto y_numerator = (s.dy) * (-l.x2y1_x1y2)
        + (l.dy) * (s.x2y1_x1y2);

    auto x = (double)x_numerator / denominator;
    auto y = (double)y_numerator / denominator;

    if (PointOnSection(x, y, s)) points_.emplace_back(x, y);
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

inline void Solver::RaySectionIntersect(const Ray& r, const Section& s) {
    const auto denominator =
        r.dx * s.dy - s.dx * r.dy;
    if (denominator == 0) {
        //TODO: modify exception condition
        if (r.x2y1_x1y2 - s.x2y1_x1y2 == 0) {
            if (r.dx != 0) {
                const auto s_xmin = std::min(s.x1, s.x2);
                const auto s_xmax = std::max(s.x1, s.x2);
                if (r.dx < 0) {
                    if (s_xmax > r.x1) {
                        throw CoreException(InfiniteIntersectionsFound);
                    }
                    else if (s_xmax == r.x1) {
                        points_.emplace_back(r.x1, r.y1);
                    }
                    return;
                }
                else {
                    if (s_xmin < r.x1) {
                        throw CoreException(InfiniteIntersectionsFound);
                    }
                    else if (s_xmin == r.x1) {
                        points_.emplace_back(r.x1, r.y1);
                    }
                    return;
                }
            }
            else {
                const auto s_ymin = std::min(s.y1, s.y2);
                const auto s_ymax = std::max(s.y1, s.y2);
                if (r.dy < 0) {
                    if (s_ymax > r.y1) {
                        throw CoreException(InfiniteIntersectionsFound);
                    }
                    else if (s_ymax == r.y1) {
                        points_.emplace_back(r.x1, r.y1);
                    }
                    return;
                }
                else {
                    if (s_ymin < r.y1) {
                        throw CoreException(InfiniteIntersectionsFound);
                    }
                    else if (s_ymin == r.y1) {
                        points_.emplace_back(r.x1, r.y1);
                    }
                    return;
                }
            }
            throw CoreException(InfiniteIntersectionsFound);
        }
        return;
    }
    const auto x_numerator =
        r.x1 * (r.y2 * s.dx + s.x2y1_x1y2) +
        r.x2 * (r.y1 * -s.dx - s.x2y1_x1y2);
    const auto y_numerator = (s.dy) * (-r.x2y1_x1y2)
        + (r.dy) * (s.x2y1_x1y2);

    auto x = (double)x_numerator / denominator;
    auto y = (double)y_numerator / denominator;

    if (PointOnRay(x, y, r) && PointOnSection(x, y, s)) {
        points_.emplace_back(x, y);
    }
}

inline void Solver::RayCircleIntersect(const Ray& ray, const Circle& c) {
    const auto x1 = static_cast<double>(ray.x1) - static_cast<double>(c.x);
    const auto x2 = static_cast<double>(ray.x2) - static_cast<double>(c.x);
    const auto y1 = static_cast<double>(ray.y1) - static_cast<double>(c.y);
    const auto y2 = static_cast<double>(ray.y2) - static_cast<double>(c.y);
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
        if (PointOnRay(xc, yc, ray)) points_.emplace_back(xc, yc);
        if (PointOnRay(xd, yd, ray)) points_.emplace_back(xd, yd);
    }
}

inline void Solver::SectionCircleIntersect(const Section& s, const Circle& c) {
    const auto x1 = static_cast<double>(s.x1) - static_cast<double>(c.x);
    const auto x2 = static_cast<double>(s.x2) - static_cast<double>(c.x);
    const auto y1 = static_cast<double>(s.y1) - static_cast<double>(c.y);
    const auto y2 = static_cast<double>(s.y2) - static_cast<double>(c.y);
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
        if (PointOnSection(xc, yc, s)) points_.emplace_back(xc, yc);
        if (PointOnSection(xd, yd, s)) points_.emplace_back(xd, yd);
    }
}