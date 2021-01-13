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

#include <intrin.h>

using Point = std::array<int, 2>;

inline Point operator+(const Point& p1, const Point& p2)
{
  return { {std::get<0>(p1) + std::get<0>(p2), std::get<1>(p1) + std::get<1>(p2)} };
}

long long adventDay13problem12016(std::string instrucc)
{    
  const int NUM = std::stoi(instrucc);

  const std::array<Point, 4> DIRS{ {{{-1, 0}}, {{1, 0}}, {{0, -1}}, {{0, 1}}} };
  const Point INIT{ {1, 1} };
  Point TARGET{ {39, 31} };

  auto valid = [NUM](const Point& p) -> bool {
    return p[1] >= 0 && p[0] >= 0 && !(__popcnt(p[1] * (p[1] + 3) + p[0] * (p[1] + p[1] + p[0] + 1) + NUM) & 0x1);
  };

  int steps = 0;
  std::set<Point> queue{ {INIT} };
  std::set<Point> seen{ queue };
  std::set<Point> next;

  while (queue.size() != 0 && !seen.count(TARGET) )
  {
    for (const auto& q : queue)
    {
      for (const auto& d : DIRS)
      {
        if (valid(q + d) && !seen.count(q + d))
        {
          next.emplace(q + d);
          seen.emplace(q + d);
        }
      }
    }

    next.swap(queue), next.clear(), ++steps;
  }

  return steps;
}

long long adventDay13problem22016(std::string instrucc)
{
  const int LIMIT = 50;
  const int NUM = std::stoi(instrucc);

  const std::array<Point, 4> DIRS{ {{{-1, 0}}, {{1, 0}}, {{0, -1}}, {{0, 1}}} };
  const Point INIT{ {1, 1} };
  Point TARGET{ {39, 31} };

  auto valid = [NUM](const Point& p) -> bool {
    return p[1] >= 0 && p[0] >= 0 && !(__popcnt(p[1] * (p[1] + 3) + p[0] * (p[1] + p[1] + p[0] + 1) + NUM) & 0x1);
  };

  int steps = 0;
  std::set<Point> queue{ {INIT} };
  std::set<Point> seen{ queue };
  std::set<Point> next;

  while (queue.size() != 0 && steps != LIMIT)
  {
    for (const auto& q : queue)
    {
      for (const auto& d : DIRS)
      {
        if (valid(q + d) && !seen.count(q + d))
        {
          next.emplace(q + d);
          seen.emplace(q + d);
        }
      }
    }

    next.swap(queue), next.clear(), ++steps;
  }

  return seen.size();
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string instrucc = "1352";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  instrucc.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay13problem12016(instrucc)
                              : adventDay13problem22016(instrucc);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 2)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[1]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}