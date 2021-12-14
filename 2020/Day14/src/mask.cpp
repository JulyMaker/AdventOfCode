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


long long adventDay14problem1(std::map<uint64_t, uint64_t>& mem, std::string& mask, std::string& line)
{
  //mask = 0010X01001X010000110100000X000010X11
  //mem[41717] = 288
  std::smatch sm;
  std::regex regExpMask("mask = (\\w+)");
  std::regex regExpMem("mem\\[(\\d+)\\] = (\\d+)");

  if (regex_search(line, sm, regExpMask))
  {
    mask = sm[1].str();
  }

  if (regex_search(line, sm, regExpMem))
  {
    uint64_t num = std::stoull( sm[2].str());

    std::string mskNumber;
    for (uint64_t i =0; i < mask.size(); ++i)
    {
      std::uint64_t maskAux{ (uint64_t)1 << mask.size() - 1 - i };

      if (mask[i] == '1')
      {
        num |= maskAux;
      }
      else if(mask[i] == '0')
      {
        num &= ~maskAux;
      }
    }

    mem[std::stoull(sm[1].str())] = num;
  }

  if(line == "")
  {
    long long sum = 0;
    for (auto& m :mem)
    {
      sum += m.second;
    }
    return sum;
  }

  return 0;
}

long long adventDay14problem2(std::map<uint64_t, uint64_t>& mem, std::string& mask, std::string& line)
{
  //mask = 0010X01001X010000110100000X000010X11
//mem[41717] = 288
  std::smatch sm;
  std::regex regExpMask("mask = (\\w+)");
  std::regex regExpMem("mem\\[(\\d+)\\] = (\\d+)");

  if (regex_search(line, sm, regExpMask))
  {
    mask = sm[1].str();
  }

  if (regex_search(line, sm, regExpMem))
  {
    uint64_t num = std::stoull(sm[1].str());

    std::vector<uint64_t> masks;
    std::string mskNumber;
    for (uint64_t i = 0; i < mask.size(); ++i)
    {
      std::uint64_t maskAux{ (uint64_t)1 << mask.size() - 1 - i };

      if (mask[i] == '1')
      {
        num |= maskAux;
      }else if(mask[i] == 'X')
      {
        masks.push_back(maskAux);
      }
    }

    std::vector<uint64_t> possibles{num};
    std::vector<uint64_t> possiblesAux;
    for (uint64_t i = 0; i < masks.size(); ++i)
    {
      possiblesAux.clear();
      for (auto& p : possibles)
      {
        possiblesAux.push_back(p | masks[i]);
        possiblesAux.push_back(p & ~masks[i]);
      }

      possibles.clear();
      possibles = possiblesAux;
    }
 
    for(auto& m :possibles)
      mem[m] = std::stoull(sm[2].str());
  }

  if (line == "")
  {
    long long sum = 0;
    for (auto& m : mem)
    {
      sum += m.second;
    }
    return sum;
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result = 0;
  std::map<uint64_t, uint64_t> mem;
  std::string mask;

  while (!infile.eof())
  {
    std::getline(infile, line);

    result= (problNumber == 1) ? adventDay14problem1(mem, mask, line)
                               : adventDay14problem2(mem, mask, line);
  }
  infile.close();

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
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

  long long int result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}