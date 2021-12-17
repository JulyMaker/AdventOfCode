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

struct YInfo 
{
  int64_t minStep = -1;
  int64_t maxStep = -1;
  int64_t highestPos = 0;
};

struct pairHash
{
  template <class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2>& pair) const 
  {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

void parseInput(std::ifstream& input, int64_t& minX, int64_t& maxX, int64_t& minY, int64_t& maxY)
{
  std::string line;

  std::getline(input, line);
  input.close();

  const std::regex pat{ "target area: x=(-?\\d+)..(-?\\d+), y=(-?\\d+)..(-?\\d+)" };
  std::smatch match;
  std::regex_search(line, match, pat);

  minX = std::stoi(match[1].str());
  maxX = std::stoi(match[2].str());
  minY = std::stoi(match[3].str());
  maxY = std::stoi(match[4].str());
}

std::optional<YInfo> stepsForInitialDy(int64_t dy, const int64_t minY, const int64_t maxY) 
{
  YInfo info;
  int64_t posY = 0;
  int64_t step = 0;

  while (posY >= minY)
  {
    if (posY <= maxY)
    {
      if (info.minStep == -1) 
        info.minStep = step;

      info.maxStep = step;
    }

    info.highestPos = std::max(info.highestPos, posY);
    posY += dy;
    --dy;
    ++step;
  }

  if (info.minStep >= 0 && info.maxStep >= 0)
    return info;

  return std::nullopt;
}

int64_t afterStepsX(int64_t dx, int64_t step) 
{
  if (step >= dx)
    return (dx + 1) * dx / 2;

  return (dx + (dx - step + 1)) * step / 2;
}


uint64_t adventDay17problem12021(std::ifstream& input)
{
  const int STEPS = 1000;
  int64_t minX = 0, maxX = 0;
  int64_t minY = 0, maxY = 0;

  parseInput(input, minX, maxX, minY, maxY);
 
  int64_t highestPos = 0;
  for (int64_t candidateY = minY; candidateY < STEPS; ++candidateY)
  {
    auto stepRange = stepsForInitialDy(candidateY, minY, maxY);
    if (!stepRange.has_value()) continue;

    for (int64_t steps = stepRange->minStep; steps <= stepRange->maxStep; ++steps)
    {
      for (int64_t candidateX = 0; candidateX <= maxX; ++candidateX)
      {
        int64_t x_pos = afterStepsX(candidateX, steps);
        if (x_pos >= minX && x_pos <= maxX)
          highestPos = std::max(highestPos, stepRange->highestPos);
      }
    }
  }

  return highestPos;
}

uint64_t adventDay17problem22021(std::ifstream& input)
{
  const int STEPS = 1000;
  int64_t minX = 0, maxX = 0;
  int64_t minY = 0, maxY = 0;

  parseInput(input, minX, maxX, minY, maxY);

  std::unordered_set<std::pair<int, int>, pairHash> validVelocities;
  for (int64_t candidateY = minY; candidateY < STEPS; ++candidateY)
  {
    auto stepRange = stepsForInitialDy(candidateY, minY, maxY);
    if (!stepRange.has_value()) continue;

    for (int64_t steps = stepRange->minStep; steps <= stepRange->maxStep; ++steps)
    {
      for (int64_t candidateX = 0; candidateX <= maxX; ++candidateX)
      {
        int64_t x_pos = afterStepsX(candidateX, steps);
        if (x_pos >= minX && x_pos <= maxX)
          validVelocities.emplace(std::pair{ candidateX, candidateY });
      }
    }
  }

  return validVelocities.size();
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay17problem12021(infile)
                                       : adventDay17problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day17/input01.txt";
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