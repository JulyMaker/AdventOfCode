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


long long adventDay19problem12016(std::string& input)
{    
  const int ELVES = std::stoi(input);
  const int RESULT= (int)__lzcnt(ELVES); // Counts the number of leading zeros

  return ELVES << (RESULT + 1) >> RESULT | 1;
}

long long adventDay19problem22016(std::string& input)
{
  const int ELVES = std::stoi(input);
  const int RESULT= int(std::pow(3, int(std::log2(ELVES - 1) / std::log2(3))));

  return ELVES - RESULT + std::max(ELVES - 2 * RESULT, 0);
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;
 
  std::string input = "3001330";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  process(input, mask, line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay19problem12016(input)
                              : adventDay19problem22016(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  const int N = 1;
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