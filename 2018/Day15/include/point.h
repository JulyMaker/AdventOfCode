#pragma once

#include <algorithm>
#include <vector>

struct Point
{
  uint8_t x, y;

  Point() = default;
  Point(uint32_t x, uint32_t y)
  {
    this->x = (uint8_t)x;
    this->y = (uint8_t)y;
  }

  bool operator==(const Point& o) const
  {
    return x == o.x && y == o.y;
  }

  bool operator!=(const Point& o) const
  {
    return x != o.x || y != o.y;
  }

  bool operator<(const Point& o) const
  {
    return (y == o.y) ? x < o.x : y < o.y;
  }

  Point up() const { return Point(x, y - 1); }
  Point down() const { return Point(x, y + 1); }
  Point left() const { return Point(x - 1, y); }
  Point right() const { return Point(x + 1, y); }
};

struct Path
{
  Point to;
  std::vector<Point> steps;
};