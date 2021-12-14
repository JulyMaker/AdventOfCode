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
#include <polymer.h>

using Rules  = std::unordered_map<std::string, char>;
using Rules2 = std::unordered_map<std::array<char, 2>, char>;

void parseRules(std::ifstream& infile, std::string& polymer, Rules& rules)
{
  std::string line;

  std::getline(infile, line);
  polymer = line;
  
  // Read rules
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      rules.try_emplace(line.substr(0, 2), line.back());
    }
  }
  infile.close();
}

std::string applyRules(const std::string& polymer, const Rules& rules) 
{
  std::string new_polymer(1, polymer.front());

  for (int pos = 1; pos < polymer.size(); ++pos) 
  {
    auto rule_it = rules.find(polymer.substr(pos - 1, 2));
    if (rule_it != rules.end()) 
    {
      new_polymer.push_back(rule_it->second);
    }
    new_polymer.push_back(polymer[pos]);
  }
  return new_polymer;
}

long long adventDay14problem12021(std::ifstream& infile)
{
  const int STEPS = 10;

  std::string polymer;
  Rules rules;

  parseRules(infile,polymer, rules);

  for (int i = 0; i < STEPS; ++i)
  {
    polymer = applyRules(polymer, rules);
  }

  std::unordered_map<char, int> counts;
  for (const char element : polymer) 
  {
    ++counts[element];
  }

  auto [min_it, max_it] = std::minmax_element(counts.begin(), counts.end(),
    [](const auto l, const auto r) { return l.second < r.second; });

  return max_it->second - min_it->second;
}

CompressedPolymer parseRules2(std::ifstream& infile, Rules2& rules)
{
  std::string line;

  std::getline(infile, line);
  CompressedPolymer polymer(line);

  // Read rules
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      rules.try_emplace({ line[0], line[1] }, line.back());
    }
  }
  infile.close();

  return polymer;
}

long long adventDay14problem22021(std::ifstream& infile)
{
  const int STEPS = 40;

  Rules2 rules;
  CompressedPolymer polymer = parseRules2(infile, rules);

  for (int i = 0; i < STEPS; ++i)
  {
    polymer = polymer.applyRules(rules);
  }

  return polymer.Score();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay14problem12021(infile)
                                        : adventDay14problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day14/input01.txt";
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