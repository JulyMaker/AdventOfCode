#include <utils.h>

enum class OBJ { WALL, SAND };

using Point = std::pair<int, int>;
using Map = std::unordered_map<Point, OBJ, PointHash<int, int>>;

Point operator+(Point p1, Point p2)
{
  return {p1.first + p2.first, p1.second + p2.second };
}

void printmap(const Map& gameMapint)
{
  int maxHeight = 0;
  int maxWe = 0;

  for (auto& point : gameMapint)
  {
    maxHeight = std::max(maxHeight, point.first.first);
    maxWe = std::max(maxWe, point.first.second);
  }

  std::vector<std::vector<char>> map(maxWe +1, std::vector<char>(maxHeight +1, ' '));
  for (auto& point : gameMapint)
  {
    char aux = ' ';
    if (point.second == OBJ::WALL) aux = '#';
    if (point.second == OBJ::SAND) aux = 'o';

    map[point.first.second][point.first.first] = aux;
  }

  for (auto& c : map)
  {
    for (auto& s : c)
      std::cout << s;
    std::cout << std::endl;
  }
    
}

void fillWalls(const std::vector<std::string>& in, Map& gameMap, int& maxHeight)
{
  // Map only walls
  for (auto& wall : in)
  {
    std::vector<std::string> pointsPair = splitS(wall, " -> ");
    std::vector<int> pointsInt = splitI(pointsPair[0], ",");

    int px = pointsInt[0];
    int py = pointsInt[1];
    maxHeight = std::max(maxHeight, py);
    gameMap[Point(px, py)] = OBJ::WALL;

    for (int i = 1; i < pointsPair.size(); i++)
    {
      pointsInt = splitI(pointsPair[i], ",");

      int x = pointsInt[0];
      int y = pointsInt[1];
      maxHeight = std::max(maxHeight, y);
      gameMap[Point(pointsInt[0], pointsInt[1])] = OBJ::WALL;

      if (px == x) // Vertical wall
      {
        for (int j = std::min(py, y); j <= std::max(py, y); j++)
          gameMap[Point(px, j)] = OBJ::WALL;
      }
      else if (py == y) // Horizontal wall
      {
        for (int j = std::min(px, x); j <= std::max(px, x); j++)
          gameMap[Point(j, py)] = OBJ::WALL;
      }

      px = x;
      py = y;
    }
  }
}

bool fillSand(Map& gameMap, Point point, const int maxHeight, const std::vector<Point>& inc, uint64_t& sand)
{
  if (point.second > maxHeight)
    return false;

  if (gameMap.find(point) != gameMap.end())
    return true;

  bool ok = fillSand(gameMap, point + inc[0], maxHeight, inc, sand) &&
            fillSand(gameMap, point + inc[1], maxHeight, inc, sand) &&
            fillSand(gameMap, point + inc[2], maxHeight, inc, sand);

  if (ok) { gameMap[point] = OBJ::SAND; sand++; }

  return ok;
}

uint64_t adventDay14problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  int maxHeight = 0;
  Map gameMap;

  std::vector<std::string> in = parseInput(input, '\n');
  fillWalls(in, gameMap, maxHeight);
  
  // Map sand
  const std::vector<Point> inc = { {0,1}, {-1, 1}, {1, 1} };
  fillSand(gameMap, Point(500, 0), maxHeight, inc, score);
  //printmap(gameMap);

  return score;
}

bool fillSand2(Map& gameMap, Point point, const int maxHeight, const std::vector<Point>& inc, uint64_t& sand)
{
  if (point.second == maxHeight)
    return true;

  if (gameMap.find(point) != gameMap.end())
    return true;

  bool ok = fillSand2(gameMap, point + inc[0], maxHeight, inc, sand) &&
            fillSand2(gameMap, point + inc[1], maxHeight, inc, sand) &&
            fillSand2(gameMap, point + inc[2], maxHeight, inc, sand);

  if (ok) { gameMap[point] = OBJ::SAND; sand++; }

  return ok;
}

uint64_t adventDay14problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  int maxHeight = 0;
  Map gameMap;

  std::vector<std::string> in = parseInput(input, '\n');
  fillWalls(in, gameMap, maxHeight);

  // Map sand
  const std::vector<Point> inc = { {0,1}, {-1, 1}, {1, 1} };
  fillSand2(gameMap, Point(500, 0), maxHeight + 2, inc, score);
  //printmap(gameMap);

  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "14";

  std::string fileName = DAY_PATH(day);
  //fileName = DAY_EXAMPLE_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay14problem12022(inputFile); break;
    case 2: result = adventDay14problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}