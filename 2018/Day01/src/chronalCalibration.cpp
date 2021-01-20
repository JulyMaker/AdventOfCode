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
#include <valarray>
#include <thread>
#include <unordered_set>


long long adventDay01problem12018(std::ifstream& is)
{
  std::vector<int> data(std::istream_iterator<int>(is), {});

  return std::accumulate(data.begin(), data.end(),0);
}

long long adventDay01problem22018(std::ifstream& is)
{
  std::vector<long> data(std::istream_iterator<int>(is), {});
  std::set<int> uniq;
  int sum= 0;
  
  while(true) 
  {
    for (int const v : data)
    {
      if (auto[_, u] = uniq.insert(sum += v); !u)
        return sum;
    }  
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  //std::string line;
  //
  //std::vector<std::string> input;
  long long result = 0;
  //
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay01problem12018(infile)
                              : adventDay01problem22018(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day01/input01.txt";
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