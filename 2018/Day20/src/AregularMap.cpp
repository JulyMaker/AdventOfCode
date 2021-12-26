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
#include <ctype.h>

using namespace std::string_literals;

struct Room 
{
  std::array<Room*, 4> door;
  Room() : door() { }
  Room(int dir, Room* prev) : door() { door[dir ^ 1] = prev; }

  Room* walk(int dir) 
  {
    if (!door[dir]) 
    {
      door[dir] = new Room(dir, this);
    }

    return door[dir];
  }
};

std::vector<std::string> parseLines(std::ifstream& input)
{
  std::vector<std::string> lines;

  for (std::string line; getline(input, line);)
  {
    if (line != "")
      lines.push_back(line);
  }

  return lines;
}

int64_t adventDay20problem12018(std::ifstream& input)
{
  Room* R0 = new Room();
  std::vector< std::vector<Room*>> S = { {R0} };

  auto TOP   = [&S]() -> auto& { return S.back(); };
  auto SAVED = [&S]() -> auto& { return *(S.rbegin() + 1); };
  auto NEXT  = [&S]() -> auto& { return *(S.rbegin() + 2); };

  std::vector<std::string> inputLines = parseLines(input);

  // Build the map from the regex
  for (auto& ch : inputLines[0]) 
  {
    switch (ch) 
    {
      case 'N': case 'S': case 'E': case 'W':
        ch = "NSEW"s.find(ch);
        for (auto&& room : TOP()) {
          room = room->walk(ch);
        }
        break;
      case '(':
        S.push_back(std::move(TOP()));
        S.push_back(TOP());
        break;
      case '|': case ')':
        NEXT().insert(NEXT().end(), TOP().begin(), TOP().end());
        if (ch == '|') 
        {
          TOP() = SAVED();
        }
        else 
        {
          S.pop_back();
          S.pop_back();
          // deduplicate
          std::sort(TOP().begin(), TOP().end());
          TOP().erase( std::unique(TOP().begin(), TOP().end()),TOP().end());
        }
        break;
    }
  }

  // Breadth-first search to get room counts at each depth
  std::set<Room*> frontier{ R0 }, closed{ R0 }, next;
  std::vector<int> counts;
  while (!frontier.empty()) 
  {
    counts.push_back(closed.size());
    for (auto&& r : frontier) 
    {
      for (auto&& rn : r->door) 
      {
        if (rn && closed.insert(rn).second) 
        {
          next.insert(rn);
        }
      }
    }
    frontier.swap(next);
    next.clear();
  }

  return counts.size() - 1;
}

int64_t adventDay20problem22018(std::ifstream& input)
{
  const size_t DEPTH = 1000;

  Room* R0 = new Room();
  std::vector< std::vector<Room*>> S = { {R0} };

  auto TOP = [&S]() -> auto& { return S.back(); };
  auto SAVED = [&S]() -> auto& { return *(S.rbegin() + 1); };
  auto NEXT = [&S]() -> auto& { return *(S.rbegin() + 2); };

  std::vector<std::string> inputLines = parseLines(input);

  // Build the map from the regex
  for (auto& ch : inputLines[0])
  {
    switch (ch)
    {
    case 'N': case 'S': case 'E': case 'W':
      ch = "NSEW"s.find(ch);
      for (auto&& room : TOP()) {
        room = room->walk(ch);
      }
      break;
    case '(':
      S.push_back(std::move(TOP()));
      S.push_back(TOP());
      break;
    case '|': case ')':
      NEXT().insert(NEXT().end(), TOP().begin(), TOP().end());
      if (ch == '|')
      {
        TOP() = SAVED();
      }
      else
      {
        S.pop_back();
        S.pop_back();
        // deduplicate
        std::sort(TOP().begin(), TOP().end());
        TOP().erase(std::unique(TOP().begin(), TOP().end()), TOP().end());
      }
      break;
    }
  }

  // Breadth-first search to get room counts at each depth
  std::set<Room*> frontier{ R0 }, closed{ R0 }, next;
  std::vector<int> counts;
  while (!frontier.empty())
  {
    counts.push_back(closed.size());
    for (auto&& r : frontier)
    {
      for (auto&& rn : r->door)
      {
        if (rn && closed.insert(rn).second)
        {
          next.insert(rn);
        }
      }
    }
    frontier.swap(next);
    next.clear();
  }

  return (counts.size() < DEPTH) ? 0 : counts.back() - counts[DEPTH - 1];;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay20problem12018(infile)
                                        : adventDay20problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day20/input20.txt";
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