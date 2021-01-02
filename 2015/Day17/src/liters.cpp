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

const int TARGET = 150;

long long adventDay17problem12015(std::vector<int>& numbers)
{
  std::sort(numbers.rbegin(), numbers.rend());
  std::array <int, TARGET + 1> ways;
  std::fill(ways.begin(), ways.end(), 0);

  ways[0] = 1;
  for (auto&& num : numbers)
    for (int mem =TARGET; mem >= num; --mem)
      ways[mem] += ways[mem - num];
    
  return ways[TARGET];
}

long long adventDay17problem22015(std::vector<int>& numbers)
{
  std::sort(numbers.rbegin(), numbers.rend());
  std::array <int, TARGET + 1> best, ways;
  std::fill(ways.begin(), ways.end(), 0);
  std::fill(best.begin(), best.end(), std::numeric_limits <int>::max() - 1);

  ways[0] = 1;
  best[0] = 0;

  for (auto&& num : numbers)
    for (int mem = TARGET; mem >= num; --mem)
    {
      if (best[mem - num] + 1 < best[mem])
      {
        best[mem] = best[mem - num] + 1;
        ways[mem] = 0;
      }
        
      if (best[mem - num] + 1 == best[mem])
        ways[mem] += ways[mem - num];
    }
     

  return ways[TARGET];
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::vector <int> numbers;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    numbers.push_back(std::stoi(line)); 
  }
  infile.close();

  result = (problNumber == 1) ? adventDay17problem12015(numbers)
                              : adventDay17problem22015(numbers);

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