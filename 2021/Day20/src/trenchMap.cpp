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
#include <image.h>

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::string line;
  std::vector<std::string> output;

  while (!input.eof())
  {
    std::getline(input, line);
    //if (line != "")
    {
      output.push_back(line);
    }
  }
  input.close();

  return output;
}

std::vector<std::vector<std::string>> splitByEmptyStrings(std::vector<std::string> strs)
{
  std::vector<std::vector<std::string>> splits;
  std::vector<std::string> current_split;

  for (std::string& str : strs)
  {
    if (!str.empty())
    {
      current_split.emplace_back(std::move(str));
      continue;
    }

    if (current_split.empty()) continue;

    splits.emplace_back(std::move(current_split));
    current_split.clear();
  }

  if (!current_split.empty())
    splits.emplace_back(std::move(current_split));

  return splits;
}

std::vector<bool> parseEnhancementProgram(const std::string rep) 
{
  std::vector<bool> program;
  for (char c : rep) 
  {
    switch (c) 
    {
      case '#':
        program.push_back(true);
        break;
      case '.':
        program.push_back(false);
        break;
    }
  }

  return program;
}

uint64_t adventDay20problem12021(std::ifstream& input)
{
  const int STEPS = 2;
  std::vector<std::string> inputLines = parseInput(input);
  std::vector<std::vector<std::string>> segments = splitByEmptyStrings(std::move(inputLines));

  std::vector<bool> program = parseEnhancementProgram(segments.front().front());

  Image image(segments.back());
  for (int iteration = 0; iteration < STEPS; ++iteration)
    image = image.applyProgram(program);

  return  image.pixelsLit();
}

uint64_t adventDay20problem22021(std::ifstream& input)
{
  const int STEPS = 50;
  std::vector<std::string> inputLines = parseInput(input);
  std::vector<std::vector<std::string>> segments = splitByEmptyStrings(std::move(inputLines));

  std::vector<bool> program = parseEnhancementProgram(segments.front().front());

  Image image(segments.back());
  for (int iteration = 0; iteration < STEPS; ++iteration)
    image = image.applyProgram(program);

  return  image.pixelsLit();
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay20problem12021(infile)
                                       : adventDay20problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day20/input01.txt";
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