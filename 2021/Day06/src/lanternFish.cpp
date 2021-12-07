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
#include <deque>

const int FISH = 8;

std::vector<int> split(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(std::stoi(text.substr(start, end - start)));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(std::stoi(text.substr(start)));
  return tokens;
}

long long adventDay06problem12021(std::string fishes)
{
  std::vector<int> fishesNum = split(fishes,",");

  for(int days=80-1; days >= 0; days--)
  {
    int size = fishesNum.size();
    for (int i = 0; i < size; i++)
    {
      if (fishesNum[i] == 0)
      {
        fishesNum.push_back(FISH);
        fishesNum[i] = 6;
      }
      else
      {
        fishesNum[i] -= 1;
      }
    }
  }

  return fishesNum.size();
}


long long adventDay06problem22021(std::string fishes)
{
  std::vector<int> fishesNum = split(fishes, ",");
  std::deque<int64_t> fishesCount(9, 0);

  for(auto& num : fishesNum)
  {
    ++fishesCount[num];
  }

  for (int days = 256 - 1; days >= 0; days--)
  {
    const int64_t parent = fishesCount.front();
    fishesCount.pop_front();
    fishesCount[6] += parent;
    fishesCount.push_back(parent);
  }

  
  return std::accumulate(fishesCount.begin(), fishesCount.end(), int64_t{ 0 });
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  std::string line;
  
  std::getline(infile, line);
  infile.close();

  long long result = (problNumber == 1) ? adventDay06problem12021(line)
                                        : adventDay06problem22021(line);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day06/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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