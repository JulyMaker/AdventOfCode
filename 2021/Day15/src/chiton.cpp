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
#include <point.h>
#include <grid.h>
#include <astar.h>

std::vector<std::string> parseGrid(std::ifstream& infile)
{
  std::string line;
  std::vector<std::string> grid;

  // Read rules
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      grid.push_back(line);
    }
  }
  infile.close();

  return grid;
}


long long adventDay15problem12021(std::ifstream& infile)
{
  std::vector<std::string> grid = parseGrid(infile);
  Grid<int> risk_grid = Grid<int>::readFromDigits(grid);

  std::unordered_map<Point, int, pointHash> risk_to_point{ {Point(0, 0), 0} };
  std::unordered_set<Point, pointHash> new_points{ Point(0, 0) };
  while (!new_points.empty()) 
  {
    std::unordered_set<Point, pointHash> next_points;
    for (const Point& point : new_points) 
    {
      for (const Point& adjacent : point.adjacentPoints())
      {
        if (!risk_grid.inRange(adjacent)) continue;

        const int risk = risk_to_point[point] + risk_grid[adjacent];
        auto [risk_it, inserted] = risk_to_point.try_emplace(adjacent, risk);

        if (inserted || risk_it->second > risk) 
        {
          risk_it->second = risk;
          next_points.emplace(adjacent);
        }
      }
    }
    new_points = std::move(next_points);
  }

  auto destination_it = risk_to_point.find({ static_cast<int64_t>(risk_grid.XSize()) - 1,static_cast<int64_t>(risk_grid.YSize()) - 1 });
  

  return destination_it->second;
}

Grid<int> blowupGrid(const Grid<int>& original_grid) 
{
  Grid<int> new_grid(original_grid.XSize() * 5, original_grid.YSize() * 5);

  const Point x_stride{ static_cast<int64_t>(original_grid.XSize()), 0 };
  const Point y_stride{ 0, static_cast<int64_t>(original_grid.YSize()) };

  for (const Point& original_point : original_grid.Points()) 
  {
    for (int x_repeat = 0; x_repeat < 5; ++x_repeat) 
    {
      for (int y_repeat = 0; y_repeat < 5; ++y_repeat) 
      {
        Point new_point = original_point +  x_stride * x_repeat + y_stride * y_repeat;

        int new_risk = original_grid[original_point] + x_repeat + y_repeat;

        if (new_risk > 9) 
        {
          new_risk -= 9;
        }
        new_grid[new_point] = new_risk;
      }
    }
  }

  return new_grid;
}

long long adventDay15problem22021(std::ifstream& infile)
{
  std::vector<std::string> grid = parseGrid(infile);
  Grid<int> risk_grid = blowupGrid(Grid<int>::readFromDigits(grid));

  const Point goal{ static_cast<int64_t>(risk_grid.XSize()) - 1, static_cast<int64_t>(risk_grid.YSize()) - 1 };

  auto result = aStar<Point, int>(Point(0, 0), goal,[&risk_grid](const Point& p) 
    {
      return risk_grid.filterInRange(p.adjacentPoints());
    },
    [&risk_grid](const Point& from, const Point& to) {
      return risk_grid[to];
    });

  return result->cost;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay15problem12021(infile)
                                        : adventDay15problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day15/input01.txt";
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