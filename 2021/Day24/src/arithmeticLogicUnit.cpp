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

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::vector<std::string> output;
  std::string line;

  std::getline(input, line);
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

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}

int64_t search(std::vector<std::vector<std::vector<std::string>>>& program, bool part1=true)
{
  std::unordered_map<int64_t, int64_t> zValues;
  std::unordered_map<int64_t, int64_t> zValuesNew;
  zValues.insert(std::make_pair(0, 0));

  for (int64_t index = 0; index < 14; index++) 
  {
    int divisors  = std::stoi(program[index][3][2]);   // div z 1
    int offsets   = std::stoi(program[index][4][2]);   // add x offset
    int modifiers = std::stoi(program[index][14][2]);  // add y modifiers

    for (auto z0 : zValues)
    {
      for (int64_t digit = 9; digit > 0; digit--) 
      {
        int64_t candidate = z0.second * 10 + digit;
        int64_t z = z0.first / divisors;

        if (z0.first % 26 + offsets != digit)
          z = z * 26 + digit + modifiers;

        auto [it, flag] = zValuesNew.emplace(z, candidate);

        if (!flag)
        {
          if(part1)
            it->second = std::max(it->second, candidate);
          else
            it->second = std::min(it->second, candidate);
        }    
      }
    }
    zValues = std::move(zValuesNew);
  }

  return zValues[0];
}

uint64_t adventDay24problem12021(std::ifstream& input)
{
  std::vector<std::string> inputIns = parseInput(input);
  std::vector<std::vector<std::vector<std::string>>> program;
  std::vector<std::vector<std::string>> groups;

  for (auto& ins : inputIns)
  {
    if (ins.substr(0, 3) == "inp")
    {
      program.push_back(groups);
      groups.clear();
    }
    else
      groups.push_back(split(ins, " "));
  }
  program.push_back(groups);

  std::pair<int, int> op;
  search(program);

  std::cout << "Highest valid number: " << search(program) << "\n";

  return 0;
}

uint64_t adventDay24problem22021(std::ifstream& input)
{
  std::vector<std::string> inputIns = parseInput(input);
  std::vector<std::vector<std::vector<std::string>>> program;
  std::vector<std::vector<std::string>> groups;

  for (auto& ins : inputIns)
  {
    if (ins.substr(0, 3) == "inp")
    {
      program.push_back(groups);
      groups.clear();
    }
    else
      groups.push_back(split(ins, " "));
  }
  program.push_back(groups);

  std::pair<int, int> op;
  search(program);

  std::cout << "Lowest valid number: " << search(program, false) << "\n";

  return  0;
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay24problem12021(infile)
                                       : adventDay24problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day24/input01.txt";
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