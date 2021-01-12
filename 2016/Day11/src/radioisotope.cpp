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

long long adventDay11problem12016(std::string& line, int& floorFactor)
{   
  static const std::regex RE{ " a " };

  return 2 * floorFactor-- * std::distance(std::sregex_iterator(line.begin(), line.end(), RE), {});
}

long long adventDay11problem22016(std::string& line, int& floorFactor)
{
  static const std::regex RE{ " a " };

  return 2 * floorFactor-- * std::distance(std::sregex_iterator(line.begin(), line.end(), RE), {});;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int floorFactor = 3;
  long long result = -9;
  if (problNumber == 2) result = 15;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    result += (problNumber == 1) ? adventDay11problem12016(line, floorFactor)
                                 : adventDay11problem22016(line, floorFactor);
  }
  infile.close();

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