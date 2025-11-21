#include <days.h>

struct Coordinate 
{
    int x;
    int y;
    bool isObstacle;

    Coordinate() : x(0), y(0), isObstacle(false) {}
    Coordinate(int _x, int _y, bool _isObstacle) : x(_x), y(_y), isObstacle(_isObstacle) {}
    Coordinate(int _x, int _y, char _c) : x(_x), y(_y), isObstacle(_c == '#' ? isObstacle = true : isObstacle = false) {}
};

struct GuardPosition : public Coordinate 
{
    char direction;

    GuardPosition() {}
    GuardPosition(char c) : direction(c) {}
    GuardPosition(int _x, int _y, char _c) 
    {
        x = _x;
        y = _y;
        direction = _c;
    }

    bool stopCheck(int cols, int rows )
    {
        if (x >= 0 && x < cols && y < rows && y >= 0)
            return true;
        return false;
    }
};

using Grid = std::map<std::pair<int, int>, Coordinate>;
using Visited = std::set<std::pair<int, int>>;
using Dirs = std::map<char, std::pair<int, int>>;

Dirs dirs = { {'^', {0, -1}}, {'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}} };
std::map<char, char> nextDir = { {'^', '>'}, {'>', 'v'}, {'v', '<'}, {'<', '^'} };

uint64_t adventDay06P12025(std::ifstream& input)
{
    uint64_t score = 1;
    
    Grid          grid;
    GuardPosition guardPos;
    
    std::string line;
    int row = 0, cols = 0;
    while (std::getline(input, line)) 
    {
        cols = line.size();
        for (int col = 0; col < cols; ++col) 
        {
            grid[{col, row}] = Coordinate(col, row, line[col]);

            if (line[col] != '.' && line[col] != '#')
              guardPos = GuardPosition(col, row, line[col]);
        }
        ++row;
    }

    Visited visitedPos;
    while (guardPos.stopCheck(cols, row)) 
    {
        auto [dx, dy] = dirs[guardPos.direction];
        int nextX = guardPos.x + dx;
        int nextY = guardPos.y + dy;

        if (grid.find({ nextX, nextY }) != grid.end()) 
        {
            if (!grid[{nextX, nextY}].isObstacle) 
            {
                guardPos.x = nextX;
                guardPos.y = nextY;
            }
            else 
            {
                guardPos.direction = nextDir[guardPos.direction];
                continue;
            }
        }
        else
            break;

        visitedPos.insert(std::make_pair(guardPos.x, guardPos.y));
    }

    score = visitedPos.size();
    return score;
}

using Visited2 = std::set<std::tuple<int, int, char>>;

bool moveGuard(GuardPosition& _guardPos, Grid& _grid, const std::pair<int, int>& _gridSize, Visited2& _visitedPos) 
{
    int cols = _gridSize.first, row = _gridSize.second;
    while (_guardPos.stopCheck(cols, row)) 
    {
        auto [dx, dy] = dirs[_guardPos.direction];
        int nextX = _guardPos.x + dx;
        int nextY = _guardPos.y + dy;
        
        if (_grid.find({ nextX, nextY }) != _grid.end()) 
        {
            if (!_grid[{nextX, nextY}].isObstacle) 
            {
                _guardPos.x = nextX;
                _guardPos.y = nextY;
            }
            else {
                _guardPos.direction = nextDir[_guardPos.direction];
                continue;
            }
        }
        else
            break;

        std::tuple<int, int, char> currentPos = { _guardPos.x, _guardPos.y, _guardPos.direction };
        if (_visitedPos.find(currentPos) != _visitedPos.end())
            return false;


        _visitedPos.insert({ _guardPos.x, _guardPos.y, _guardPos.direction });
    }

    return true;
}

uint64_t adventDay06P22025(std::ifstream& input) // Launch in Release mode
{
    uint64_t score = 0;
   
    Grid          grid;
    GuardPosition guardPos;

    std::string line;
    int row = 0, cols = 0;
    while (std::getline(input, line))
    {
        cols = line.size();
        for (int col = 0; col < cols; ++col)
        {
            grid[{col, row}] = Coordinate(col, row, line[col]);

            if (line[col] != '.' && line[col] != '#')
              guardPos = GuardPosition(col, row, line[col]);
                
        }
        ++row;
    }

    Visited2 visitedPos;

    const GuardPosition auxGuardPos = guardPos;
    std::pair<int, int> gridSize(cols, row);
    moveGuard(guardPos, grid, gridSize, visitedPos);

    Visited notValid;
    // iterate through grid to find infinite loops
    for (const std::tuple<int, int, char>& pos : visitedPos) 
    {
      int x = std::get<0>(pos), y = std::get<1>(pos);

      guardPos = auxGuardPos;
      if (x == guardPos.x && y == guardPos.y) continue;
      if (notValid.find({x,y}) != notValid.end()) continue;

      grid[{x, y}].isObstacle = true;

      Visited2 auxVisited;
      bool isValid = moveGuard(guardPos, grid, gridSize, auxVisited);
      if (!isValid)
      {
          notValid.insert({x,y});
          score++;
      }

      grid[std::make_pair(x, y)].isObstacle = false;
    }

    return score; 
}