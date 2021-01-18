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


long long adventDay11problem12017(std::string& input)
{
  int x = 0, y = 0, z = 0, dist = 0;
  int v = 0;

  input = input+","; // Last loop
  for(auto& c : input)
  {
    if (std::isalpha(c)) 
    {
      v ^= c;
      continue;
    }

    switch (std::exchange(v, 0)) 
    {
      case 'n'      : ++y, --z; break;
      case 'n' ^ 'e': ++x, --z; break;
      case 's' ^ 'e': ++x, --y; break;
      case 's'      : --y, ++z; break;
      case 's' ^ 'w': --x, ++z; break;
      case 'n' ^ 'w': --x, ++y; break;
    }
    dist = (std::abs(x) + std::abs(y) + std::abs(z)) / 2;
  }

  dist = (std::abs(x) + std::abs(y) + std::abs(z)) / 2;

  return dist;
}


long long adventDay11problem22017(std::string& input)
{
  int x= 0, y= 0, z= 0, dist= 0, max= 0;
  int v = 0;

  input = input + ","; // Last loop
  for (auto& c : input)
  {
    if (std::isalpha(c)) 
    {
      v ^= c;
      continue;
    }

    switch (std::exchange(v, 0)) 
    {
      case 'n':      ++y, --z; break;
      case 'n' ^ 'e': ++x, --z; break;
      case 's' ^ 'e': ++x, --y; break;
      case 's':      --y, ++z; break;
      case 's' ^ 'w': --x, ++z; break;
      case 'n' ^ 'w': --x, ++y; break;
    }

    dist = (std::abs(x) + std::abs(y) + std::abs(z)) / 2;

    max = std::max(max, dist);
  }

  return max;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::string input;
  int pos = 0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    input = line;
  }
  infile.close();

  result = (problNumber == 1) ? adventDay11problem12017(input)
                              : adventDay11problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day11/input11.txt";
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