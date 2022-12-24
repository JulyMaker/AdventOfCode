#include <utils.h>

using Coord = std::pair<int, int>;

Coord operator+(const Coord& c1, const Coord& c2)
{
  auto [x1, y1] = c1;
  auto [x2, y2] = c2;

  return { x1 + x2, y1 + y2 };
}

const std::vector<Coord> MOVES = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 0, 0 } };


const bool isIn(int min, int val, int max) { return min <= val && val <= max; }
struct Boundaries
{
  int minX, maxX, minY, maxY;

  const bool inside(const Coord& p) const { return isIn(minX, p.first, maxX) && isIn(minY, p.second, maxY); }
};


int reachGoal(const Coord start, const Coord goal, const Boundaries& bound, std::vector<std::vector<Coord>>& dirBliz, const int maxX, const int maxY)
{
  int time = 0;
  std::set<Coord> curr{ start };
  std::set<Coord> next;
  std::set<Coord> blizzards;

  while (!curr.contains(goal))
  {
    blizzards.clear();
    for (Coord& p : dirBliz[0]) { if (++p.second == maxY) p.second = 1;         blizzards.insert(p); }
    for (Coord& p : dirBliz[1]) { if (!--p.second)        p.second = maxY - 1;	blizzards.insert(p); }
    for (Coord& p : dirBliz[2]) { if (!--p.first)         p.first  = maxX - 1;  blizzards.insert(p); }
    for (Coord& p : dirBliz[3]) { if (++p.first == maxX)  p.first  = 1;         blizzards.insert(p); }

    for (Coord coord : curr)
      for (auto& delta : MOVES)
        if (Coord newCoord = coord + delta; (bound.inside(newCoord) || newCoord == start || newCoord == goal) && !blizzards.contains(newCoord))
          next.insert(newCoord);

    curr= next;
    next.clear();

    ++time;
  }

  return time;
};

uint64_t adventDay24problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  int maxX = 0, maxY = 0;
  std::vector<std::vector<Coord>> dirBliz = { {}, {}, {}, {} }; // right, left, up, down;
  Coord start, goal;

  std::vector<std::string> in = parseInput(input, '\n');
  for(auto& s : in)
  {
    if (!maxX++)
    {
      start = { 0, (int)s.find('.') };
      maxY = s.size() - 1;
    }
    else
      for (int i = 1; i < s.size() - 1; ++i)
        switch (s[i])
        {
          case '>': dirBliz[0].push_back({ maxX - 1, i }); break;
          case '<': dirBliz[1].push_back({ maxX - 1, i }); break;
          case '^': dirBliz[2].push_back({ maxX - 1, i }); break;
          case 'v': dirBliz[3].push_back({ maxX - 1, i }); break;
          case '.': goal = { maxX - 1, i };
        }
  }

  Boundaries bound = { 1, --maxX - 1, 1, maxY - 1 };

  score = reachGoal(start, goal, bound, dirBliz, maxX, maxY);

  return score;
}

uint64_t adventDay24problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  int maxX = 0, maxY = 0;
  std::vector<std::vector<Coord>> dirBliz = { {}, {}, {}, {} }; // right, left, up, down;
  Coord start, goal;

  std::vector<std::string> in = parseInput(input, '\n');
  for (auto& s : in)
  {
    if (!maxX++)
    {
      start = { 0, (int)s.find('.') };
      maxY = s.size() - 1;
    }
    else
      for (int i = 1; i < s.size() - 1; ++i)
        switch (s[i])
        {
          case '>': dirBliz[0].push_back( {maxX - 1, i} ); break;
          case '<': dirBliz[1].push_back( {maxX - 1, i} ); break;
          case '^': dirBliz[2].push_back( {maxX - 1, i} ); break;
          case 'v': dirBliz[3].push_back( {maxX - 1, i} ); break;
          case '.': goal = { maxX - 1, i };
        }
  }

  Boundaries bound = { 1, --maxX - 1, 1, maxY - 1 };

  score  = reachGoal(start, goal, bound, dirBliz, maxX, maxY);
  score += reachGoal(goal, start, bound, dirBliz, maxX, maxY);
  score += reachGoal(start, goal, bound, dirBliz, maxX, maxY);

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "24";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay24problem12022(inputFile); break;
    case 2: result = adventDay24problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}