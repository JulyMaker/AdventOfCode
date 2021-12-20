#pragma once

#include <vector>
#include <vec.h>

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

  // Arithmetic between Points and Vecs.

  Point operator+(const Vec& vec)
  {
    return Point{ x + vec.dx, y + vec.dy};
  }

  Point operator-(const Vec& vec)
  {
    return Point{ x - vec.dx, y - vec.dy };
  }
};

struct pointHash
{
  size_t operator()(const Point& p) const { return std::hash<int>()((p.x * 39) ^ p.y); }
};

template <typename PointContainer>
Point MinDimensions(const PointContainer& container) 
{
  Point min{ std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max() };
  for (const Point& point : container) 
  {
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
  }
  return min;
}

template <typename PointContainer>
Point MaxDimensions(const PointContainer& container) 
{
  Point max{ std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::min() };
  for (const Point& point : container) 
  {
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
  }
  return max;
}

// Renders a set of points, returning a multiline ASCII string where points are
// represented as '#'.
//template <typename PointContainer>
//std::string RenderPoints(const PointContainer& points) 
//{
//  const Point max = MaxDimensions(points);
//
//  std::vector<std::string> view(max.y + 1, std::string(max.x + 1, ' '));
//  for (const Point& point : points) 
//  {
//    view[point.y][point.x] = '#';
//  }
//
//  return absl::StrJoin(view, "\n");
//}