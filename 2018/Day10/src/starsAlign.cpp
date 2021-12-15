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

struct Position { int row{ 0 }, col{ 0 }; };
struct Velocity { int row{ 0 }, col{ 0 }; };
struct Light { Position pos; Velocity speed; };

using Lights = std::vector< Light >;
using Aligned = std::vector< int >; // unique alignments of row/col per tick
using Unique = std::unordered_set< int >;
bool operator==(const Position& lhs, const Position& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; }
struct Cmp { size_t operator()(const Position& pos) const { return pos.row * 10000 + pos.col; } };
using Message = std::unordered_set< Position, Cmp >;

struct Answer
{
  Lights lights;
  int tick{ 0 }, minRow{ 0 }, maxRow{ 0 }, minCol{ 0 }, maxCol{ 0 };
};

void parse(std::ifstream& infile, Lights& lights)
{
  std::string line;
  const std::regex pat{ "^position=<\\s*(-?\\d+),\\s*(-?\\d+)\\s*>\\s*velocity=<\\s*(-?\\d+),\\s*(-?\\d+)\\s*>$" };

  std::smatch match;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line != "")
    {
      std::regex_search(line, match, pat);

      Position pos{ std::stoi(match[1].str()), std::stoi(match[2].str()) };
      Velocity speed{ std::stoi(match[3].str()), std::stoi(match[4].str()) };

      lights.emplace_back(std::move(Light{ pos,speed }));
    }
  }
  infile.close();
}

Answer getMaxAligned(std::ifstream& infile)
{
  int row = 0, col = 0, minTick = 0, minRow = 0, maxRow = 0, minCol = 0, maxCol = 0;
  int minUnaligned = std::numeric_limits<int>::max();

  Lights lights = {}; 
  Lights alignedLights = {};
  Aligned unaligned = {};
  Answer ans = {};

  parse(infile, lights);

  for (auto tick{ 0 }; tick < 20000; ++tick)
  {
    auto uniqueTotal{ 0 }; 
    Unique uniqueRow, uniqueCol;

    for (const auto& light : lights)
    {
      uniqueRow.insert(light.pos.row);
      uniqueCol.insert(light.pos.col);
    }
      
    unaligned.push_back(uniqueRow.size() + uniqueCol.size());
    int unalignedCount = *min_element(unaligned.cbegin(), unaligned.cend());

    if (minUnaligned > unalignedCount)
    {
      minUnaligned = unalignedCount;
      ans.lights = lights;
      ans.tick = tick;
      auto [minRowIt, maxRowIt] = minmax_element(uniqueRow.cbegin(), uniqueRow.cend());
      auto [minColIt, maxColIt] = minmax_element(uniqueCol.cbegin(), uniqueCol.cend());
      ans.minRow = *minRowIt, ans.maxRow = *maxRowIt;
      ans.minCol = *minColIt, ans.maxCol = *maxColIt;
    }

    for (auto& light : lights)
    {
      light.pos.row += light.speed.row;
      light.pos.col += light.speed.col;
    }     
  }

  return ans;
}

long long adventDay10problem12018(std::ifstream& is)
{
  auto ans{ getMaxAligned(is) };

  Message message;
  for (const auto& light : ans.lights)
    message.insert(light.pos);

  std::cout << std::endl << std::endl << "Wait for " << ans.tick << " seconds:" << std::endl << std::endl;
  for (auto j{ ans.minCol }; j <= ans.maxCol; ++j, std::cout << std::endl)
    for (auto i{ ans.minRow }; i <= ans.maxRow; ++i) 
      std::cout << ((message.find({ i, j }) == message.end()) ? '.' : '#');

  return 0;
}

/*
#...#..###
#...#...#.
#...#...#.
#####...#.
#...#...#.
#...#...#.
#...#...#.
#...#..###
*/

/*
Wait for 10054 seconds:
######.....###..######..######....##......##....#####...######
#...........#........#..#........#..#....#..#...#....#..#.....
#...........#........#..#.......#....#..#....#..#....#..#.....
#...........#.......#...#.......#....#..#....#..#....#..#.....
#####.......#......#....#####...#....#..#....#..#####...#####.
#...........#.....#.....#.......######..######..#.......#.....
#...........#....#......#.......#....#..#....#..#.......#.....
#.......#...#...#.......#.......#....#..#....#..#.......#.....
#.......#...#...#.......#.......#....#..#....#..#.......#.....
######...###....######..######..#....#..#....#..#.......######
*/

long long adventDay10problem22018(std::ifstream& is)
{
  auto ans{ getMaxAligned(is) };

  return ans.tick;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay10problem12018(infile)
                                        : adventDay10problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day10/input10.txt";
  int problem = 1;

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