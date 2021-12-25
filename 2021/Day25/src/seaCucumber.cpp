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
#include <optional>

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::vector<std::string> output;
  std::string line;

  while (!input.eof()) 
  {
    std::getline(input, line);
    if (line != "") 
    { 
      output.push_back(line);
    }
  }
  input.close();

  return output;
}

class FloorMap 
{
public:
  explicit FloorMap(std::vector<std::string> grid) : grid_(std::move(grid)) {}

  bool step() 
  {
    std::vector<std::pair<size_t, size_t>> eastMov;
    for (size_t y = 0; y < grid_.size(); ++y) 
    {
      for (size_t x = 0; x < grid_[y].size(); ++x) 
      {
        auto p = std::make_pair(y, x);
        if (at(p) == '>' && at(east(p)) == '.') 
        {
          eastMov.emplace_back(p);
        }
      }
    }

    for (const auto& pt : eastMov) 
    {
      at(pt) = '.';
      at(east(pt)) = '>';
    }

    std::vector<std::pair<size_t, size_t>> southMov;
    for (size_t y = 0; y < grid_.size(); ++y) 
    {
      for (size_t x = 0; x < grid_[y].size(); ++x) 
      {
        auto pt = std::make_pair(y, x);
        if (at(pt) == 'v' && at(south(pt)) == '.') 
        {
          southMov.emplace_back(pt);
        }
      }
    }

    for (const auto& pt : southMov) 
    {
      at(pt) = '.';
      at(south(pt)) = 'v';
    }

    return !(eastMov.empty() && southMov.empty());
  }

  void print() const 
  {
    for (const std::string& row : grid_) 
    {
      std::cout << row << "\n";
    }
    std::cout << "\n";
  }

private:
  std::pair<size_t, size_t> east(std::pair<size_t, size_t> pt) const 
  {
    if (++pt.second == grid_[pt.first].size()) 
      pt.second = 0;

    return pt;
  }

  std::pair<size_t, size_t> south(std::pair<size_t, size_t> pt) const 
  {
    if (++pt.first == grid_.size()) 
      pt.first = 0;

    return pt;
  }

  char& at(const std::pair<size_t, size_t>& pt) 
  {
    return grid_[pt.first][pt.second];
  }

  std::vector<std::string> grid_;
};


uint64_t adventDay25problem12021(std::ifstream& input)
{
  FloorMap floorMap(parseInput(input));

  int steps = 0;
  while (floorMap.step()) 
  {
    ++steps;
  }

  //floorMap.print();

  return ++steps;
}


uint64_t adventDay25problem22021(std::ifstream& input)
{
  std::cout << "Happy Advent of Code 2021!" << std::endl;
  return  0;
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay25problem12021(infile)
                                       : adventDay25problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day25/input01.txt";
  int problem = 1;

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