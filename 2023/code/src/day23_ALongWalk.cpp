#include <days.h>

#define ALL(x) (x).begin(), (x).end()

using Grid = std::vector<std::vector<char>>;

struct Coord {
    int64_t x, y;

    Coord operator+(Coord move) {
        return { x + move.x, y + move.y };
    }

    bool operator==(const Coord& c2) const {
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

std::map<char, Coord> moves = { {'>', {0, 1 } }, {'<', { 0, -1 } }, {'v', { 1, 0 } }, {'^', { -1, 0 } } }; // R - L - D - U

std::vector<Coord> getNextPoints(const Grid& grid, Coord& current)
{
       std::vector<Coord> nextCoords;
       Coord next;
       if (grid[current.x][current.y] != '.')
       {
           next = current + moves[grid[current.x][current.y]];
           if (grid[next.x][next.y] != '#')
                nextCoords.push_back(next);
       }      
       else
           for (auto& move : moves)
           {
               Coord next= current + moves[move.first];
               if (isValid(grid, next) && grid[next.x][next.y] != '#')
                   nextCoords.push_back(next);
           }

       return nextCoords;
}

void dfsHike(Coord current, const Coord& end, const Grid& grid, std::unordered_set<Coord>& visited, uint64_t steps, uint64_t& max)
{
    if (current == end)
    {
        max = std::max(max, steps);
        return;
    }
                                
    visited.insert(current);
    for (auto& c : getNextPoints(grid, current))
    {
        if (auto it = visited.find(c); it == visited.end())
            dfsHike(c, end, grid, visited, steps + 1, max); 
    }
    visited.erase(current);
}

uint64_t adventDay23P12023(std::ifstream& input)
{
    uint64_t score = 0;

    Grid grid = parseInputChars(input);

    char startAndend = '.';
    auto colS = std::distance(grid[0].begin(), std::find(ALL(grid[0]), startAndend));
    auto colE = std::distance(grid[grid.size()- 1].begin(), std::find(ALL(grid[grid.size() - 1]), startAndend));

    std::unordered_set<Coord> visited;
    dfsHike(Coord(0, colS), Coord(grid.size()- 1, colE), grid, visited, 0, score);

    return score;
}

using ADJACENCIES = std::unordered_map<Coord, std::unordered_map<Coord, int64_t>>;

ADJACENCIES adjacencies(const Grid& grid)
{
    ADJACENCIES adjacencies;
    
    for (int x = 0; x < grid.size(); ++x) 
    {
        for (int y = 0; y < grid[0].size(); ++y) 
        {
            if (grid[x][y] != '#') 
            {
                Coord current(x, y);
                std::unordered_map<Coord, int64_t> directions;
                for (const auto& move : moves) 
                {
                    Coord next = Coord(x, y) + move.second;
                    if (isValid(grid,next) && grid[next.x][next.y] != '#')
                        directions[next] = 1;
                }

                adjacencies[current] = directions;
            }
        }
    }

    std::vector<Coord> keys;
    for (const auto& entry : adjacencies)
        keys.push_back(entry.first);

    for (const auto& key : keys) 
    {
        auto& neighbors = adjacencies[key];
        
        if (neighbors.size() == 2) 
        {
            auto left = neighbors.begin()->first;
            auto right = std::next(neighbors.begin())->first;
        
            int64_t totalSteps = neighbors[left] + neighbors[right];
        
            // Update adjacencias
            adjacencies[left][right] = std::max(adjacencies[left][right], totalSteps);
            adjacencies[right][left] = std::max(adjacencies[right][left], totalSteps);

            // Remove old adjacencias
            for (const auto& coord : { left, right }) 
            {
                auto it = adjacencies.find(coord);
                if (it != adjacencies.end())
                    it->second.erase(key);
            }
        
            adjacencies.erase(key);
        }
    }

    return adjacencies;
}

int64_t dfsHike2(const ADJACENCIES& adjac, Coord current, const Coord& end, std::unordered_map<Coord, int64_t >& seen)
{
    if (current == end) {
        int sum = 0;
        for (const auto& entry : seen)
            sum += entry.second;

        return sum;
    }

    int best = -1;
    for (const auto& neighborEntry : adjac.at(current))
    {
        const Coord& neighbor = neighborEntry.first;
        int64_t steps = neighborEntry.second;

        if (seen.find(neighbor) == seen.end()) 
        {
            seen[neighbor] = steps;
            int64_t res = dfsHike2(adjac, neighbor, end, seen);
            if (best == -1 || (res != -1 && res > best))
                best = res;

            seen.erase(neighbor);
        }
    }

    return best;
}


uint64_t adventDay23P22023(std::ifstream& input)
{
    uint64_t score = 0;

    Grid grid = parseInputChars(input);

    char startAndend = '.';
    auto colS = std::distance(grid[0].begin(), std::find(ALL(grid[0]), startAndend));
    auto colE = std::distance(grid[grid.size() - 1].begin(), std::find(ALL(grid[grid.size() - 1]), startAndend));

    ADJACENCIES adjacncies = adjacencies(grid);
    std::unordered_map<Coord, int64_t> seen;
    score= dfsHike2(adjacncies, Coord(0, colS), Coord(grid.size() - 1, colE), seen);

    return score;
}