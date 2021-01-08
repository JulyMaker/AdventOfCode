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


long adventDay20problem12015(std::string& input)
{
  static std::array <int, 1000000> points;

  int sum = std::stoi(input);
  int weight = 10;

  for (int elf =1; elf <= points.size(); ++elf) 
  {
    for (int h = elf - 1; h < points.size(); h += elf)
    {
      points[h] += elf * weight;
    }
      
    if (points[elf - 1] >= sum)
      return elf;
  }

  return 0;
}

long long adventDay20problem22015(std::string& input)
{
  static std::array <int, 1000000> points;

  int sum = std::stoi(input);
  int weight = 11;

  for (int elf = 1; elf <= points.size(); ++elf)
  {
    for (int h = elf - 1; h < points.size() && h < elf * 50; h += elf)
    {
      points[h] += elf * weight;
    }

    if (points[elf - 1] >= sum)
      return elf;
  }

  return 0;
}

long long readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;
  
  std::string input = "33100000";

  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  //infile >> line;
  //
  //  if (line == "") continue;
  // 
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay20problem12015(input)
                              : adventDay20problem22015(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain txt path
  if (argc < 2)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long result = 0;
  switch (std::stoi(argv[1]))
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