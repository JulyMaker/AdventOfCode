#include <days.h>

using Grid = std::vector<std::vector<int>>;
using DIR = std::pair<int, int>;

struct Coord
{
    int x, y;

    Coord operator+(const DIR& dir){
        return { x + dir.first, y + dir.second };
    }
};

constexpr DIR RIGHT = { 0,  1 };
constexpr DIR DOWN = { 1,  0 };
constexpr DIR LEFT = { 0, -1 };
constexpr DIR UP = { -1,  0 };

std::vector<DIR> dir{RIGHT, DOWN, LEFT, UP};

auto valid = [&](int x, int y, const Grid& grid){
    return 0 <= x && x < grid.size() && 0 <= y && y < grid[0].size();
};

using T = std::array<int, 4>;

std::vector<T> getAdj(int x, int y, int d, int s)
{
    std::vector<T> adjacent;
    int d1 = (d + 3) % 4;
    Coord c = Coord{x, y} + dir[d1];
    adjacent.push_back({ c.x, c.y , d1, 1 });

    int d2 = (d + 1) % 4;
    c = Coord{ x, y } + dir[d2];
    adjacent.push_back({ c.x, c.y, d2, 1 });

    c = Coord{ x, y } + dir[d];
    if (s < 3) adjacent.push_back({ c.x, c.y, d, s + 1 });

    return adjacent;
};

std::vector<T> getAdj2(int x, int y, int d, int s)
{
    std::vector<T> adjacent;
    Coord c;
    if (s >= 4) {
        int d1 = (d + 3) % 4;
        c = Coord{ x, y } + dir[d1];
        adjacent.push_back({ c.x, c.y, d1, 1 });
    }
    if (s >= 4) {
        int d2 = (d + 1) % 4;
        c = Coord{ x, y } + dir[d2];
        adjacent.push_back({ c.x, c.y, d2, 1 });
    }
    if (s < 10)
    {
        c = Coord{ x, y } + dir[d];
        adjacent.push_back({ c.x, c.y, d, s + 1 });
    }

    return adjacent;
}

using VI = std::vector<int>;
using VVI = std::vector<VI>;
using VVVI = std::vector<VVI>;
using DIJKSTRA = std::vector<VVVI>;

DIJKSTRA dijkstra(const Grid& grid, DIJKSTRA& dijst, const bool part2 = false)
{
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;
    for (int d = 0; d < 2; d++)
    {
        dijst[0][0][d][0] = 0;
        pq.push({ 0, {0, 0, d, 0} });
    }

    while (!pq.empty()) 
    {
        auto [w, u] = pq.top(); pq.pop();
        auto [x, y, dir, state] = u;

        if (w > dijst[x][y][dir][state]) continue;
        for (auto [nx, ny, nd, ns] : (part2)? getAdj2(x, y, dir, state) : getAdj(x, y, dir, state))
        {
            if (!valid(nx, ny, grid)) continue;
            int weight = grid[nx][ny];
            if (dijst[nx][ny][nd][ns] > dijst[x][y][dir][state] + weight)
            {
                dijst[nx][ny][nd][ns] = dijst[x][y][dir][state] + weight;
                pq.push({ dijst[nx][ny][nd][ns], {nx, ny, nd, ns} });
            }
        }
    }

    return dijst;
}

uint64_t adventDay17P12024(std::ifstream& input)
{
    uint64_t score = INT_MAX;

    Grid grid = parseInputGrid(input);

    DIJKSTRA dijstra(grid.size(), VVVI(grid[0].size(), VVI(4, VI(4, score))));
    auto dijst= dijkstra(grid, dijstra);
    
    for (int dir = 0; dir < 4; dir++)
        for (int state = 0; state < 4; state++)
            score = std::min((int)score, dijst[grid.size() -1][grid[0].size() - 1][dir][state]);

    return score;
}

uint64_t adventDay17P22024(std::ifstream& input)
{
    uint64_t score = INT_MAX;

    Grid grid = parseInputGrid(input);

    DIJKSTRA dijstra(grid.size(), VVVI(grid[0].size(), VVI(4, VI(11, score))));
    auto dijst = dijkstra(grid, dijstra, true);

    for (int dir = 0; dir < 4; dir++)
        for (int state= 4; state <= 10; state++)
            score = std::min((int)score, dijst[grid.size() - 1][grid[0].size() - 1][dir][state]);

    return score;
}