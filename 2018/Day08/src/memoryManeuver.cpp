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
#include <optional>

long long calculateSum(std::vector<int>& memory, int& index)
{
  if (index >= memory.size()) return 0;

  const int nChild = memory[index], nMetadata = memory[++index];

  std::vector<int> childrenSum;
  int sum = 0;

  for (int i = 0; i < nChild; i++)
    childrenSum.push_back(calculateSum(memory, ++index));

  sum = std::accumulate(childrenSum.begin(), childrenSum.end(), 0);
  
  for (int j = 0; j < nMetadata; j++)
    sum += memory[++index];

  return sum;
}

long long adventDay08problem12018(std::ifstream& is)
{
  std::vector<int> memory(std::istream_iterator<int>(is), {});
  int index = 0;

  return calculateSum(memory, index);
}

long long calculateSum2(std::vector<int>& memory, int& index)
{
  if (index >= memory.size()) return 0;

  const int nChild = memory[index], nMetadata = memory[++index];

  std::vector<int> childrenSum;
  int sum = 0;

  for (int i = 0; i < nChild; i++)
    childrenSum.push_back(calculateSum2(memory, ++index));

  if (nChild == 0) 
  {
    for (int j = 0; j < nMetadata; j++)
      sum += memory[++index];
  }
  else {
    for (int j = 0; j < nMetadata; j++) {
      int metadata = memory[++index];
      if (metadata > nChild) continue;
      sum += childrenSum[metadata - 1];
    }
  }

  return sum;
}

long long adventDay08problem22018(std::ifstream& is)
{

  std::vector<int> memory(std::istream_iterator<int>(is), {});
  int index = 0;

  return calculateSum2(memory, index);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay08problem12018(infile)
                                        : adventDay08problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day08/input08.txt";
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