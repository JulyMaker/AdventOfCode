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
#include "game.h"

void process (std::vector<char>& initValues, std::string& line)
{
  //Hit Points : 109  //Damage : 8  //Armor : 2
  const static std::regex PARSE1{ R"(Hit Points: (\d+))"}, PARSE2{ R"(Damage: (\d+))" };
  std::smatch m;

  if (std::regex_match(line, m, PARSE1) || std::regex_match(line, m, PARSE2))
  {
    initValues.push_back((char)std::stoi(m[1].str()));
  }
}

long long adventDay22problem12015(Game& game)
{
  short best = std::numeric_limits <short>::max();
  
  for (int i= 0; i < 5; ++i)
    round(false, game, i, best);

  return best;
}

long long adventDay22problem22015(Game& game)
{
  short best = std::numeric_limits <short>::max();

  for (int i = 0; i < 5; ++i)
    round(true, game, i, best);

  return best;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<char> initValues;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(initValues, line);
  }
  infile.close();

  Game game{ initValues[0], initValues[1]};
  result = (problNumber == 1) ? adventDay22problem12015(game)
                              : adventDay22problem22015(game);

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