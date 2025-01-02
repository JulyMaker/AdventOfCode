#include <days.h>

using GridBase = std::vector<std::string>;

struct Coord
{
    int64_t x, y;

    Coord operator+(const Coord& b)
    {
        return { x + b.x, y + b.y };
    }

    Coord operator+(Coord& b) const
    {
        return { x + b.x, y + b.y };
    }

    Coord operator-(const Coord& b)
    {
        return { x - b.x, y - b.y };
    }

    Coord operator-(const Coord& b) const 
    {
        return { x - b.x, y - b.y };
    }

    Coord operator*(const long long& b)
    {
        return { x * b, y * b };
    }

    bool operator<(const Coord& b)
    {
        return (x == b.x) ? y < b.y : x < b.x;
    }

    const bool operator<(const Coord& b) const
    {
        return (x == b.x) ? y < b.y : x < b.x;
    }

    bool operator!=(const Coord& b)
    {
        return (x != b.x) || (y != b.y);
    }

    bool operator==(const Coord& b) const
    {
        return (x == b.x) && (y != b.y);
    }

    void operator-=(const Coord& b)
    {
        x -= b.x;
        y -= b.y;
    }

    void operator+=(const Coord& b)
    {
        x += b.x;
        y += b.y;
    }

};

struct Node 
{
    Coord pos;
    char dir;

    bool operator==(Node const& b)
    {
        return (pos == b.pos) && (dir == b.dir);
    }

    bool operator!=(Node const& b)
    {
        return (pos != b.pos) || (dir != b.dir);
    }

    bool operator<(Node const& b) const
    {
        return std::tie(pos, dir) < std::tie(b.pos, b.dir);
    }
};

struct Score 
{
    int64_t score;
    Node node;

    bool operator<(Score const& b) const
    {
          return std::tie(score, node) < std::tie(b.score, b.node);;
    }

    bool operator>(Score const& b) const
    {
        return std::tie(score, node) > std::tie(b.score, b.node);;
    }

};

class Map
{
private:
    GridBase grid;

public:
    Map() {}
    Map(const GridBase& g) : grid(g) {}

    GridBase& getMap() { return grid; }

    char& operator[](const Coord& coord)
    {
        if (coord.x < 0 || coord.x >= grid.size() || coord.y < 0 || coord.y >= grid[0].size())
            throw std::out_of_range("Coordinate is out of bounds");

        return grid[coord.x][coord.y];
    }

    void push_back(std::string str)
    {
        grid.push_back(str);
    }

    std::vector<Coord> positions()
    {
        std::vector<Coord> coord;
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

using Dirs = std::map<char, Coord>;
Dirs dirs = { {'<', {0, -1}}, {'v', {1, 0}}, {'>', {0, 1}}, {'^', {-1, 0}} };
std::map<char, std::pair<char, char>> nextDir = { {'^', {'>','<'}}, {'>', {'^','v'}}, {'v', {'<', '>'}}, {'<', {'^','v'}} };

uint64_t dijkstra(Map& map, const Node start)
{
    std::priority_queue<Score, std::vector<Score>, std::greater<Score>> frontier{};
    std::set<Node> visited{};
    auto enqueue = [&frontier, &visited](int64_t const score, Node const& node) 
    {
        if (!visited.contains(node)) 
        {
            visited.insert(node);
            frontier.push({ score, node });
        }
    };

    enqueue(0, start);
    while (!frontier.empty()) 
    {
        auto const [score, node] = frontier.top();
        frontier.pop();
        Coord next = node.pos + dirs[node.dir];

        if (map[node.pos] == 'E')
            return score;
        
        if (map[next] != '#')
            enqueue(score + 1, { next, node.dir });

        enqueue(score + 1000, { node.pos, nextDir[node.dir].first });
        enqueue(score + 1000, { node.pos, nextDir[node.dir].second});
    }

    return 0;
}

uint64_t adventDay16P12024(std::ifstream& input)
{
    uint64_t score = 0;

	Map map = parseInput(input, '\n');
    Node start;

    for (int row=0; row < map.rows(); ++row)
    {
       if (auto c = map.getMap()[row].find('S'); c != std::string::npos)
       {
           start.pos = { row, (int64_t)c };
           start.dir = '>';
           break;
       }
    }

    score = dijkstra(map, start);

    return score;
}

uint64_t findPaths(std::map<Node, int64_t> const& minScores, Node const end)
{
    std::queue<Node> frontier{};
    std::set<Node> visited{};
    auto enqueue = [&frontier, &visited](auto const node) 
    {
        if (!visited.contains(node))
        {
            frontier.push(node);
            visited.insert(node);
        }
    };

    enqueue(end);
    while (!frontier.empty()) 
    {
        const Node current = frontier.front();
        auto currentScore = minScores.at(current);
        frontier.pop();
        auto const prevPos = current.pos - dirs[current.dir];

        if (minScores.contains({ prevPos, current.dir })) 
            if (minScores.at({ prevPos, current.dir }) == currentScore - 1) 
                enqueue(Node{ prevPos, current.dir });           

        for (char const turn : {'<', '^','>', 'v'})
            if (minScores.contains({ current.pos, turn }))
                if (minScores.at({ current.pos, turn }) == currentScore - 1000)
                    enqueue(Node{ current.pos, turn });
    }

    std::set<Coord> minPaths{};
    for (auto const p : visited)
        minPaths.insert(p.pos);

    return minPaths.size();
}

uint64_t dijkstra2(Map& map, const Node start)
{
    std::priority_queue<Score, std::vector<Score>, std::greater<Score>> frontier{};
    std::set<Node> visited{};
    std::map<Node, int64_t> minScores{};
    auto enqueue = [&frontier, &visited, &minScores](int64_t const score, Node const& node)
    {
      if (!visited.contains(node))
      {
        visited.insert(node);
        frontier.push({ score, node });
        if (!minScores.contains(node) or minScores[node] > score) 
          minScores[node] = score;
          
      }
    };

    enqueue(0, start);
    while (!frontier.empty())
    {
        auto const [score, node] = frontier.top();
        frontier.pop();
        Coord next = node.pos + dirs[node.dir];

        if (map[node.pos] == 'E')
            return findPaths(minScores, node);

        if (map[next] != '#')
            enqueue(score + 1, { next, node.dir });

        enqueue(score + 1000, { node.pos, nextDir[node.dir].first });
        enqueue(score + 1000, { node.pos, nextDir[node.dir].second });
    }

    return 0;
}

uint64_t adventDay16P22024(std::ifstream& input)
{
    uint64_t score = 0;

    Map map = parseInput(input, '\n');
    Node start;

    for (int row = 0; row < map.rows(); ++row)
    {
        if (auto c = map.getMap()[row].find('S'); c != std::string::npos)
        {
            start.pos = { row, (int64_t)c };
            start.dir = '>';
            break;
        }
    }

    score = dijkstra2(map, start);

    return score;
}