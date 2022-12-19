#include <utils.h>

using Coord  = std::tuple<int, int, int>;
using Coords = std::set<Coord>;

const std::array<Coord, 6> directions = {
        Coord{0,  0,  1},
        Coord{0,  0, -1},
        Coord{0,  1,  0},
        Coord{0, -1,  0},
        Coord{1,  0,  0},
        Coord{-1, 0,  0},
};

Coord operator+(const Coord& c1, const Coord& c2)
{
  auto [x, y, z] = c1;
  auto [x2, y2, z2] = c2;

  return {x + x2, y + y2, z + z2};
}

void operator--(Coord& c)
{
  get<0>(c)--;
  get<1>(c)--;
  get<2>(c)--;
}

void operator++(Coord& c)
{
  get<0>(c)++;
  get<1>(c)++;
  get<2>(c)++;
}

int& get(Coord& c, int i)
{
  switch (i)
  {
  case 0: return std::get<0>(c);
  case 1: return std::get<1>(c);
  case 2: return std::get<2>(c);
  }
}

uint64_t adventDay18problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  Coords coords;

  std::vector<std::string> in = parseInput(input, '\n');
  for (auto& s : in)
  {
    std::vector<int> c = splitI(s, ",");
    coords.insert({c[0], c[1], c[2]});
  }


  for (auto& coord : coords) 
  {
    for (auto& dir : directions)
    {
      Coord candidate = coord + dir;

      if (coords.find(candidate) == coords.end())
        score++;
    }
  }

  return score;
}


uint64_t adventDay18problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  Coords coords;

  std::vector<std::string> in = parseInput(input, '\n');
  for (auto& s : in)
  {
    std::vector<int> c = splitI(s, ",");
    coords.insert({ c[0], c[1], c[2] });
  }

  Coord boxMin(INT_MAX, INT_MAX, INT_MAX), boxMax(INT_MIN, INT_MIN, INT_MIN);
  for (auto c : coords)
  {
    for (int axis = 0; axis < 3; axis++) 
    {
      get(boxMin, axis) = std::min(get(boxMin,axis), get(c, axis));
      get(boxMax, axis) = std::max(get(boxMax,axis), get(c, axis));
    }
  }

  --boxMin;
  ++boxMax;
 
  std::queue<Coord> stack;
  std::set<Coord> visited;
 
  stack.push(boxMin);

  while (!stack.empty())
  {
    auto current = stack.front(); stack.pop();

    if (visited.find(current) != visited.end()) continue;

    visited.insert(current);

    for (auto& d : directions)
    {
      Coord candidate = current + d;

      if (coords.find(candidate) != coords.end()) score++;

      if (coords.count(candidate) == 0 && visited.count(candidate) == 0)
      {
        auto [x, y, z] = candidate;
        auto [minX, minY, minZ] = boxMin;
        auto [maxX, maxY, maxZ] = boxMax;
        
        if ((minX <= x && x <= maxX) && (minY <= y && y <= maxY) && (minZ <= z && z <= maxZ))
          stack.push(candidate);

      }
    }
  }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "18";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay18problem12022(inputFile); break;
    case 2: result = adventDay18problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}