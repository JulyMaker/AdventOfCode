#pragma once

#include <vector>

struct Point 
{
  int64_t x = 0;
  int64_t y = 0;
  
  Point() = default;

  Point(int64_t x_, int64_t y_) { x = x_; y = y_; }

  bool operator==(const Point& other) const 
  {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point& other) const 
  {
    return x != other.x || y != other.y;
  }
  
  Point operator+(const Point& other) const
  {
    return Point(x + other.x, y + other.y);
  }

  Point operator*(int& num) const
  {
    return Point(x * num, y * num);
  }

  Point mul(int& num) const
  {
    return Point(x * num, y * num);
  }

  Point suma(Point& other) const
  {
    return Point(x + other.x, y + other.y);
  }

  Point suma(const Point& other) const
  {
    return Point(x + other.x, y + other.y);
  }

  std::vector<Point> Point::adjacentPoints() const
  {
    std::vector<Point> vecs = { Point(-1, 0), Point(1, 0) , Point(0, -1),Point(0, 1) };
    std::vector<Point> points;
    Point pAux = *this;

    for (auto& v : vecs)
    {
      Point p = pAux.suma(v);
      points.push_back(p);
    }

    return points;
  }
};

struct pointHash {
  size_t operator()(const Point& p) const { return std::hash<int>()((p.x * 39) ^ p.y); }
};
