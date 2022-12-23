#include <utils.h>

using Coord = std::pair<int, int>;

Coord operator+(const Coord& c1, const Coord& c2)
{
  auto [x1, y1] = c1;
  auto [x2, y2] = c2;

  return { x1 + x2, y1 + y2 };
}

Coord NW{ -1, -1 };
Coord N {  0, -1 };
Coord NE{  1, -1 };
Coord E {  1,  0 };
Coord W { -1,  0 };
Coord SW{ -1,  1 };
Coord S {  0,  1 };
Coord SE{  1,  1 };

std::vector<Coord> North = { NW, N, NE };
std::vector<Coord> South = { SE, S, SW };
std::vector<Coord> East  = { NE, E, SE };
std::vector<Coord> West  = { SW, W, NW };

const std::vector<std::vector<Coord>> DIR = { North, South, West, East };
auto All = { NE, N, NW, W, SW, S, SE, E };

bool moveRound(std::map<uint64_t, Coord>& elfs, std::set<Coord>& occupied, const uint64_t roundNum)
{
  std::map<Coord, uint64_t> coordCnt;
  std::map<uint64_t, Coord> proposedPos;
  std::set<Coord> newOccupied;

  for (auto& elf : elfs) 
  {
    if (std::none_of(All.begin(), All.end(), [&elf, &occupied](auto& c) { return occupied.contains(elf.second + c); })) {

      newOccupied.insert( elf.second );
      continue;
    }

    bool hasProposed = false;
    for (int idx = 0; idx < 4; ++idx) 
    {
      auto dirs = DIR[(roundNum + idx) % 4];
      if (std::none_of(dirs.begin(), dirs.end(), [&elf, &occupied](auto& c) { return occupied.contains(elf.second + c); })) {

        proposedPos[elf.first] = elf.second + dirs[1];
        coordCnt[elf.second + dirs[1]]++;
        hasProposed = true;
        break;
      }
    }
    if (!hasProposed) newOccupied.insert( elf.second );
  }

  for (auto& proposed : proposedPos) 
  {
    if (coordCnt[proposed.second] == 1) 
    {
      elfs[proposed.first] = proposed.second;
      newOccupied.insert( proposed.second );
    }
    else 
    {
      newOccupied.insert( elfs[proposed.first] );
    }
  }

  occupied = newOccupied;

  return !proposedPos.empty();
}


uint64_t adventDay23problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::map<uint64_t, Coord> elfs;
  std::set<Coord> occupied;

  uint64_t idx = 0;
  uint64_t x = 0;
  uint64_t y = 0;

  std::vector<std::string> in = parseInput(input, '\n');
  for (auto& s : in) 
  {
    x = 0;
    for (char c : s) 
    {
      if (c == '#') 
      {
        elfs[idx] = { x, y };
        occupied.insert( elfs[idx] );
        idx++;
      }
      x++;
    }
    y++;
  }

  for (int i = 0; i < 10; ++i)
    moveRound(elfs, occupied, i);


  int minX = std::numeric_limits<int>::max();
  int maxX = std::numeric_limits<int>::min();
  int minY = std::numeric_limits<int>::max();
  int maxY = std::numeric_limits<int>::min();

  for (auto pos : occupied) 
  {
    minX = std::min(minX, pos.first);
    maxX = std::max(maxX, pos.first);
    minY = std::min(minY, pos.second);
    maxY = std::max(maxY, pos.second);
  }

  score = (maxX - minX + 1) * (maxY - minY + 1) - occupied.size();

  return score;
}

uint64_t adventDay23problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  std::map<uint64_t, Coord> elfs;
  std::set<Coord> occupied;

  uint64_t idx = 0;
  uint64_t x = 0;
  uint64_t y = 0;

  std::vector<std::string> in = parseInput(input, '\n');
  for (auto& s : in)
  {
    x = 0;
    for (char c : s)
    {
      if (c == '#')
      {
        elfs[idx] = { x, y };
        occupied.insert(elfs[idx]);
        idx++;
      }
      x++;
    }
    y++;
  }

  while (moveRound(elfs, occupied, score)) score++;
  
  score++;

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "23";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay23problem12022(inputFile); break;
    case 2: result = adventDay23problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}