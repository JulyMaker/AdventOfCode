#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <array>
#include <mutex>
#include <numeric>
#include <intrin.h>
#include <tuple>
#include <iomanip>
#include <cctype> 
#include <random>
#include <valarray>
#include <thread>
#include <unordered_set>
#include <optional>
#include <deque>
#include <queue>
#include <ctype.h>

struct Nanobot
{
  int64_t x=0, y=0, z=0, r=0 ;

  bool inRange(const Nanobot& rhs) const
  {
    return r >= (abs(x - rhs.x) + abs(y - rhs.y) + abs(z - rhs.z));
  }

  bool operator<(const Nanobot& rhs) const
  {
    return r < rhs.r;
  }
};
using Nanobots = std::vector< Nanobot >;

Nanobots getNanobots(std::ifstream& infile)
{
  std::regex pattern = std::regex{ "^pos=<([-]?\\d+),([-]?\\d+),([-]?\\d+)>, r=(\\d+)$" };
  Nanobots nanobots = {};

  int64_t x = 0, y = 0, z = 0, r = 0;

  for (std::string line; getline(infile, line); )
  {
    std::smatch m; 
    regex_match(line, m, pattern);
    if (m.size() == 5)
    { 
      x =std::stoi(m[1]), y = std::stoi(m[2]), z = std::stoi(m[3]), r = std::stoi(m[4]);

      nanobots.emplace_back(Nanobot{ x, y, z, r });
    }
  }

  return nanobots;
}

int64_t adventDay23problem12018(std::ifstream& input)
{
  Nanobots nanobots = getNanobots(input);

  auto strongest = *max_element(nanobots.cbegin(), nanobots.cend());
  auto count = count_if(nanobots.cbegin(), nanobots.cend(),
    [&](const auto& nanobot) { return strongest.inRange(nanobot); });

  return count;
}


bool covers(const Nanobot& nanobot, const int64_t& x, const int64_t& y, const int64_t& z, const int64_t& padding)
{
  return (std::abs(x - nanobot.x) + std::abs(y - nanobot.y) + std::abs(z - nanobot.z) <= nanobot.r + padding);
}

struct Point
{
  int64_t x, y, z;
  Point(const int64_t& X, const int64_t& Y, const int64_t& Z) : x(X), y(Y), z(Z) {}

  bool operator<(const Point& p) const
  {
    return x < p.x
      ? true
      : (x > p.x ? false
        : (y < p.y ? true : (y > p.y ? false : z < p.z)));
  }

  bool operator==(const Point& p) const
  {
    return x == p.x && y == p.y && z == p.z;
  }
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << "(" << point.x << "," << point.y << "," << point.z << ")";
  return os;
}

bool covers(const Nanobot& nanobot, const Point& p, const int64_t& padding)
{
  return covers(nanobot, p.x, p.y, p.z, padding);
}

int64_t adventDay23problem22018(std::ifstream& input)
{
  Nanobots nanobots = getNanobots(input);

  std::sort(nanobots.begin(), nanobots.end(), [](const Nanobot& n0, const Nanobot& n1) { return n0.r < n1.r; });

  int64_t x_min(0), y_min(0), z_min(0), x_max(0), y_max(0), z_max(0);
  for (auto& n : nanobots)
  {
    x_min = std::min(x_min, n.x - n.r);
    x_max = std::max(x_max, n.x + n.r + 1);
    y_min = std::min(y_min, n.y - n.r);
    y_max = std::max(y_max, n.y + n.r + 1);
    z_min = std::min(z_min, n.z - n.r);
    z_max = std::max(z_max, n.z + n.r + 1);
  }

  int64_t scale(int64_t(1) << int64_t(std::log2(x_max - x_min + y_max - y_min + z_max - z_min) + 1));
  x_min = (x_min / scale)     * scale;
  x_max = (x_max / scale + 1) * scale;
  y_min = (y_min / scale)     * scale;
  y_max = (y_max / scale + 1) * scale;
  z_min = (z_min / scale)     * scale;
  z_max = (z_max / scale + 1) * scale;

  size_t nx = (x_max - x_min) / scale;
  size_t ny = (y_max - y_min) / scale;
  size_t nz = (z_max - z_min) / scale;

  std::vector<Point> points;
  for (size_t dx = 0; dx < nx; ++dx)
    for (size_t dy = 0; dy < ny; ++dy)
      for (size_t dz = 0; dz < nz; ++dz)
      {
        points.emplace_back(x_min + dx * scale, y_min + dy * scale, z_min + dz * scale);
      }

  while (true)
  {
    size_t max_bots= 0;
    std::vector<Point> new_points;
    for (auto& point : points)
    {
      size_t num_bots(std::count_if(nanobots.begin(), nanobots.end(), 
        [&](const Nanobot& n) { return covers(n, point, scale); }));

      if (num_bots != 0 && num_bots == max_bots)
      {
        new_points.emplace_back(point);
      }

      if (num_bots > max_bots)
      {
        max_bots = num_bots;
        new_points.clear();
        new_points.emplace_back(point);
      }
    }

    if (scale == 0)
    {
      std::swap(points, new_points);
      break;
    }

    points.clear();
    scale /= 2;
    if (scale == 0)
    {
      std::swap(points, new_points);
    }
    else
    {
      for (auto& point : new_points)
      {
        for (int64_t dx = -scale; dx <= scale; dx += scale)
          for (int64_t dy = -scale; dy <= scale; dy += scale)
            for (int64_t dz = -scale; dz <= scale; dz += scale)
              points.emplace_back(point.x + dx, point.y + dy, point.z + dz);
      }

      std::sort(points.begin(), points.end());
      auto last(std::unique(points.begin(), points.end()));
      points.erase(last, points.end());
    }
  }

  int64_t minDistance(std::numeric_limits<int64_t>::max());
  for (auto& point : points)
    minDistance = std::min(minDistance, std::abs(point.x) + std::abs(point.y) + std::abs(point.z));

  return minDistance;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay23problem12018(infile)
                                        : adventDay23problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day23/input23.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return -1;
  }


  long long int result = 0;
  switch (problem)
  {
  case 1:
    result = readFile(fileName, problem);
    break;
  case 2:
    result = readFile(fileName, problem);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}