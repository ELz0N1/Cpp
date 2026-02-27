#include "lines.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

static bool isEqual(double a, double b) {
  auto abs_max = fabs(fmax(a, b));
  auto epsilon = std::numeric_limits<double>::epsilon();
  if (abs_max != 0) epsilon *= abs_max;
  return std::fabs(a - b) < epsilon;
}

static double lineNorm(double x, double y) {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2)) * (x < 0 ? -1 : 1);
}

bool operator==(const Point& p1, const Point& p2) {
  return isEqual(p1.x, p2.x) && isEqual(p1.y, p2.y);
}

bool operator==(const Line& l1, const Line& l2) {
  double norm1 = lineNorm(l1.a, l1.b);
  double norm2 = lineNorm(l2.a, l2.b);
  return isEqual(l1.b / norm1, l2.b / norm2) &&
         isEqual(l1.c / norm1, l2.c / norm2);
}

Line::Line(const Point& p1, const Point& p2)
    : a(-(p2.y - p1.y)), b(p2.x - p1.x), c(-(a * p1.x + b * p1.y)) {}

Line::Line(double a, double b, double c) : a(a), b(b), c(c) {}

std::optional<Line> Line::makeLine(const Point& p1, const Point& p2) {
  if (p1 == p2) return std::nullopt;
  return Line(p1, p2);
}
std::optional<Line> Line::makeLine(double a, double b, double c) {
  if (isEqual(a, 0) && isEqual(b, 0) && isEqual(c, 0)) return std::nullopt;
  return Line(a, b, c);
}

std::optional<Point> Line::intersection(const Line& other) const {
  double determinant = a * other.b - b * other.a;

  if (isEqual(determinant, 0)) return std::nullopt;

  double x = (other.b * c - b * other.c) / determinant;
  double y = (a * other.c - c * other.a) / determinant;

  return Point(x, y);
}

Line Line::perpendicular(const Point& p) const {
  return Line(-b, a, b * p.x - a * p.y);  
}
