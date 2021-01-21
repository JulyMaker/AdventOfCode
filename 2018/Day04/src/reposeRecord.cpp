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

#include "Guard.h"
#include "HashWrapper.h"

struct Sleeper 
{
  Sleeper(int i, int m, int s) : id{ i }, minute{ m }, sleep{ s } { }
  int id = 0;
  int minute = 0;
  int sleep = 0;
};

long long adventDay04problem12018(std::vector<std::string>& input)
{
  auto gsm = map_sleep_data(input);

  auto it = std::max_element(gsm.begin(), gsm.end(),
    [](auto& ga, auto& gb) 
  {
    return ga.second->get_total_sleep() <
      gb.second->get_total_sleep();
  });

  auto& worst_guard = *it->second;

  return worst_guard.get_aoc_answer();
}


long long adventDay04problem22018(std::vector<std::string>& input)
{
  auto gsm = map_sleep_data(input);

  std::vector<Sleeper> vs;

  for (const auto& gp : gsm) 
  {
    auto& p = gp.second;
    auto it = std::max_element(std::begin(p->get_mins()),
      std::end(p->get_mins()));
    auto minute = std::distance(std::begin(p->get_mins()), it);
    vs.emplace_back(Sleeper{ p->get_id(), static_cast<int>(minute), *it });
  }

  auto it = std::max_element(std::begin(vs), std::end(vs),
    [](auto& a, auto& b) {
    return a.sleep < b.sleep;
  });

  auto& reg_sleeper =  *gsm.at(it->id);    // at at at... for const access~!

  return reg_sleeper.get_aoc_answer();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::vector<std::string> input;
  long long result = 0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    input.push_back(line);
  }
  infile.close();

  std::sort(input.begin(), input.end());

  result = (problNumber == 1) ? adventDay04problem12018(input)
                              : adventDay04problem22018(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day04/input04.txt";
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