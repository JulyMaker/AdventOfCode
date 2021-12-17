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
#include <deque>

int64_t vectorToNum(const std::vector<int>& score)
{
  std::string output; 
  
  for (const auto digit : score) { output.push_back('0' + digit); }
  return strtoll(output.c_str(), NULL, 10);
}

int64_t adventDay14problem12018(std::ifstream& input)
{
  std::string line;
  std::getline(input, line);
  input.close();

  const int PRE{ std::stoi(line) }, CUR{ 10 }, TOTAL{ PRE + CUR }; // input values
  std::vector<int> S = { 3,7 };
  size_t i = 0;
  size_t j = 1;

  for (std::deque<int> next; S.size() < TOTAL; next.clear(), i = (i + S[i] + 1) % S.size(), j = (j + S[j] + 1) % S.size())
  {
    for (auto score(S[i] + S[j]); score > 0; score /= 10)
    {
      next.push_front(score % 10);
    }

    if (next.empty()) // 0 + 0 == 0
      next.push_back(0);

    std::move(next.cbegin(), next.cend(), back_inserter(S));
  }

  std::vector<int> result{ S.cbegin() + PRE, S.cbegin() + TOTAL };
  result.resize(CUR);

  return vectorToNum(result);
}

int64_t adventDay14problem22018(std::ifstream& input)
{
  std::string line;
  std::getline(input, line);
  input.close();

  std::vector<int> scoreboard{ 3, 7 };
  int elves[2] = { 0, 1 };
  int nRecipes = std::stoi(line);

  std::vector<int> match;
  while (nRecipes != 0) 
  {
    match.push_back(nRecipes % 10);
    nRecipes /= 10;
  }
  std::reverse(match.begin(), match.end());

  while (true) 
  {
    int sum = scoreboard[elves[0]] + scoreboard[elves[1]];
    if (sum >= 10) 
    { 
      scoreboard.push_back(1);
      scoreboard.push_back(sum % 10); 
    }
    else 
      scoreboard.push_back(sum);

    if (scoreboard.size() < match.size()) continue;

    if (std::equal(match.begin(), match.end(), scoreboard.end() - match.size()))
    {
      return scoreboard.size() - match.size();
    }
    else if (scoreboard.size() >= match.size() + 1 && std::equal(match.begin(), match.end(), scoreboard.end() - match.size() - 1, scoreboard.end() - 1)) 
    {
      return scoreboard.size() - match.size() - 1;
    }

    elves[0] = (elves[0] + scoreboard[elves[0]] + 1) % scoreboard.size();
    elves[1] = (elves[1] + scoreboard[elves[1]] + 1) % scoreboard.size();
  }

  return 0;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay14problem12018(infile)
                                        : adventDay14problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day14/input14.txt";
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