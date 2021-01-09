#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <valarray>
#include <functional>
#include <numeric>
#include <array>

using Inst = std::pair <int, std::function <void()>>;
using Ptr = std::vector <Inst>::const_iterator;

enum class IN { HLF, TPL, INC, JMP, JIE, JIO};

long long adventDay23problem12015(std::vector<std::string>& initInstrucc, int aValue)
{
  const static std::regex PARSE{ R"((\w+) (a|b|[-+\d]+)(, ([-+\d]+))?)" };
  std::smatch m;

  int a = aValue;
  int b = 0;

  auto getRef = [&](auto && s) -> int & { return (s == "a") ? a : b; };

  std::vector <Inst> instrucc;
  Ptr pc;
  std::unordered_map<std::string, IN> const table = { {"hlf",IN::HLF}, {"tpl",IN::TPL}, {"inc",IN::INC}
                                                    , {"jmp",IN::JMP}, {"jie",IN::JIE}, {"jio",IN::JIO}};
  
    std::transform(initInstrucc.begin(), initInstrucc.end(), std::back_inserter(instrucc), [&](std::string line)->Inst
    {
      if (std::regex_match(line, m, PARSE))
      {
        int & ref = getRef(m[2].str());
        auto it = table.find(m[1].str());

        switch (it->second)
        {
          case IN::HLF: return { 0, [&] { ref /= 2, ++pc; } };
          case IN::TPL: return { 0, [&] { ref *= 3, ++pc; } };
          case IN::INC: return { 0, [&] { ++ref, ++pc; } };
          case IN::JMP: return { std::stoi(m[2].str()), [&] { pc += pc->first; } };
          case IN::JIE: return { std::stoi(m[4].str()), [&] { pc += (ref & 1) ? 1 : pc->first; } };
          case IN::JIO: return { std::stoi(m[4].str()), [&] { pc += (ref == 1) ? pc->first : 1; } };
          default: return { };
        }
      }

    });
  
  
  for (pc = instrucc.begin(); pc != instrucc.end(); pc->second());

  return b;
}

long long adventDay23problem22015(std::vector<std::string>& initInstrucc, int aValue)
{
  return adventDay23problem12015(initInstrucc, aValue);
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> initInstrucc;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;

    if (line == "") continue;

    initInstrucc.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay23problem12015(initInstrucc, 0)
                              : adventDay23problem22015(initInstrucc, 1);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain txt path
  if (argc < 3)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The problem number isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}