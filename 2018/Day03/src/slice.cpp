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

constexpr size_t FAB_WIDTH = 1000;

using Fabric = std::vector<std::vector<int>>;

struct Claim 
{
  int id = 0;
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;
};

void process(std::vector<Claim>& claims, std::string& line)
{
  int id, x, y, w, h; 
  std::sscanf(line.c_str(), "#%d @ %d,%d: %dx%d",
    &id, &x, &y, &w, &h);

  Claim claim{ id, x, y, w, h };
  claims.push_back(claim);
}

long long adventDay03problem12018(std::vector<Claim>& claims)
{
  Fabric fabric(FAB_WIDTH, std::vector<int>(FAB_WIDTH, 0));

  std::for_each(claims.begin(), claims.end(),
    [&fabric](const Claim& c) 
  {
    for (int i = c.y; i < c.y + c.h; ++i)
      for (int j = c.x; j < c.x + c.w; ++j)
        ++fabric[i][j];
  });

  int count = 0;
  for (const auto& ai : fabric)
    for (const auto i : ai)
      if (i > 1)  ++count;
       
  return count;
}


long long adventDay03problem22018(std::vector<Claim>& claims)
{
  Fabric fabric(FAB_WIDTH, std::vector<int>(FAB_WIDTH, 0));

  std::for_each(claims.begin(), claims.end(),
    [&fabric](const Claim& c)
  {
    for (int i = c.y; i < c.y + c.h; ++i)
      for (int j = c.x; j < c.x + c.w; ++j)
        ++fabric[i][j];
  });

  for (const auto& c : claims) 
  {
    bool intact = true;
    for (int i = c.y; intact && i < c.y + c.h; ++i)
      for (int j = c.x; intact && j < c.x + c.w; ++j)
        if (fabric[i][j] != 1)
        {
          intact = false;
          break;
        }
      
    if (intact)
      return c.id;
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::vector<Claim> claims;
  long long result = 0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(claims, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay03problem12018(claims)
                              : adventDay03problem22018(claims);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day03/input03.txt";
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