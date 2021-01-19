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
#include <iterator>
#include <thread>


long long adventDay19problem12017(std::vector<std::string>& grid)
{
  unsigned int const X(grid[0].size()), Y(grid.size());
  unsigned int x(grid[0].find("|")), y= 0, count= 0;
  std::string result;

  for (int dx= 0, dy= 1; grid[y][x] != ' '; x += dx, y += dy, ++count) 
  {
    if (std::isalpha(grid[y][x])) 
    {
      result+= grid[y][x];
    }
    else if (grid[y][x] == '+') {
      dx = -std::exchange(dy, dx);
      if (x + dx >= X || y + dy >= Y || grid[y + dy][x + dx] == ' ')
        dx = -dx, dy = -dy;
    }
  }

  std::cout <<"Result: " << result << std::endl;
  return 0;
}

long long adventDay19problem22017(std::vector<std::string>& grid)
{
  unsigned int const X(grid[0].size()), Y(grid.size());
  unsigned int x(grid[0].find("|")), y= 0, count= 0;

  for (int dx= 0, dy= 1; grid[y][x] != ' '; x += dx, y += dy, ++count) 
  {
    if (grid[y][x] == '+') {
      dx = -std::exchange(dy, dx);
      if (x + dx >= X || y + dy >= Y || grid[y + dy][x + dx] == ' ')
        dx = -dx, dy = -dy;
    }
  }
  
  return count;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> grid;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    grid.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay19problem12017(grid)
                              : adventDay19problem22017(grid);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day19/input19.txt";
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