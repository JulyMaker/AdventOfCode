#include <days.h>

struct Coordi
{
    long long x, y;

    Coordi operator+(const Coordi& b)
    {
        return { x + b.x, y + b.y };
    }

    Coordi operator-(const Coordi& b)
    {
        return { x - b.x, y - b.y };
    }

    Coordi operator*(const long long& b)
    {
        return { x * b, y * b };
    }

    bool operator<(const Coordi& b)
    {
        return (x == b.x) ? y < b.y : x < b.x;
    }

    bool operator!=(const Coordi& b)
    {
        return (x != b.x) || (y != b.y);
    }

    void operator-=(const Coordi& b)
    {
        x -= b.x;
        y -= b.y;
    }

    void operator+=(const Coordi& b)
    {
        x += b.x;
        y += b.y;
    }

};

using GridBase = std::vector<std::string>;

class Map
{
private:
    GridBase grid;

public:
    Map() {}
    Map(const GridBase& g) : grid(g) {}
    Map(const size_t h, const size_t w, char c)
    {
        grid = GridBase(h, std::string(w, c));
    }

    GridBase& getMap() { return grid; }

    char& operator[](const Coordi& coord)
    {
        if (coord.x < 0 || coord.x >= grid.size() || coord.y < 0 || coord.y >= grid[0].size())
            throw std::out_of_range("Coordinate is out of bounds");

        return grid[coord.x][coord.y];
    }

    void push_back(std::string str)
    {
        grid.push_back(str);
    }

    std::vector<Coordi> positions()
    {
        std::vector<Coordi> coord;
        int col = cols();
        int row = rows();

        for (int x = 0; x < col; ++x)
            for (int y = 0; y < row; ++y)
                coord.push_back({ x, y });

        return coord;
    }

    std::vector<Coordi> positions2()
    {
        std::vector<Coordi> coord;
        int col = cols();
        int row = rows();

        for (int x = 0; x < row; ++x)
            for (int y = 0; y < col; ++y)
                coord.push_back({ x, y });

        return coord;
    }

    void print()
    {
        for (auto line : grid)
            std::cout << line << std::endl;
    }

    size_t rows() const { return grid.size(); }
    size_t cols() const { return grid.empty() ? 0 : grid[0].size(); }
};

using Dirs = std::map<char, Coordi>;
Dirs dirs = { {'<', {0, -1}}, {'v', {1, 0}}, {'>', {0, 1}}, {'^', {-1, 0}} };
//Dirs dirs = { {'^', {0, -1}}, {'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}} };
using std::views::reverse;

void moveRobot(Map& map, Coordi& robot, const char move)
{
    const Coordi dir = dirs[move];
    if (dir.y == 0) 
    {
        Coordi next = robot + dir;
        while (map[next] == 'O' or map[next] == '[' or map[next] == ']') 
        {
            next += dir;
        }

        if (map[next] == '#') 
            return;

        if (map[next] == '.') 
        {
            for (auto dest = next; dest != robot; dest -= dir)
                map[dest] = map[dest - dir];

            map[robot] = '.';
            robot += dir;
            return;
        }
    }
    else 
    {
        std::vector<std::pair<std::set<int64_t>, int64_t>> moveset{};
        moveset.emplace_back(std::set<int64_t>{robot.x}, robot.y).first;

        auto row = robot.y;
        while (!moveset.back().first.empty()) 
        {
            row += dir.y;
            auto& cols = moveset.emplace_back(std::set<int64_t>{}, row).first;

            for (auto const x : moveset[moveset.size() - 2].first) 
            {
                switch (map[{x, row}]) {
                  case '#':
                      return;
                  case '.':
                      break;
                  case 'O':
                      cols.insert(x);
                      break;
                  case '[':
                      cols.insert(x);
                      cols.insert(x + 1);
                      break;
                  case ']':
                      cols.insert(x - 1);
                      cols.insert(x);
                      break;
                }
            }
        }
        // move
        for (auto const& [xs, y] : moveset | reverse) 
        {
            for (auto const x : xs) 
            {
                map[{x, y + dir.y}] = map[{x, y}];
                map[{x, y}] = '.';
            }
        }
        robot += dir;
    }
}

uint64_t sumBoxes(Map& map)
{
    uint64_t sum = 0;
    for (Coordi pos : map.positions())
    {
        if (map[pos] == 'O' or map[pos] == '[')
            sum += pos.y + pos.x * 100;
    }
    return sum;
}

uint64_t adventDay15P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    Map map;
    Coordi robot;
    for (auto& line : in)
    {
        if (line[0] == '#')
        {
            map.push_back(line);
            if (auto s = line.find('@'); s != std::string::npos)
            {
                robot = { (long long) map.rows() - 1, (long long)s };
            }
            continue;
        }

        for (char c : line)
           moveRobot(map, robot, c);       
    }

    score = sumBoxes(map);

    return score; // 1550868 Too low
}

Map stretch(Map& map) 
{
   Map doubleMap{ map.rows(), map.cols() * 2, '#'};

    for (auto const pos : map.positions()) 
    {
        switch (map[pos]) 
        {
          case 'O':
              doubleMap[{pos.x, pos.y * 2}] = '[';
              doubleMap[{pos.x, pos.y * 2 + 1}] = ']';
              break;
          case '.':
              doubleMap[{pos.x, pos.y * 2}] = '.';
              doubleMap[{pos.x, pos.y * 2 + 1}] = '.';
              break;
          case '@':
              doubleMap[{pos.x, pos.y * 2}] = '@';
              doubleMap[{pos.x, pos.y * 2 + 1}] = '.';
              break;
        }
    }
    return doubleMap;
}


uint64_t sumBoxes2(Map& map)
{
    uint64_t sum = 0;
    for (Coordi pos : map.positions2())
    {
        if (map[pos] == 'O' or map[pos] == '[')
            sum += pos.x * 100 + pos.y;
    }
    return sum;
}

void moveRobot2(Map& map, Coordi& robot, const char move)
{
    const Coordi dir = dirs[move];
    if (dir.x == 0)
    {
        Coordi next = robot + dir;
        while (map[next] == 'O' or map[next] == '[' or map[next] == ']')
        {
            next += dir;
        }

        if (map[next] == '#')
            return;

        if (map[next] == '.')
        {
            for (auto dest = next; dest != robot; dest -= dir)
                map[dest] = map[dest - dir];

            map[robot] = '.';
            robot += dir;
            return;
        }
    }
    else
    {
        std::vector<std::pair<std::set<int64_t>, int64_t>> moveset{};
        moveset.emplace_back(std::set<int64_t>{robot.y}, robot.x).first;

        auto row = robot.x;
        while (!moveset.back().first.empty())
        {
            row += dir.x;
            auto& cols = moveset.emplace_back(std::set<int64_t>{}, row).first;

            for (auto const x : moveset[moveset.size() - 2].first)
            {
                switch (map[{row, x}]) 
                {
                  case '#':
                      return;
                  case '.':
                      break;
                  case 'O':
                      cols.insert(x);
                      break;
                  case '[':
                      cols.insert(x);
                      cols.insert(x + 1);
                      break;
                  case ']':
                      cols.insert(x - 1);
                      cols.insert(x);
                      break;
                }
            }
        }
        // move
        for (auto const& [ys, x] : moveset | reverse)
        {
            for (auto const y : ys)
            {
                map[{x + dir.x, y}] = map[{x, y}];
                map[{x, y}] = '.';
            }
        }
        robot += dir;
    }
}

uint64_t adventDay15P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    Map map;
    Map doubleMap;
    Coordi robot;
    for (auto& line : in)
    {
        if (line[0] == '#')
        {
            map.push_back(line);
            if (auto s = line.find('@'); s != std::string::npos)
            {
                robot = { (long long)(map.rows() - 1), (long long)s * 2 };
            }
            continue;
        }

        if( doubleMap.getMap().empty()) doubleMap = stretch(map);
        //doubleMap.print();
        for (char c : line)
        {
            moveRobot2(doubleMap, robot, c);
            //std::cout << c << std::endl;
            //doubleMap.print();
        }
            
    }

    
    //doubleMap.print();
    score = sumBoxes2(doubleMap);

    return score;
}