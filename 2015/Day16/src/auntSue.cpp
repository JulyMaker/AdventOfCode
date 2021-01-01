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

using FnType = std::function <bool(int, int)>;
using MapType = std::unordered_map <std::string, std::pair <int, FnType>>;

const static FnType EQ{ std::equal_to <int>{ } }, GT{ std::greater <int>{ } }, LT{ std::less <int>{ } };
const static MapType MAP
{ 
  {
  {"children", {3, EQ}}, {"cats",     {7, GT}}, {"samoyeds", {2, EQ}}, {"pomeranians", {3, LT}}, {"akitas",   {0, EQ}},
  {"vizslas",  {0, EQ}}, {"goldfish", {5, LT}}, {"trees",    {3, GT}}, {"cars",        {2, EQ}}, {"perfumes", {1, EQ}}
  } 
};

bool check(const std::string & key, int val) 
{
  const auto & data = MAP.at(key);
  return (EQ) (val, data.first);
}

bool check2(const std::string & key, int val) 
{
  const auto & data = MAP.at(key);
  return data.second(val, data.first);
}

long long adventDay16problem12015(std::string& line)
{
  const static std::regex SUE{ "Sue (\\d+): (.*)" }, ITEM{ R"((\w+): (\d))" };
  std::smatch m;
  std::smatch m2;

  bool invalid = false;

  if (regex_search(line, m, SUE))
  {  
    std::stringstream lineAux(m[2].str());
    std::string saux;
    while (getline(lineAux, saux, ','))
    {
      if (saux[0] == ' ') saux.erase(saux.begin());

      if (regex_search(saux, m2, ITEM))
      {
        invalid = invalid || !check(m2[1].str(), std::stoi(m2[2].str()));
      }   
    }
      
    if (!invalid)
      return std::stoi(m[1].str());
  }
  
  return -1;
}

long long adventDay16problem22015(std::string& line)
{
  const static std::regex SUE{ "Sue (\\d+): (.*)" }, ITEM{ R"((\w+): (\d))" };
  std::smatch m;
  std::smatch m2;

  bool invalid = false;

  if (regex_search(line, m, SUE))
  {
    std::stringstream lineAux(m[2].str());
    std::string saux;
    while (getline(lineAux, saux, ','))
    {
      if (saux[0] == ' ') saux.erase(saux.begin());

      if (regex_search(saux, m2, ITEM))
      {
        invalid = invalid || !check2(m2[1].str(), std::stoi(m2[2].str()));
      }
    }

    if (!invalid)
      return std::stoi(m[1].str());
  }

  return -1;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    result = (problNumber == 1) ? adventDay16problem12015(line)
                                : adventDay16problem22015(line);

    if (result != -1) break;
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