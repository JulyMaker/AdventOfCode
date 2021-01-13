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
#include <valarray>
#include "assembunny.h"

long long adventDay12problem12016(std::vector<std::string> instrucc)
{    
  return Assembunny{ instrucc }.set('c', 0).optAdd().optMul().run().get('a');
}

long long adventDay12problem22016(std::vector<std::string> instrucc)
{
  return Assembunny{ instrucc }.set('c', 1).optAdd().optMul().run().get('a');
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> instrucc;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    instrucc.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay12problem12016(instrucc)
                              : adventDay12problem22016(instrucc);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 3)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
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