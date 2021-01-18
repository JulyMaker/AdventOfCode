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

#define OP(X) { #X, [](int a, int b) { return a X b; } }
#define MOD(TAG, X) { TAG, [](int& a, int b) { return a X b; } }

template <typename V>
using Map = std::unordered_map<std::string, V>;

static Map<bool(*)(int, int)> const cmp{ {OP(== ), OP(!= ), OP(< ), OP(> ), OP(<= ), OP(>= )} };
static Map<int(*)(int&, int)> const apply{ {MOD("inc", +=), MOD("dec", -=)} };


long long adventDay08problem12017(std::vector<std::string>& input)
{
  Map<int> vals;
  std::string var1, inc_dec, var2, op;
  int val1, val2, max= 0;

  for (auto& line : input)
  {
    std::istringstream is(line);
    is >> var1 >> inc_dec >> val1 >> var2 >> var2 >> op >> val2;
      if (cmp.at(op)(vals[var2], val2))
        max = std::max(max, apply.at(inc_dec)(vals[var1], val1));
  }
    
  max = std::max_element(vals.begin(), vals.end(), [](auto a, auto b) { return a.second < b.second; })->second;

  return max;
}

long long adventDay08problem22017(std::vector<std::string>& input)
{
  Map<int> vals;
  std::string var1, inc_dec, var2, op;
  int val1, val2, max = 0;

  for (auto& line : input)
  {
    std::istringstream is(line);
    is >> var1 >> inc_dec >> val1 >> var2 >> var2 >> op >> val2;
      if (cmp.at(op)(vals[var2], val2))
        max = std::max(max, apply.at(inc_dec)(vals[var1], val1));
  }

  return max;
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

  result = (problNumber == 1) ? adventDay08problem12017(input)
                              : adventDay08problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day08/input08.txt";
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