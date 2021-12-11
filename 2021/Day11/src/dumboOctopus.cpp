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

using Coords = std::pair<int, int>;

std::vector<std::vector<int>> readGrid (std::ifstream& is)
{
  std::vector<std::vector<int>> grid;
  std::string line;

  while (!is.eof())
  {
    std::vector<int> gridLine;
    std::getline(is, line);

    if (line != "")
    {
      for(auto& c : line)
        gridLine.push_back(c - '0');

      grid.push_back(gridLine);
    }   
  }
  is.close();

  return grid;
}

std::vector<Coords> adjacentCells(const Coords coords, std::vector<std::vector<int>>& grid)
{
  std::vector<Coords> cells;
  const bool left = coords.first > 0;
  const bool right = coords.first < grid.size() - 1;
  const bool up = coords.second > 0;
  const bool down = coords.second < grid[coords.first].size() - 1;

  if (left)          cells.emplace_back(coords.first - 1, coords.second);
  if (left && up)    cells.emplace_back(coords.first - 1, coords.second - 1);
  if (up)            cells.emplace_back(coords.first, coords.second - 1);
  if (right && up)   cells.emplace_back(coords.first + 1, coords.second - 1);
  if (right)         cells.emplace_back(coords.first + 1, coords.second);
  if (right && down) cells.emplace_back(coords.first + 1, coords.second + 1);
  if (down)          cells.emplace_back(coords.first, coords.second + 1);
  if (left && down)  cells.emplace_back(coords.first - 1, coords.second + 1);

  return cells;
}

long long adventDay11problem12021(std::vector<std::vector<int>>& grid)
{
  const int STEPS = 100;
  long long total = 0;
  
  for (int step = 0; step < STEPS; ++step)
  {
    std::queue<Coords> pendingFlashers;

    for (int x = 0; x < grid.size(); ++x)
      for (int y = 0; y < grid[x].size(); ++y)
        if (++grid[x][y] == 10)
          pendingFlashers.emplace(x, y);

    while (!pendingFlashers.empty()) 
    {
      total++;
      Coords flasher = pendingFlashers.front();
      pendingFlashers.pop();
      for (Coords adjacent : adjacentCells(flasher, grid)) 
      {
        if (++grid[adjacent.first][adjacent.second] == 10) 
        {
          pendingFlashers.emplace(adjacent);
        }
      }
    }

    for (int x = 0; x < grid.size(); x++)
      for (int y = 0; y < grid[x].size(); y++)
        if (grid[x][y] > 9)
          grid[x][y] = 0;

  }

  return total;
}
  

long long adventDay11problem22021(std::vector<std::vector<int>>& grid)
{
  const int totalOctopus = grid.size() * grid[0].size();
  int total = 0;

  int step = 0;
  while (total != totalOctopus)
  {
    total = 0;

    std::queue<Coords> pendingFlashers;

    for (int x = 0; x < grid.size(); ++x)
      for (int y = 0; y < grid[x].size(); ++y)
        if (++grid[x][y] == 10)
          pendingFlashers.emplace(x, y);

    while (!pendingFlashers.empty())
    {
      total++;
      Coords flasher = pendingFlashers.front();
      pendingFlashers.pop();
      for (Coords adjacent : adjacentCells(flasher, grid))
      {
        if (++grid[adjacent.first][adjacent.second] == 10)
        {
          pendingFlashers.emplace(adjacent);
        }
      }
    }

    for (int x = 0; x < grid.size(); x++)
      for (int y = 0; y < grid[x].size(); y++)
        if (grid[x][y] > 9)
          grid[x][y] = 0;

    step++;
  }

  return step;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::vector<std::vector<int>> grid = readGrid(infile);

  long long result = (problNumber == 1) ? adventDay11problem12021(grid)
                                        : adventDay11problem22021(grid);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day11/input01.txt";
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