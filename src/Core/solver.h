// Copyright 2020 Yucong Zhu
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "circle.hpp"
#include "error.h"
#include "exception.h"
#include "line.hpp"
#include "section.hpp"
#include "ray.hpp"
#include "point.hpp"

#include "intersect_dll.h"

using std::vector;
using std::istream;
using std::ostream;
using std::string;
using std::endl;

inline constexpr double sgn(const double x) {
    return x < 0 ? -1 : 1;
}

// constexpr int kOptN = 500000;
//constexpr int kMaxN_ = 5000000;

class Solver {
    istream& in_;
    ostream& out_;

    // int n_;
    // int n_line_;
    // int n_section_;
    // int n_ray_;
    // int n_circle_;

    const int kMaxN_;

public:

    vector<Line> lines_;
    vector<Ray> rays_;
    vector<Section> sections_;
    vector<Circle> circles_;
    vector<Point> points_;

    INTERSECT_API Solver(istream& in, ostream& out, const int kMaxN_ = 5000000) noexcept
        :in_(in), out_(out), kMaxN_(kMaxN_) {    }

    void Clear() {
        // n_ = 0;
        // n_line_ = 0;
        // n_section_ = 0;
        // n_ray_ = 0;
        // n_circle_ = 0;
        lines_.clear();
        rays_.clear();
        sections_.clear();
        circles_.clear();
        points_.clear();
    }

    INTERSECT_API int Solve();

    int SolveWithOutIO();

    INTERSECT_API int GetAns();

    int Input();

    int GetPointsInLines();

    int GetPointsInRays();

    int GetPointsInSections();

    int GetPointsInCircles();

    int GetPointsBetweenLinesAndRays();

    int GetPointsBetweenLinesAndSections();

    int GetPointsBetweenLinesAndCircles();

    int GetPointsBetweenRaysAndSections();

    int GetPointsBetweenRaysAndCircles();

    int GetPointsBetweenSectionsAndCircles();

    INTERSECT_API bool PointOnRay(const double& x, const double& y, const Ray& r);

    INTERSECT_API bool PointOnSection(const double& x, const double& y, const Section& s);

    void Optimize();

    INTERSECT_API void LineLineIntersect(const Line& a, const Line& b);

    INTERSECT_API void RayRayIntersect(const Ray& a, const Ray& b);

    INTERSECT_API void SectionSectionIntersect(const Section& a, const Section& b);

    INTERSECT_API void CircleCircleIntersect(const Circle& a, const Circle& b);

    INTERSECT_API void LineRayIntersect(const Line& l, const Ray& r);

    INTERSECT_API void LineSectionIntersect(const Line& l, const Section& s);
    
    INTERSECT_API void LineCircleIntersect(const Line& l, const Circle& c);

    INTERSECT_API void RaySectionIntersect(const Ray& r, const Section& s);

    INTERSECT_API void RayCircleIntersect(const Ray& r, const Circle& c);

    INTERSECT_API void SectionCircleIntersect(const Section& s, const Circle& c);
};


extern "C" {

    INTERSECT_API void Clear();

    INTERSECT_API void Input(char *input);

    INTERSECT_API void AddLine(int x1, int y1, int x2, int y2);

    INTERSECT_API void RemoveLine(int x1, int y1, int x2, int y2);

    INTERSECT_API int GetLinesSize();

    INTERSECT_API void GetLines(int* x1s, int* y1s, int* x2s, int* y2s, int size);

    INTERSECT_API void AddCircle(int x, int y, int r);

    INTERSECT_API void RemoveCircle(int x, int y, int r);

    INTERSECT_API int GetCirclesSize();

    INTERSECT_API void GetCircles(int* xs, int* ys, int* rs, int size);

    INTERSECT_API void AddRay(int x1, int y1, int x2, int y2);

    INTERSECT_API void RemoveRay(int x1, int y1, int x2, int y2);

    INTERSECT_API int GetRaysSize();

    INTERSECT_API void GetRays(int* x1s, int* y1s, int* x2s, int* y2s, int size);

    INTERSECT_API void AddSection(int x1, int y1, int x2, int y2);

    INTERSECT_API void RemoveSection(int x1, int y1, int x2, int y2);

    INTERSECT_API int GetSectionsSize();

    INTERSECT_API void GetSections(int* x1s, int* y1s, int* x2s, int* y2s, int size);

    INTERSECT_API int GetIntersectionsSize();

    INTERSECT_API void GetIntersections(float* xs, float* ys, int size);

}
