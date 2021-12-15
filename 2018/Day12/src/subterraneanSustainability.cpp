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

using Plants = std::unordered_map<int, bool>;
using Rules = std::unordered_map<std::string, bool>;


void parsePlants(std::ifstream& infile, Plants& plants, Rules& rules)
{
  std::string line;
  std::getline(infile, line);
 
  // First line "initial state"
  {
    const std::regex pat{ "initial state: (.*|#*)" };
    std::smatch match;
    std::regex_search(line, match, pat);
    line = match[1].str();

    for (size_t i{ 0 }; i < line.size(); ++i)
      plants[i] = (line[i] == '#');
  }

  std::string condition;
  char newState;
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      condition = line.substr(0, 5);
      newState = line[line.length() - 1];
      rules[condition] = (newState == '#');
    }
  }
  infile.close();
}

char toPlantChar(bool bol) {
  if (bol == true) return '#';
  else return '.';
}

std::string getRegion(Plants& plants, const int index) 
{
  std::string region = "";
  for (int i = -2; i <= 2; i++) 
    region += toPlantChar(plants[index + i]);

  return region;
}

long long adventDay12problem12018(std::ifstream& infile)
{
  Plants plants = {};
  Rules rules = {};
  parsePlants(infile, plants, rules);

  const int GENERATIONS = 20;
  Plants newPlants;
  for (int i = 0; i < GENERATIONS; i++)
  {
    int minIndex = INT_MAX, maxIndex = INT_MIN;
    for (auto& [num, bol] : plants) 
    {
      if (bol)
      {
        minIndex = std::min(minIndex, num);
        maxIndex = std::max(maxIndex, num);
      }
    }

    newPlants.clear();
    for (int j = minIndex - 2; j <= maxIndex + 2; j++) 
    {
      std::string region = getRegion(plants, j);
      newPlants[j] = rules[region];
    }

    plants = newPlants;
  }

  long sum = 0;
  for (auto& [num, bol] : plants) 
    if (bol) sum += num;

  return sum;
}

long long adventDay12problem22018(std::ifstream& infile)
{
  Plants plants = {};
  Rules rules = {};
  parsePlants(infile, plants, rules);

  const long long GENERATIONS = 50000000000;
  Plants newPlants;
  long long sum =0;

  long prevSum = 0;
  int repeatIndex = 0;
  int repeat = 0;
  long diff = 0;

  for (int i = 0; i < GENERATIONS; i++)
  {
    int minIndex = INT_MAX, maxIndex = INT_MIN;
    for (auto& [num, bol] : plants) 
    {
      if (bol) 
      {
        minIndex = std::min(minIndex, num);
        maxIndex = std::max(maxIndex, num);
      }
    }

    newPlants.clear();
    for (int j = minIndex - 2; j <= maxIndex + 2; j++) 
    {
      std::string region = getRegion(plants, j);
      newPlants[j] = rules[region];
    }

    plants = newPlants;

    /* After 108 iterations, the sum difference is always 65 */
    sum = 0;
    for(auto& [num, bol]: plants) 
      if(bol) sum += num;
    //std::cout << "Iteration " << i << " sum is " << sum << ", difference from previous: " << sum - prevSum << std::endl;
    
    if (diff == sum - prevSum)
    {
      if (repeat++ == 2)
      {
        repeatIndex = i;
        break;
      }
    }
    else
      repeat = 0;
       
    diff = sum - prevSum;
    prevSum = sum;
  }

  sum = 0;
  for (auto& [num, bol] : plants)
    if (bol) sum += num;

  return sum + (GENERATIONS - repeatIndex - 1) * diff;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay12problem12018(infile)
                                        : adventDay12problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day12/input12.txt";
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