#include <days.h>

struct Point
{
    int64_t x, y;

    Point operator+(Point p2)
    {
        return { x + p2.x, y + p2.y };
    }
    Point operator+(Point p2) const
    {
        return { x + p2.x, y + p2.y };
    }

    bool operator==(Point p2)
    {
        return (x == p2.x) && (y == p2.y);
    }
    bool operator==(const Point p2) const
    {
        return (x == p2.x) && (y == p2.y);
    }

    bool operator<(const Point& p2)
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }

    const bool operator<(const Point& p2) const
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }
};

using Dirs = std::map<char, Point>;
Dirs dirs = { {'<', {0, -1}}, {'v', {1, 0}}, {'>', {0, 1}}, {'^', {-1, 0}} };
using Coordinates = std::vector<Point>;

template <typename T> struct Map
{
    std::vector<T> data;
    int64_t width;
    int64_t height;
    T const empty;
    T outside;

    constexpr Map(int64_t const width, int64_t const height, T const value = T{}, T const empty = T{}) 
        : width(width), height(height), empty(empty)
    {
        data.resize(width * height, value);
    }

    constexpr bool validPos(Point const& pos) const 
    { 
        return validPos(pos.x, pos.y); 
    }
    constexpr bool validPos(int64_t const x, int64_t const y) const 
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    constexpr size_t index(Point const& pos) const 
    { 
        return index(pos.x, pos.y); 
    }
    constexpr size_t index(int64_t const x, int64_t const y) const 
    {
        return static_cast<size_t>(x + y * width);
    }

    constexpr T const& operator[](Point const p) const 
    {
        if (!validPos(p))
           return empty;
 
        return data[index(p)];
    }
    constexpr T& operator[](Point const p) 
    {
        if (!validPos(p))
            return outside = empty;

        return data[index(p)];
    }
};

struct BfsEntry
{
    Point pos;
    int len;
};

auto bfs(const Map<char>& map, const Point start, const Point goal)
{
    std::queue<BfsEntry> frontier;
    std::set<Point> visited;
    auto enqueue = [&map, &frontier, &visited](auto const pos, auto const len)
    {
        if (map[pos] == ' ')
        {
            if (!visited.contains(pos))
            {
                frontier.emplace(pos, len);
                visited.insert(pos);
            }
        }
    };

    auto dequeue = [&frontier]()
    {
        auto const pos = frontier.front();
        frontier.pop();
        return pos;
    };

    enqueue(start, 0);
    while (!frontier.empty())
    {
        auto const [pos, len] = dequeue();
        if (pos == goal)
            return len;

        for (auto const& dir : dirs)
            enqueue(pos + dirs[dir.first], len + 1);
    }

    return -1;
}

uint64_t adventDay18P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    Coordinates coordinates;
    for (auto& line : in)
    {
        std::vector<int64_t> coords= splitUInt64(line, ",");
        coordinates.emplace_back(coords[0], coords[1]);
    }
   
    Point goal;
    int64_t initSize;
    const Point start = { 0, 0 };
    if (coordinates.size() < 100) // Example
    {
        goal = { 6, 6 };
        initSize = 12;
    }
    else                 // Problem 
    {
        goal = { 70, 70 };
        initSize = 1024;
    }

    Map<char> map(goal.x + 1, goal.y + 1, ' ', '#');
    for (auto const point : coordinates | std::views::take(initSize))
    {
        map[point] = '&';
    }

    score = bfs(map, start, goal);

    return score;
}

auto const timePenalty = int64_t{ 20000 };
using std::views::iota;

struct DfsEntry 
{
    Point pos;
    int64_t level;
    int64_t cost;

    auto operator<=>(DfsEntry const& other) const { return other.cost <=> cost; }
};

uint64_t findNoPath(Map<int64_t> const& map, Point const start, auto const toplevel, Point const goal)
{
    std::priority_queue<DfsEntry> frontier;
    std::set<Point> visited;
    auto enqueue = [&map, &frontier, &visited](auto const pos, auto const level, auto const cost,
        bool const force = false) 
    {
            if (map[pos] > level) 
            {
                if (force || !visited.contains(pos)) 
                {
                    frontier.emplace(pos, level, cost);
                    visited.insert(pos);
                }
            }
    };

    auto dequeue = [&frontier]() 
    {
        auto const elem = frontier.top();
        frontier.pop();
        return elem;
    };

    enqueue(start, toplevel, 0);
    while (!frontier.empty()) 
    {
        auto const [pos, level, cost] = dequeue();
        if (pos == goal)
            return level;

        for (auto const& dir : dirs)
            enqueue(pos + dirs[dir.first], level, cost + 1);

        enqueue(pos, level - 1, cost + timePenalty, true);
    }

    return -1l;
}

uint64_t adventDay18P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    Coordinates coordinates;
    for (auto& line : in)
    {
        std::vector<int64_t> coords = splitUInt64(line, ",");
        coordinates.emplace_back(coords[0], coords[1]);
    }

    Point goal;
    int64_t initSize;
    const Point start = { 0, 0 };
    if (coordinates.size() < 100) // Example
    {
        goal = { 6, 6 };
        initSize = 12;
    }
    else                 // Problem 
    {
        goal = { 70, 70 };
        initSize = 1024;
    }

    Map<int64_t> map(goal.x + 1, goal.y + 1, timePenalty, 0);
    for (auto const clock : iota(int64_t{ 0 }, static_cast<int64_t>(coordinates.size()))) 
    {
        auto const& badAccess = coordinates[clock];
        map[badAccess] = clock + 1;
    }

    score = findNoPath(map, start, static_cast<int64_t>(coordinates.size()) + 1, goal);

    std::cout <<"Answer is: "<< coordinates[score].x << "," << coordinates[score].y << std::endl;

    return score;
}