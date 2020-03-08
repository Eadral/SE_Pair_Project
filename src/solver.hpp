#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "circle.hpp"
#include "line.hpp"
#include "point.hpp"

using namespace std;


double sgn(double x) {
	return x < 0 ? -1 : 1;
}


class Solver {
	
	istream &in;
	ostream &out;
	
	int n;
	int n_line;
	int n_circle;

	vector<Line> lines;
	vector<Circle> circles;
	vector<Point> points;

	
public:
	Solver(istream& in, ostream& out) :in(in), out(out) {
		
	}

	int Solve() {
		int err = Input();
		if (err) return err;

		GetPointsInLines();
		GetPointsInCircles();
		GetPointsBetweenLinesAndCircles();

		sort(points.begin(), points.end());
		auto new_end = unique(points.begin(), points.end());
		int unique_number = new_end - points.begin();

		// for (auto i = points.begin(); i != new_end; i++) {
		// 	cerr << i->x << " " << i->y << endl;
		// }
		
		out << unique_number << endl;

		return 0;
	}

	int Input() {
		in >> n;
		n_line = 0;
		n_circle = 0;
		int number = n;
		while (number--) {
			char type;
			in >> type;

			switch (type) {
			case 'L': {
				int x1, y1, x2, y2;
				in >> x1 >> y1 >> x2 >> y2;
				lines.emplace_back(x1, y1, x2, y2);
				n_line++;
			} break;
			case 'C': {
				int x, y, r;
				in >> x >> y >> r;
				circles.emplace_back(x, y, r);
				n_circle++;
			} break;
			default:
				return -1;
			}
		}
		return 0;
	}

	void GetPointsInLines() {
		for (int i = 0; i < n_line-1; i++) {
			for (int j = i+1; j < n_line; j++) {
				LineLineIntersect(lines[i], lines[j]);
			}
		}
	}


	void GetPointsInCircles() {
		for (int i = 0; i < n_circle-1; i++) {
			for (int j = i+1; j < n_circle; j++) {
				CircleCircleIntersect(circles[i], circles[j]);
			}
		}
	}
	

	void GetPointsBetweenLinesAndCircles() {
		for (int i = 0; i < n_line; i++) {
			for (int j = 0; j < n_circle; j++) {
				LineCircleIntersect(lines[i], circles[j]);
			}
		}
	}

	void LineLineIntersect(const Line& a, const Line& b) {
		// TODO(zyc): overflow
		int64_t deno = (a.x1 - a.x2) * (b.y1 - b.y2) - (b.x1 - b.x2) * (a.y1 - a.y2);
		if (deno == 0) {
			return;
		}
		int64_t x_numer = a.x1 * (a.y2 * (b.x1 - b.x2) + b.x2 * b.y1 - b.x1 * b.y2) +
			a.x2 * (a.y1 * (-b.x1 + b.x2) - b.x2 * b.y1 + b.x1 * b.y2);
		int64_t y_numer = a.x1 * a.y2 * (b.y1 - b.y2) +
			a.x2 * a.y1*(-b.y1 + b.y2) + (a.y1 - a.y2) *(b.x2 * b.y1 - b.x1 * b.y2);

		double d_deno = (double)deno;
		double d_x_numer = (double)x_numer;
		double d_y_numer = (double)y_numer;

		double x = d_x_numer / d_deno;
		double y = d_y_numer / d_deno;

		points.emplace_back(x, y);
		
	}

	void CircleCircleIntersect(const Circle& a, const Circle& b) {
		// TODO(zyc): optimize
		double r1 = a.r;
		double r2 = b.r;
		double x1 = a.x;
		double x2 = b.x;
		double y1 = a.y;
		double y2 = b.y;
		
		double dx = b.x - a.x;
		double dy = b.y - a.y;
		double lr = r1 + b.r;
		double dr = abs(r1 - b.r);
		double d = sqrt(dx * dx + dy * dy);
		
		if (d - lr <= eps && d - dr > eps) {
			double p = (r1 + b.r + d) / 2;
			double h = (2 / d) * sqrt(p * (p - r1) * (p - b.r) * (p - d));

			double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);

			double x0 = x1 + (a / d) * (x2 - x1);
			double y0 = y1 + (a / d) * (y2 - y1);

			if (h <= eps) {
				points.emplace_back(x0, y0);
			} else {
				double xp = (h / d) * (y2 - y1);
				double yp = (h / d) * (x2 - x1);

				points.emplace_back(x0 + xp, y0 - yp);
				points.emplace_back(x0 - xp, y0 + yp);
			}
			
			// if ((ab - lr) < eps) {
			
			// }
		}
		

		
	}
	
	void LineCircleIntersect(const Line& l, const Circle& c) {
		// TODO(zyc): overflow
		int x1 = l.x1 - c.x;
		int x2 = l.x2 - c.x;
		int y1 = l.y1 - c.y;
		int y2 = l.y2 - c.y;
		int r = c.r;

		double dx = x2 - x1;
		double dy = y2 - y1;
		double dr2 = dx * dx + dy * dy;
		double D = x1 * y2 - x2 * y1;

		double delta = r * r * dr2 - D * D;
		if (delta < eps) {

		} else if (abs(delta) <= eps) {
			double x = (D * dy) / dr2;
			double y = (-D * dx) / dr2;
			x += c.x;
			y += c.y;
			points.emplace_back(x, y);
		} else {
			double sqrt_delta = sqrt(delta);
			double x_p = sgn(dy) * dx * sqrt_delta;
			double y_p = abs(dy) * sqrt(delta);

			double x1 = (D * dy + x_p) / dr2;
			double x2 = (D * dy - x_p) / dr2;
			double y1 = (-D * dx + y_p) / dr2;
			double y2 = (-D * dx - y_p) / dr2;

			x1 += c.x;
			x2 += c.x;
			y1 += c.y;
			y2 += c.y;
			points.emplace_back(x1, y1);
			points.emplace_back(x2, y2);
		}

		
	}
	
};

