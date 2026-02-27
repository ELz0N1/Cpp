#include <gtest/gtest.h>

#include "lines.hpp"
#include "lines.cpp"

TEST(LinesTest, PointsEquality) {
  Point first(14.1, 23.5);
  Point second(14.1, 23.5);

  EXPECT_EQ(first, second);
}

TEST(LinesTest, MakeLinePoints) {
  std::optional<Line> line = Line::makeLine(Point(1, 1), Point(1, 1)).value();
  EXPECT_EQ(line, std::nullopt);
}

TEST(LinesTest, MakeLineCoeff) {
  std::optional<Line> line = Line::makeLine(0, 0, 0).value();
  EXPECT_EQ(line, std::nullopt);
}

TEST(LinesTest, Intersection) {
  Point common(0, 0);
  Line first = Line::makeLine(Point(1, 1), common).value();
  Line second = Line::makeLine(Point(-1, -1), common).value();

  EXPECT_EQ(first.intersection(second), common);
}

TEST(LinesTest, Perpendicular) {
  Line first = Line::makeLine(-1, 1, 0).value();
  EXPECT_EQ(first.perpendicular(Point(0, 0)), Line::makeLine(1, 1, 0));

  Line second = Line::makeLine(1, 0, -1).value();
  EXPECT_EQ(second.perpendicular(Point(1, 1)), Line::makeLine(0, 1, -1));
}
