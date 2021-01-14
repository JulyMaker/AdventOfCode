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
#include "uint128_t.h"

inline uint8_t popcnt128(uint128_t val)
{
  return __popcnt64(static_cast<uint64_t>(val >> 64)) + __popcnt64(static_cast<uint64_t>(val)); // __popcnt64 Counts the number of 1 bits(population count)
}

void process(uint128_t& input, uint128_t& mask, std::string line)
{
  for (char c : line)
    input = (input << 1) | (c == '^'), mask = (mask << 1) | 1;
}

long long adventDay18problem12016(uint128_t& input, uint128_t& mask)
{    
  uint64_t count= popcnt128(input);
  uint64_t limit= 40U;

  for (uint64_t i= 1; i < limit; ++i)
    count += popcnt128(input = ((input >> 1) ^ (input << 1)) & mask);

  return (limit * popcnt128(mask)) - count;
}

long long adventDay18problem22016(uint128_t& input, uint128_t& mask)
{
  uint64_t count = popcnt128(input);
  uint64_t limit = 400000U;

  for (uint64_t i = 1; i < limit; ++i)
    count += popcnt128(input = ((input >> 1) ^ (input << 1)) & mask);

  return (limit * popcnt128(mask)) - count;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  uint128_t input = 0;
  uint128_t mask = 0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(input, mask, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay18problem12016(input, mask)
                              : adventDay18problem22016(input, mask);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  const int N = 0;
 if (argc < 3 - N)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2 - N]) < 1) || (std::stoi(argv[2 - N]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2-N]))
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