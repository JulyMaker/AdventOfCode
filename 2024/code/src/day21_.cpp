#include <days.h>

#define ALLc(x) (x).cbegin(),(x).cend()
using Grid = std::vector<std::vector<char>>;

std::vector<std::pair<int, int>> moves = { {0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; // R - L - D - U

struct Coord {
    int64_t x, y;

    Coord operator+(std::pair<int, int> move){
        return {x + move.first, y + move.second};
    }

    bool operator==(const Coord& c2) const{
        return x == c2.x && y == c2.y;
    }
};

template <> struct std::hash<Coord> {
    size_t operator()(const Coord& coord) const noexcept {
        std::size_t hash = std::hash<int64_t>()(coord.x);
        hash_combine(hash, std::hash<int64_t>()(coord.y));
        return hash;
    }

    static void hash_combine(std::size_t& seed, std::size_t hash_value) {
        seed ^= hash_value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

auto isValid = [&](const Grid& grid, const Coord& cord) {
    return cord.x >= 0 && cord.x < grid.size() && cord.y >= 0 && cord.y < grid[0].size();
};

uint64_t adventDay21P12024(std::ifstream& input)
{
    uint64_t score = 0;

    constexpr int TIMES = 64;
    Grid grid = parseInputChars(input);

    char start = 'S';
    auto it = std::find_if(ALLc(grid), [&start](const std::vector<char>& row) {
        return std::find(ALLc(row), start) != row.end();
        });
    
    auto rowS = std::distance(grid.cbegin(), it);
    auto colS = std::distance(it->begin(), std::find(it->begin(), it->end(), start));

    std::deque<Coord> stepsNext;
    std::deque<Coord> stepsQueue;
    stepsQueue.emplace_back( rowS , colS );
    grid[rowS][colS] == '.';

    for(int t=0; t < TIMES; t++)
    {
        while (!stepsQueue.empty())
        {
            Coord cord = stepsQueue.front();
            stepsQueue.pop_front();
            for (auto& move : moves)
            {
                Coord newCord = cord + move;
                if (isValid(grid, newCord))
                {
                    if (grid[newCord.x][newCord.y] == '.')
                    {
                        grid[newCord.x][newCord.y] = '0';
                        stepsNext.emplace_back(newCord);
                        if(t == TIMES - 1)
                            score++;
                    }
                }
            }
            grid[cord.x][cord.y] = '.';
        }

        stepsQueue = stepsNext;
        stepsNext.clear();
    }

    return score;
}

void bfsGardenPlots(std::unordered_set<Coord>& startPositions, std::unordered_set<Coord>& visited, const Grid& grid)
{
    std::unordered_set<Coord> nextPositions;

    int height = static_cast<int>(grid.size());
    int width  = static_cast<int>(grid[0].size());

    for (auto coord : startPositions) 
    {
        for (auto& move : moves)
        {
            Coord newCoord = coord + move;
            Coord checkPos = { ((newCoord.x % height) + height) % height, ((newCoord.y % width) + width) % width };

            if (grid[checkPos.x][checkPos.y] != '#' && !visited.contains(newCoord))
            {
                nextPositions.insert(newCoord);
                visited.insert(newCoord);
            }
        }
    }

    startPositions = nextPositions;
}

uint64_t adventDay21P22024(std::ifstream& input)
{
    uint64_t score = 0;

    constexpr int TIMES = 26501365;

    // Read input and S coord
    Grid grid = parseInputChars(input);

    char start = 'S';
    auto it = std::find_if(ALLc(grid), [&start](const std::vector<char>& row) {
        return std::find(ALLc(row), start) != row.end();
        });

    auto rowS = std::distance(grid.cbegin(), it);
    auto colS = std::distance(it->begin(), std::find(it->begin(), it->end(), start));

    // Init variables
    Coord startPos(rowS, colS);
    std::unordered_set<Coord> startPositions;
    startPositions.insert(startPos);
    grid[rowS][colS] = '.';

    std::unordered_set<Coord> visited;
    visited.insert(startPos);

    std::vector<int64_t> params;
    std::vector<int64_t> lens;
    lens.push_back(1);

    // BSF Garden Plots
    for (int t = 0; t < TIMES; ++t) 
    {
        bfsGardenPlots(startPositions, visited, grid);
        lens.push_back(startPositions.size());

        if (t % grid.size() == TIMES % grid.size()) 
        {
            int len= 0;
            for (int j = 0; j < lens.size() - 1; ++j)
                if (j % 2 == t % 2) 
                    len+= lens[j];
                
            params.push_back(len);
        }

        if (params.size() == 3) break;
    }


    int64_t p1= params[0];
    int64_t p2= params[1] - params[0];
    int64_t p3= params[2] - params[1];
    int64_t ip= TIMES / static_cast<int64_t>(grid.size());

    // Solve the quadratic
    score= p1 + p2 * ip + (ip * (ip - 1) / 2) * (p3 - p2);

    return score;
}

// Second solve
//uint64_t adventDay21P22024(std::ifstream& input)
//{
//    uint64_t score = 0;
//
//    constexpr int TIMES = 26501365;
//
//    // Read input and S coord
//    Grid grid = parseInputChars(input);
//
//    int n = grid.size();
//    int m = grid[0].size();
//
//    std::vector<std::vector<char>> g(3 * n, std::vector<char>(3 * m));
//    for (int i = 0; i < n; i++) 
//        for (int j = 0; j < m; j++)
//            for (int a = 0; a < 3; a++)
//                for (int b = 0; b < 3; b++)
//                    g[i + a * n][j + b * n] = (grid[i][j] == 'S' && (a != 1 || b != 1)) ? '.' : grid[i][j];
//
//    Coord start;
//    for (int i = 0; i < 3 * n; i++)
//    {
//        for (int j = 0; j < 3 * n; j++)
//            if (g[i][j] == 'S')
//            {
//                start = Coord(i, j);
//                break;
//            }
//    }
//                  
//
//    std::vector<std::vector<int>> dist(3 * n, std::vector<int>(3 * m));
//
//    std::vector<std::vector<bool>> vis(3 * n, std::vector<bool>(3 * m));
//    std::queue<Coord> q;
//    q.push(start);
//    vis[start.x][start.y] = true;
//
//    auto inside = [&](Coord p) {
//        return 0 <= p.x && p.x < 3 * n && 0 <= p.y && p.y < 3 * m;
//    };
//
//    while (!q.empty()) {
//        Coord u = q.front();
//        q.pop();
//        for (auto& move : moves) 
//        {
//            Coord v = u + move;
//            if (inside(v) && g[v.x][v.y] != '#' && !vis[v.x][v.y]) 
//            {
//                vis[v.x][v.y] = true;
//                dist[v.x][v.y] = dist[u.x][u.y] + 1;
//                q.push(v);
//            }
//        }
//    }
//
//    std::vector<int64_t> dp(TIMES + 1000);
//    for (int i = TIMES; i >= 0; i--)
//        dp[i] = (i % 2 == TIMES % 2) + 2 * dp[i + n] - dp[i + 2 * m];
//
//
//    for (int i = 0; i < 3 * n; i++) 
//    {
//        for (int j = 0; j < 3 * m; j++) 
//        {
//            if (!vis[i][j]) continue;
//            int dx = i - start.x;
//            int dy = j - start.y;
//            if (-n <= dx && dx < n && -m <= dy && dy < m)
//                score += dp[dist[i][j]];
//        }
//    }
//
//    return score;
//}