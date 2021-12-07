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


std::vector<int> split(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(std::stoi(text.substr(start, end - start)));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(std::stoi(text.substr(start)));
  return tokens;
}

long long costFuel(std::vector<int>& pos, int compare)
{
  long long totalFuel = 0;
  for (auto& p : pos)
    totalFuel += std::abs(p - compare);

  return totalFuel;
}

long long adventDay07problem12021(std::string fishes)
{
  std::vector<int> horizontalPos = split(fishes,",");
  std::sort(horizontalPos.begin(), horizontalPos.end());

  long long costResultFuel = INT64_MAX;
  int currentNum = 0;
  for (auto& pos : horizontalPos)
  {
    if (currentNum != pos)
    {
      currentNum = pos;
      costResultFuel = std::min(costResultFuel, costFuel(horizontalPos, pos));
    }
  }


  return costResultFuel;
}

long long costFuel2(std::vector<int>& pos, int compare)
{
  long long totalFuel = 0;
  for (auto& p : pos)
  {
    const long diff = std::abs(p - compare);
    totalFuel += (diff * (diff + 1)) / 2;
  }

  return totalFuel;
}

long long adventDay07problem22021(std::string fishes)
{
  std::vector<int> horizontalPos = split(fishes, ",");
  std::sort(horizontalPos.begin(), horizontalPos.end());

  long long costResultFuel = INT64_MAX;
  int currentNum = 0;
  for (int pos = horizontalPos[0]; pos <= horizontalPos[horizontalPos.size()-1]; pos++)
  {
    if (currentNum != pos)
    {
      currentNum = pos;
      costResultFuel = std::min(costResultFuel, costFuel2(horizontalPos, pos));
    }
  }

  return costResultFuel;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  std::string line;
  
  std::getline(infile, line);
  infile.close();

  long long result = (problNumber == 1) ? adventDay07problem12021(line)
                                        : adventDay07problem22021(line);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day07/input01.txt";
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