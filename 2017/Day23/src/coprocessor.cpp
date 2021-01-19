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

#include "duet_asm.h"

long long adventDay23problem12017(std::ifstream& is)
{
  std::vector<program::instr> instr{ std::istream_iterator<program::instr>{is}, {} };

  program prog{ instr };
  prog.set('a', false);

  int mul_count= 0;
  while (true) 
  {
    auto[done, _] = prog.apply();
    if (prog.curr().cmd == "mul")
      ++mul_count;
    if (done)
      break;
  }

  return mul_count;
}

long long adventDay23problem22017(std::ifstream& is)
{
  std::vector<program::instr> instr{ std::istream_iterator<program::instr>{is}, {} };

  auto ip = std::begin(instr);
  while (ip->cmd != "set" || std::get<char>(ip->arg1) != 'e')
    ++ip;
  *ip = { "set", 'g', 'b' };
  *(++ip) = { "mod", 'g', 'd' };
  *(++ip) = { "jnz", 'g', 8L };
  *(++ip) = { "set", 'f', 0L };
  *(++ip) = { "jnz", '1', 11L };
  while (ip->cmd != "set" || std::get<char>(ip->arg1) != 'g' || std::get<char>(ip->arg2) != 'd')
    ++ip;
  *ip = { "sqrt", 'g', 'b' };
  *(++ip) = { "sub", 'g', 'd' };
  (++ip)->cmd = "jgz";

  program prog{ instr };
  prog.set('a', true);
  int mul_count= 0;

  while (true) 
  {
    auto[done, _] = prog.apply();
    if (done)
      break;
  }

  return prog.value('h');
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  //std::string line;
  //
  //std::vector<std::string> input;
  long long result = 0;
  //
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay23problem12017(infile)
                              : adventDay23problem22017(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day23/input23.txt";
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