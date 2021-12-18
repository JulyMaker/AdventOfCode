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
#include <number.h>

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::string line;
  std::vector<std::string> output;

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

uint64_t adventDay18problem12021(std::ifstream& input)
{
  std::vector<std::string> inputVec = parseInput(input);
  std::unique_ptr<Number> result = Number::parse(inputVec.front());

  for (auto line_it = inputVec.begin() + 1; line_it != inputVec.end(); ++line_it) 
  {
    std::unique_ptr<Number> next = Number::parse(*line_it);
    result = Number::add(std::move(result), std::move(next));
    result->reduce();
  }

  return result->magnitude();
}

uint64_t adventDay18problem22021(std::ifstream& input)
{
  std::vector<std::string> inputVec = parseInput(input);

  int maxMagnitude = 0;
  for (auto outer_it = inputVec.begin(); outer_it != inputVec.end(); ++outer_it) 
  {
    for (auto inner_it = inputVec.begin(); inner_it != inputVec.end(); ++inner_it) 
    {
      if (outer_it == inner_it) continue;
      auto outer = Number::parse(*outer_it);
      auto inner = Number::parse(*inner_it);
      auto result = Number::add(std::move(outer), std::move(inner));
      result->reduce();
      maxMagnitude = std::max(maxMagnitude, result->magnitude());

      outer = Number::parse(*outer_it);
      inner = Number::parse(*inner_it);
      result = Number::add(std::move(inner), std::move(outer));
      result->reduce();
      maxMagnitude = std::max(maxMagnitude, result->magnitude());
    }
  }

  return maxMagnitude;
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay18problem12021(infile)
                                       : adventDay18problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day18/input01.txt";
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