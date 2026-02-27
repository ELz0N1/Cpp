#ifndef LINES_H
#define LINES_H

#include <iostream>
#include <optional>
#include <stdexcept>

struct Point {
  double x;
  double y;

  Point(double x, double y) : x(x), y(y) {};
  friend bool operator==(const Point& p1, const Point& p2);
};

class Line {
  double a;  // Coefficient for x
  double b;  // Coefficient for y
  double c;  // Constant term

  Line(const Point& p1, const Point& p2);
  Line(double a, double b, double c);

 public:
  static std::optional<Line> makeLine(const Point& p1, const Point& p2);
  static std::optional<Line> makeLine(double a, double b, double c);
  std::optional<Point> intersection(const Line& other) const;
  Line perpendicular(const Point& p) const;
  friend bool operator==(Line const&, Line const&);
};

#endif