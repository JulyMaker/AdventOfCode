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

#include "grid.h"

void process(std::unordered_map<Grid, Grid, Grid::Hash>& data, std::string& line)
{
  auto itr = std::begin(line);
  bool size_is_two = (*std::next(itr, 2) == '/');
  Grid g(size_is_two ? 2 : 3, itr);
  std::advance(itr, 4);
  Grid gn(size_is_two ? 3 : 4, itr);

  data[g.flip()] = data[g.transpose()] = data[g.flip()] = data[g.transpose()] =
    data[g.flip()] = data[g.transpose()] = data[g.flip()] = data[g.transpose()] = gn;
}

long long adventDay21problem12017(std::unordered_map<Grid, Grid, Grid::Hash>& data)
{
  Grid grid{ '.', '#', '.', '.', '.', '#', '#', '#', '#' };

  int iters = 5;
  while (iters--)
    grid.evolve(data);

  return grid.count();
}

long long adventDay21problem22017(std::unordered_map<Grid, Grid, Grid::Hash>& data)
{
  Grid grid{ '.', '#', '.', '.', '.', '#', '#', '#', '#' };

  int iters = 18;
  while (iters--)
    grid.evolve(data);

  return grid.count();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::unordered_map<Grid, Grid, Grid::Hash> data;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(data, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay21problem12017(data)
                              : adventDay21problem22017(data);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day21/input21.txt";
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