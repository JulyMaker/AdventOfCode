#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <valarray>
#include <functional>
#include <numeric>
#include <array>

uint64_t modExp(uint64_t e, uint64_t b = 252533, uint64_t m = 33554393) 
{
  uint64_t r, x= 1;

  while (e != 0) 
  {
    r = e % 2;
    e /= 2;

    if (r == 1)
      x = (x * b) % m;
    b = (b * b) % m;
  }
  return x;
}


long long adventDay24problem12015(std::string& line)
{
  const std::regex PARSE{ R"(.*row (\d+), column (\d+).*)" };
  std::smatch m;

  if (std::regex_match(line, m, PARSE))
  {
    int r = std::stoi(m[1].str());
    int c = std::stoi(m[2].str());
    int target = (r + c - 1) * (r + c - 2) / 2 + c - 1;


    return (20151125 * modExp(target) % 33554393);
  }
  
  return 0;
}

long long adventDay24problem22015()
{
  std::cout << "Happy Advent of Code :)" << std::endl;

  return 0;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<int> nums;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;

    if (line == "") continue;

    result = (problNumber == 1) ? adventDay24problem12015(line)
                                : adventDay24problem22015();
  }
  infile.close();

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain txt path
  if (argc < 3)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The problem number isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}