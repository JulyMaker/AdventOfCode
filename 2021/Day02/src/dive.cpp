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


long long adventDay02problem12021(std::ifstream& is)
{
  long long distance = 0;
  long long depth = 0;

  std::string instruction;
  unsigned int steps;

  while (is >> instruction >> steps)
  { 
    if(instruction == "forward")
    {
      distance += steps;
    }
    else if (instruction == "up")
    {
      depth -= steps;
    }
    else if (instruction == "down")
    {
      depth += steps;
    }

  }
  is.close();

  return distance * depth;
}

long long adventDay02problem22021(std::ifstream& is)
{
  long long distance = 0;
  long long depth = 0;
  long long aim = 0;

  std::string instruction;
  unsigned int steps;

  while (is >> instruction >> steps)
  {
    if (instruction == "forward")
    {
      distance += steps;
      depth += aim * steps;
    }
    else if (instruction == "up")
    {
      aim -= steps;
    }
    else if (instruction == "down")
    {
      aim += steps;
    }

  }
  is.close();

  return distance * depth;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay02problem12021(infile)
                                        : adventDay02problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day02/input01.txt";
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