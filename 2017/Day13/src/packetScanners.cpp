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

using Pair = std::pair<int, int>;

auto invalid(int delay = 0) 
{
  return [delay](auto const & p) 
  {
    auto[layer, range] = p;
    return (delay + layer) % ((range - 1) * 2) == 0;
  };
}

long long adventDay13problem12017(std::vector<std::string>& input)
{
  std::vector<Pair> scan;
  for (auto& line : input)
  {
    std::istringstream iss(line);
    for (int layer, range; (iss >> layer).ignore(1, ':') >> range; )
      scan.emplace_back(layer, range);
  }

  int sev= 0;
  auto bad = invalid();

  for (auto const & p : scan)
    if (bad(p))
      sev += p.first * p.second;

  return sev;
}

template <unsigned int I, typename TupleLike>
struct View 
{
  std::tuple_element_t<I, TupleLike> val;
  View(TupleLike v) : val(std::get<I>(v)) {}
  bool operator<(const View &o) const { return val < o.val; }
};

long long adventDay13problem22017(std::vector<std::string>& input)
{
  std::vector<Pair> scan;
  for (auto& line : input)
  {
    std::istringstream iss(line);
    for (int layer, range; (iss >> layer).ignore(1, ':') >> range; )
      scan.emplace_back(layer, range);
  }

  int delay= 0;
  std::sort(std::begin(scan), std::end(scan), std::less<View<1, Pair>>());
  while (std::any_of(std::begin(scan), std::end(scan), invalid(delay)))
    ++delay;
  
  return delay;
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

  result = (problNumber == 1) ? adventDay13problem12017(input)
                              : adventDay13problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day13/input13.txt";
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