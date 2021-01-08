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

struct Item { int cost= 0, damage= 0, armor= 0; };
struct Player { int hitpoint= 100, damage= 0, armor= 0; };
const static std::array <Item, 5> WEAPONS{ {{8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}} };
const static std::array <Item, 6> ARMOR{ {{13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5}} };
const static std::array <Item, 7> RINGS{ {{25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, {80, 0, 3}} };

void process (std::vector<int>& initValues, std::string& line)
{
  //Hit Points : 109  //Damage : 8  //Armor : 2
  const static std::regex PARSE1{ R"(Hit Points: (\d+))"}, PARSE2{ R"(Damage: (\d+))" }, PARSE3{ R"(Armor: (\d+))" };
  std::smatch m;

  if (std::regex_match(line, m, PARSE1) || std::regex_match(line, m, PARSE2) || std::regex_match(line, m, PARSE3))
  {
    initValues.push_back(std::stoi(m[1].str()));
  }
}


long long adventDay21problem12015(Player& boss)
{
  int minCost = 746;
  int maxCost = 0;

  for (auto && w : WEAPONS)
    for (auto && a : ARMOR)
      for (auto && r1 : RINGS)
        for (auto && r2 : RINGS)
          if (r1.cost != r2.cost || r1.cost == 0) {
            if (boss.hitpoint * std::max(1, boss.damage - (w.armor + a.armor + r1.armor + r2.armor)) 
                <= 100 * std::max(1, (w.damage + a.damage + r1.damage + r2.damage) - boss.armor))
              minCost = std::min(minCost, w.cost + a.cost + r1.cost + r2.cost);
            else
              maxCost = std::max(maxCost, w.cost + a.cost + r1.cost + r2.cost);
          }

  return minCost;
}

long long adventDay21problem22015(Player& boss)
{
  int minCost = 746;
  int maxCost = 0;

  for (auto && w : WEAPONS)
    for (auto && a : ARMOR)
      for (auto && r1 : RINGS)
        for (auto && r2 : RINGS)
          if (r1.cost != r2.cost || r1.cost == 0) {
            if (boss.hitpoint * std::max(1, boss.damage - (w.armor + a.armor + r1.armor + r2.armor))
              <= 100 * std::max(1, (w.damage + a.damage + r1.damage + r2.damage) - boss.armor))
              minCost = std::min(minCost, w.cost + a.cost + r1.cost + r2.cost);
            else
              maxCost = std::max(maxCost, w.cost + a.cost + r1.cost + r2.cost);
          }

  return maxCost;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<int> initValues;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(initValues, line);
  }
  infile.close();

  Player boss{ initValues[0], initValues[1], initValues[2] };
  result = (problNumber == 1) ? adventDay21problem12015(boss)
                              : adventDay21problem22015(boss);

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