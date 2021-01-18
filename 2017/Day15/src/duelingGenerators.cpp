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

static std::regex const LINE{ R"(Generator . starts with (\d+))", std::regex::optimize };

template <typename Generator>
auto gen(int init, int mask) 
{
  return[=, r = Generator(init)]() mutable 
  {
    decltype(r()) i;
    do i = r(); while (i & mask);
    return i;
  };
}

long long adventDay15problem12017(std::vector<std::string>& input)
{
  auto parse = [](std::string line) {
    std::smatch m;
    std::regex_match(line, m, LINE);
    return std::stoi(m.str(1));
  };

  auto A = gen<std::minstd_rand0>(parse(input[0]), 0b0);
  auto B = gen<std::minstd_rand>(parse(input[1]),  0b0);

  int N{ 40'000'000 };
  int count= 0;
  while (N--)
  {
    if ((A() & 0xFFFF) == (B() & 0xFFFF))
      ++count;
  }

  return count;
}

long long adventDay15problem22017(std::vector<std::string>& input)
{
  auto parse = [](std::string line) {
    std::smatch m;
    std::regex_match(line, m, LINE);
    return std::stoi(m.str(1));
  };

  auto A = gen<std::minstd_rand0>(parse(input[0]), 0b11);
  auto B = gen<std::minstd_rand>(parse(input[1]), 0b111);

  int N= 5'000'000;
  int count = 0;
  while (N--)
  {
    if ((A() & 0xFFFF) == (B() & 0xFFFF))
      ++count;
  }

  return count;
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

  result = (problNumber == 1) ? adventDay15problem12017(input)
                              : adventDay15problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day15/input15.txt";
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