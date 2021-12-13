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
#include <deque>
#include <stack>
#include <queue>

struct Point 
{
  int64_t x_ = 0;
  int64_t y_ = 0;

  Point(int64_t x, int64_t y)
  {
    x_ = x;
    y_ = y;
  }

  bool operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }

  bool operator!=(const Point& other) const {
    return x_ != other.x_ || y_ != other.y_;
  }
};

struct MyHash {
  size_t operator()(const Point& p) const { return std::hash<int>()((p.x_*39)^p.y_); }
};

struct Fold 
{
  bool x_ = false;
  int64_t value_ = 0;

  Fold(bool x, int64_t value)
  {
    x_ = x;
    value_ = value;
  }
};

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}

void parsePointsAndFolds(std::ifstream& infile, std::unordered_set<Point, MyHash>& points, std::vector<Fold>& folds)
{
  std::string line;

  // Read points
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      std::vector<std::string> coords = split(line, ",");
      
      Point point(std::stoi(coords[0]), std::stoi(coords[1]));
      points.emplace(point);
    }
    else
      break;
  }

  // Read folds
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      Fold fold (line[11] == 'x', std::stoi(line.substr(13)));
      folds.emplace_back(fold);
    }
  }
  infile.close();
}

std::unordered_set<Point, MyHash> applyFold(std::unordered_set<Point, MyHash>& points, const Fold& fold)
{
  std::unordered_set<Point, MyHash> new_points;

  for (const Point& point : points) 
  {
    if (fold.x_) 
    {
      if (point.x_ < fold.value_) 
      {
        new_points.emplace(point);
      }
      else 
      {
        const int64_t dist = point.x_ - fold.value_;
        Point folded(point);
        folded.x_ = fold.value_ - dist;
        new_points.emplace(folded);
      }
    }
    else 
    {
      if (point.y_ < fold.value_) 
      {
        new_points.emplace(point);
      }
      else 
      {
        const int64_t dist = point.y_ - fold.value_;
        Point folded(point);
        folded.y_ = fold.value_ - dist;
        new_points.emplace(folded);
      }
    }
  }

  return new_points;
}

long long adventDay13problem12021(std::ifstream& infile)
{
  std::unordered_set<Point, MyHash> points;
  std::vector<Fold> folds;

  parsePointsAndFolds(infile, points, folds);

  return applyFold(points, folds.front()).size();
}
  
void renderPoints(const std::unordered_set<Point, MyHash>& points) {
  int64_t max_x = 0;
  int64_t max_y = 0;

  for (const Point& point : points) 
  {
    max_x = std::max(max_x, point.x_);
    max_y = std::max(max_y, point.y_);
  }

  std::vector<std::string> view(max_y + 1, std::string(max_x + 1, ' '));
  for (const Point& point : points) 
  {
    view[point.y_][point.x_] = '#';
  }

  for (const std::string& line : view) 
  {
    std::cout << line << "\n";
  }
}

long long adventDay13problem22021(std::ifstream& infile)
{
  std::unordered_set<Point, MyHash> points;
  std::vector<Fold> folds;

  parsePointsAndFolds(infile, points, folds);

  for (const Fold& fold : folds) 
  {
    points = applyFold(std::move(points), fold);
  }

  renderPoints(points);

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay13problem12021(infile)
                                        : adventDay13problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day13/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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