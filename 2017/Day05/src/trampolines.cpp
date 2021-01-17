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


long long adventDay05problem12017(std::vector<int>& input)
{
  int index = 0;
  int n = static_cast<int>(input.size());
  unsigned int steps= 0;

  while (index >= 0 && index < n) 
  {
    auto idx = static_cast<unsigned int>(index);
    ++steps;
    
    index += input[idx]++;
  }
  return steps;
}

long long adventDay05problem22017(std::vector<int>& input)
{
  int index = 0;
  int n = static_cast<int>(input.size());
  unsigned int steps = 0;

  while (index >= 0 && index < n)
  {
    auto idx = static_cast<unsigned int>(index);
    ++steps;
    if (input[idx] >= 3)
      index += input[idx]--;
    else 
      index += input[idx]++;
  }
  return steps;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<int> input;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    input.push_back(std::stoi(line));
  }
  infile.close();

  result = (problNumber == 1) ? adventDay05problem12017(input)
                              : adventDay05problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day05/input05.txt";
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