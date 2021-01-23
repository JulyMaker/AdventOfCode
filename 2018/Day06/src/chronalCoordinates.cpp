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

#include "Grid.h"


long long adventDay06problem12018(std::vector<std::string>& input)
{ 
  auto grid = Grid{ input };

  return grid.max_finite_area();
}

long long adventDay06problem22018(std::vector<std::string>& input)
{ 
  auto grid = Grid{ input };

  grid.paint_safe_region(10000);

  return grid.get_safe_region_size();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::vector<std::string> input;
  long long result = 0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    input.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay06problem12018(input)
                              : adventDay06problem22018(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day06/input06.txt";
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