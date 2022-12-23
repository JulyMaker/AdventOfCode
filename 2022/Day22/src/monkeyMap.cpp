#include <utils.h>
#include <cube.h>

// -1: turn left, +1: turn right
enum FACE { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };


int getInt(std::string& s) 
{
  int value = 0;
  int pos = std::min(s.find("R"), s.find("L"));

  if(pos == -1)
  {
    value = stoi(s);
    s.clear();
    return value;
  }

  value = stoi(s.substr(0, pos));
  s = s.substr(pos, s.size());

  return value;
}

Coord getNextPos(const Coord& myPos, const int64_t myFace, const std::vector<Coord>& directions, const std::vector<Coord>& borderCols, const std::vector<Coord>& borderRows)
{
  auto [myPosX, myPosY] = myPos;
  auto [x, y] = myPos + directions[myFace];

  switch (myFace) 
  {
    case FACE::RIGHT:
      if (x > borderRows[myPosY].second) x = borderRows[myPosY].first;
      break;
    case FACE::LEFT:
      if (x < borderRows[myPosY].first)  x = borderRows[myPosY].second;
      break;
    case FACE::DOWN:
      if (y > borderCols[myPosX].second) y = borderCols[myPosX].first;
      break;
    case FACE::UP:
      if (y < borderCols[myPosX].first)  y = borderCols[myPosX].second;
  }

  return {x, y};
}

void fillBorderRows(const std::unordered_map<Coord, char, PointHash<int, int>>& stMap, const int maxRow, const int maxCol, std::vector<Coord>& borderRows)
{
  for (int y = 1; y <= maxRow; y++)
  {
    for (auto x = 1; x <= maxCol; ++x)
    {
      if (stMap.contains({ x, y }))
      {
        const auto minX = x;
        while (stMap.contains({ ++x, y }));

        const auto maxX = x - 1;
        borderRows[y] = { minX, maxX };
        break;
      }
    }
  }
}

void fillBorderCols(const std::unordered_map<Coord, char, PointHash<int, int>>& stMap, const int maxRow, const int maxCol, std::vector<Coord>& borderCols)
{
  for (int x = 1; x <= maxCol; x++)
  {
    for (auto y = 1; y <= maxRow; ++y)
    {
      if (stMap.contains({ x, y }))
      {
        const auto minY = y;
        while (stMap.contains({ x, ++y }));

        const auto maxY = y - 1;
        borderCols[x] = { minY, maxY };
        break;
      }
    }
  }
}

uint64_t adventDay22problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const std::vector<Coord> directions{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

  std::unordered_map<Coord, char, PointHash<int, int>> stMap;
  std::vector<Coord> borderRows; // borderRows[y] = {minX,maxX}
  std::vector<Coord> borderCols; // borderCols[x] = {minY,maxY}

  int64_t maxCol = 0;
  int64_t maxRow = 0;

  std::vector<std::string> grid = parseInput(input, '\n');
  std::string instructions = grid.back(); grid.pop_back();
  for (int64_t row = 1; row <= grid.size(); ++row) 
  {
    int i = 0;
    for (char c : grid[row -1 ]) 
    {
      if (c != ' ') 
      {
        const int64_t col = i + 1;
        stMap[{col, row}] = c;
        maxCol = std::max(maxCol, col);
      }
      i++;
    }
  }
  maxRow = grid.size();

  borderRows.resize(maxRow + 1);
  borderCols.resize(maxCol + 1);

  fillBorderRows(stMap, maxRow, maxCol, borderRows);
  fillBorderCols(stMap, maxRow, maxCol, borderCols);

  Coord myPos{ borderRows[1].first, 1 };
  int64_t myFace = FACE::RIGHT;

  while (!instructions.empty())
  {
    int steps = getInt(instructions);

    for (int i=0; i < steps; i++)
    {
      const Coord nextPos = getNextPos(myPos, myFace, directions, borderCols, borderRows);

      if (stMap[nextPos] == '#') break;

      myPos = nextPos;
    }
 
    if (instructions.empty()) break;

    char turn = instructions[0]; instructions = instructions.substr(1, instructions.size());

    switch (turn) 
    {
      case 'L': myFace = (myFace + 3) % 4;
        break;
      case 'R': myFace = (myFace + 1) % 4;
        break;
    }
  }

 
  score = 1000 * myPos.second + 4 * myPos.first + myFace;

  return score;
}


void solveCubeWormholes(MonkeyMap& map, std::vector<std::string>& in)
{
  Cube cube;
  CubeTools cTools;

  int resolution = cTools.detectResolution(in);
  auto minimapInputLines = cTools.filterMinimapLines(in, resolution);

  MonkeyMap minimap(minimapInputLines, true);

  findNetLocations(cube, minimap, cTools);
  calculateEdgeAnchors(cube, map, resolution);
  setupWormholes(cube, map, resolution, cTools);

  //uncomment to print minimap
  //std::cout << std::endl << minimap.data;
}

uint64_t adventDay22problem22022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<std::string> grid = parseInput(input, '\n');
  std::string instructions = grid.back(); grid.pop_back();

  MonkeyMap map(grid, true);
  Cursor cursor(map);

  solveCubeWormholes(map, grid);


  int value = 0;
  for (auto c : instructions)
  {
    if (c == 'R')
    {
      cursor.move(value);
      cursor.rotate(1);
      value = 0;
    }
    else if (c == 'L')
    {
      cursor.move(value);
      cursor.rotate(-1);
      value = 0;
    }
    else
    {
      value = value * 10 + (c - '0');
    }
  }
  cursor.move(value);

  cursor.drawSelf();

  Coord myPos = map.toPosition(cursor.index);

  score = myPos.second * 1000 + myPos.first * 4 + cursor.direction;

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "22";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay22problem12022(inputFile); break;
    case 2: result = adventDay22problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}