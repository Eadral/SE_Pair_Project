#pragma once
#include <tuple>

double const eps = 1e-6;

class Point {
public:
	double x, y;
	Point(double x, double y) : x(x), y(y) {}

	// TODO: optimize
	friend bool operator<(const Point& lhs, const Point& rhs) {
		if (lhs == rhs)
			return false;
		if (abs(lhs.x - rhs.x) <= eps)
			return lhs.y - rhs.y < eps;
		else
			return lhs.x - rhs.x < eps;
	}

	friend bool operator==(const Point& lhs, const Point& rhs) {
		return abs(lhs.x - rhs.x) <= eps && abs(lhs.y - rhs.y) <= eps;
	}

	
};




