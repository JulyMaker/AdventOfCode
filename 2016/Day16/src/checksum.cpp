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

size_t dragon_parity(size_t n)
{
  size_t gray{ n ^ (n >> 1) };
  return (gray ^ __popcnt64(n & gray)) & 1;
}

size_t parity(const std::string& input)
{
  auto   in{ input.data() };
  size_t input_parity= 0;

  for (size_t i= 0, j = input.size() * 2; i < j; ++in, ++i, --j)
    input_parity ^= (static_cast<size_t>(*in & 1) << (i + 1)) ^ (static_cast<size_t>((*in & 1) ^ 1) << j);

  for (size_t i{ 1 }; i < 64; i <<= 1)
    input_parity ^= input_parity << i;

  return input_parity;
}

std::string dragon(const std::string& input, size_t disk_size)
{
  std::string out;
  const size_t LEN{ input.size() };
  const size_t INCR{ disk_size & -disk_size };
  size_t par{ parity(input) };
  size_t prev= 0;

  for (size_t length{ INCR }; length <= disk_size; length += INCR) 
  {
    size_t dragons{ length / (LEN + 1) };
    size_t p{ 1 & (dragon_parity(dragons) ^ (((length - dragons) / (LEN << 1)) & LEN) ^ (par >> ((length - dragons) % (LEN << 1)))) };
    out.push_back("10"[p ^ prev]);
    prev = p;
  }
  return out;
}

long long adventDay16problem12016(std::string input)
{    
  const size_t LIM= 272U;
  std::string result = dragon(input, LIM);

  std::cout << "Result: " << result << std::endl;
  return 0;
}

long long adventDay16problem22016(std::string input)
{
  const size_t LIM = 35651584U;

  std::string result = dragon(input, LIM);

  std::cout << "Result: " << result << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string input="11110010111001001";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay16problem12016(input)
                              : adventDay16problem22016(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 2)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[1]))
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