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
#include <iterator>
#include <thread>

#include "duet_asm.h"


long long adventDay18problem12017(std::ifstream& is)
{
  std::vector<program::instr> inst{ std::istream_iterator<program::instr>{is}, {} };
  auto result = [aux = inst]() mutable 
  {
      program p0 = program{aux};
      while (true) 
      {
        auto[fin, val] = p0.apply();
        if (val)
          return static_cast<int>(val.value());
      } 
  }();

  return result;
}

long long adventDay18problem22017(std::ifstream& is)
{
  std::vector<program::instr> inst{ std::istream_iterator<program::instr>{is}, {} };

  auto result = [aux = inst]() mutable
  {
    program p0 = program{ aux };
    program p1 = program{ aux, 1 };

    std::thread{ &program::run, &p0, &p1 }.detach();
    std::thread{ &program::run, &p1, &p0 }.detach();
    while (!p0.deadlock() || !p1.deadlock());

    return p1.send_count();
  }();

  return result;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<program::instr> inst;
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  process(inst, line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay18problem12017(infile)
                              : adventDay18problem22017(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day18/input18.txt";
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