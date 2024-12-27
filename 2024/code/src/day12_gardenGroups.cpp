#include <days.h>

using Grid = std::vector<std::string>;

struct Coordinate
{
    int x, y;

    Coordinate operator+(const Coordinate b) const
    {
        return { x + b.x, y + b.y };
    }

    bool operator<(const Coordinate& b) const {
        return (x == b.x) ? y < b.y : x < b.x;
    }
};

class GridExtended
{
private:
    Grid grid;

public:
    GridExtended() {}
    GridExtended(const Grid& g) : grid(g) {}

    char operator[](const Coordinate& coord) const 
    {
        if (coord.x < 0 || coord.x >= grid.size() || coord.y < 0 || coord.y >= grid[0].size())
            throw std::out_of_range("Coordinate is out of bounds");

        return grid[coord.x][coord.y];
    }

    void push_back(std::string str)
    {
        grid.push_back(str);
    }

    size_t rows() const { return grid.size(); }
    size_t cols() const { return grid.empty() ? 0 : grid[0].size(); }
};


constexpr Coordinate up =    { -1,  0 };
constexpr Coordinate down =  { 1,  0 };
constexpr Coordinate left =  { 0, -1 };
constexpr Coordinate right = { 0,  1 };

constexpr Coordinate left_up =   {-1 , -1};
constexpr Coordinate left_down = {1, -1};
constexpr Coordinate right_up =  {-1, 1};

static const std::vector<Coordinate> DIRS = { right, left, down, up };

std::tuple<size_t, size_t> totalPrice(const Grid& garden, Coordinate pos, std::set<Coordinate>& visited) 
{
    if (visited.contains(pos)) return { 0, 0 };

    visited.insert(pos);

    size_t area = 1;
    size_t perimeter = 0;

    for (auto d : DIRS) 
    {
        Coordinate newPos = pos + d;
        if (garden[newPos.y][newPos.x] == garden[pos.y][pos.x])
        {
            auto [newArea, newPerimeter] = totalPrice(garden, newPos, visited);
            area += newArea;
            perimeter += newPerimeter;
        }
        else
            ++perimeter;
    }

    return { area, perimeter };
}

uint64_t adventDay12P12024(std::ifstream& input)
{
    uint64_t score = 0;

    Grid map = parseInput(input, '\n');
    Grid garden;

    char basic = '~';
    std::string basicStr = std::string(map[0].size() + 2, basic);
    garden.push_back(basicStr); // First line

    for (auto& line : map)
    {
        garden.push_back(basic + line + basic);
    }

    garden.push_back(basicStr); // Last line

    std::set<Coordinate> visited;
    for (int x = 1; x < garden[0].size() - 1; ++x)
    {
        for (int y = 1; y < garden.size() - 1; ++y) 
        {
            auto [area, perimeter] = totalPrice(garden, Coordinate{x, y}, visited);
            score += area * perimeter;
        }
    }

    return score;
}

std::tuple<size_t, size_t> priceWithDiscount(const GridExtended& garden, Coordinate pos, std::set<Coordinate>& visited)
{
    if (visited.contains(pos)) return { 0, 0 };

    std::stack<Coordinate> nextPos;
    nextPos.push(pos);
    size_t area = 0;
    size_t slides = 0;

    while (!nextPos.empty()) 
    {
        pos = nextPos.top();
        nextPos.pop();

        if (visited.contains(pos)) continue;
        visited.insert(pos);

        ++area;

        if (garden[pos + up] != garden[pos]) 
        {
            if (garden[pos + left] != garden[pos] || garden[pos + left_up] == garden[pos])
                slides++;
        }

        if (garden[pos + right] != garden[pos]) 
        {
            if (garden[pos + up] != garden[pos] || garden[pos + right_up] == garden[pos])
                slides++;
        }

        if (garden[pos + down] != garden[pos]) 
        {
            if (garden[pos + left] != garden[pos] || garden[pos + left_down] == garden[pos])
                slides++;
        }

        if (garden[pos + left] != garden[pos]) 
        {
            if (garden[pos + up] != garden[pos] || garden[pos + left_up] == garden[pos])
                slides++;
        }

        std::vector<Coordinate> borderPos;
        for (auto direction : DIRS) 
        {
            Coordinate newPos = pos + direction;
            if (garden[newPos] == garden[pos] && !visited.contains(newPos))
                nextPos.push(pos + direction);
        }
    }

    return { area, slides };
}

uint64_t adventDay12P22024(std::ifstream& input)
{
    uint64_t score = 0;

    Grid map = parseInput(input, '\n');
    GridExtended garden;

    char basic = '~';
    std::string basicStr = std::string(map[0].size() + 2, basic);
    garden.push_back(basicStr); // First line

    for (auto& line : map)
    {
        garden.push_back(basic + line + basic);
    }

    garden.push_back(basicStr); // Last line

    std::set<Coordinate> visited;
    for (int x = 1; x < garden.cols() - 1; ++x)
    {
        for (int y = 1; y < garden.rows() - 1; ++y)
        {
            auto [area, perimeter] = priceWithDiscount(garden, Coordinate{x, y}, visited);
            score += area * perimeter;
        }
    }

    return score;
}