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
#include "assembunny.h"

static const std::string ZERO_ONE{ "010101010101" };


long long adventDay25problem12016(std::vector<std::string>& input)
{ 
  Assembunny asmb{ input };
  asmb.optAdd().optRemoveInfiniteLoops().setOutputBufferLimit(12);

  for (int a = 0; a < 256; ++a)
  {
    if (asmb.clearOutputBuffer().set('a', a).run().getOuputBuffer() == ZERO_ONE)
      return a;
  }   
}

long long adventDay25problem22016()
{
  std::cout << "Happy Advent of Code 2016 :)" << std::endl;

  return 0;
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

  result = (problNumber == 1) ? adventDay25problem12016(input)
                              : adventDay25problem22016();

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