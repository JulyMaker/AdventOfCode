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
#include <queue>
#include <battle.h>

std::vector<std::string> parseLines(std::ifstream& input)
{
  std::vector<std::string> grid;

  for (std::string line; getline(input, line);)
  {
    if (line != "")
      grid.push_back(line);
  }

  return grid;
}

std::ostream& operator<<(std::ostream& os, const Battle& battle)
{
  for (uint32_t y = 0; y < battle.height; ++y)
  {
    os.write(battle.map + y * battle.width, battle.width);

    std::vector<Actor> acs;
    std::insert_iterator<std::vector<Actor>> itin(acs, acs.begin());
    copy_if(battle.actors.begin(), battle.actors.end(), itin, [=](auto& a)->bool {
      return (a.pos.y == y);
      });

    if (!acs.empty())
    {
      std::sort(acs.begin(), acs.end(), [](auto& a, auto& b)->bool {
        return a.pos.x < b.getPos().x;
        });

      os << "   ";

      for (auto& actor : acs)
      {
        os << actor.race << '(' << actor.hp << ")  ";
      }
    }

    os << '\n';
  }
  return os;
}

int64_t adventDay15problem12018(std::ifstream& input)
{
  std::vector<std::string> grid = parseLines(input);

  Battle battle(grid, 3);

  for (int i = 1; i < 200; ++i)
  {
    //cout << "Before Round " << i << ":\n" << battle << endl;
    if (battle.tick())
    {
      //cout << "Finished after " << i-1 << " complete rounds\n";
      //cout << battle << endl;
      //cout << "                     hp score is " << battle.getscore() << endl;

      return (i - 1) * battle.getScore();
    }
  }

  return -1;
}

int64_t adventDay15problem22018(std::ifstream& input)
{
  std::vector<std::string> grid = parseLines(input);

  for (int elfpower = 3; ; ++elfpower)
  {
    Battle battle(grid, elfpower);

    for (int i = 1; i < 200; ++i)
    {
      //cout << "Before Round " << i << ":\n" << battle << endl;
      bool gameover = battle.tick();
      if (battle.deadElves())
        break;

      if (gameover)
      {
        //cout << "Finished after " << i - 1 << " complete rounds\n";
        //cout << battle << endl;
        //cout << "                     hp score is " << battle.getscore() << ", ELF POWER is " << elfpower << endl;
        return (i - 1) * battle.getScore();
      }
    }
  }

  return -1;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay15problem12018(infile)
                                        : adventDay15problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day15/input15.txt";
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