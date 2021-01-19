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



long long adventDay17problem12017(std::string& input)
{
  int incr = std::stoi(input);

  std::vector<int> buf{ 0 };
  buf.reserve(2017);
  int p= 0;

  for (int n= 1; n <= 2017; ++n) 
  {
    p = ((p + incr) % std::size(buf)) + 1;
    buf.insert(std::begin(buf) + p, n);
  }
    
  return buf[(p + 1) % buf.size()];
}

long long adventDay17problem22017(std::string& input)
{
  int incr = std::stoi(input);

  int afterZero= 0, i= 0;
  for (int n(1); n <= 50'000'000; ++n) 
  {
    while (i + incr + 1 < n)
      i += incr + 1, ++n;
    if (i = (i + incr) % n, i++ == 0)
      afterZero = n;
  }
  
  return afterZero;
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string input = "324";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay17problem12017(input)
                              : adventDay17problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day17/input17.txt";
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