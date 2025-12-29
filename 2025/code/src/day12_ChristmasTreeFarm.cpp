#include <days.h>
#include <ansiColors.h>

struct Shape 
{
    std::vector<std::string> pattern;
    int filled;
};

struct Region 
{
    int w, h;
    std::vector<int> counts;
};

typedef std::vector<std::pair<int, int>> Coords;
typedef std::vector<std::vector<int>> Grid;

Coords parseShape(const std::vector<std::string>& pattern) 
{
    Coords cells;
    for (int r = 0; r < pattern.size(); r++) 
        for (int c = 0; c < pattern[r].length(); c++) 
            if (pattern[r][c] == '#') 
                cells.push_back({ r, c });

    return cells;
}

Coords normalize(const Coords& shape) 
{
    if (shape.empty()) return shape;

    int minR = shape[0].first, minC = shape[0].second;
    for (const auto& [r, c] : shape) 
    {
        minR = std::min(minR, r);
        minC = std::min(minC, c);
    }

    Coords normalized;
    for (const auto& [r, c] : shape) 
        normalized.push_back({ r - minR, c - minC });

    std::sort(normalized.begin(), normalized.end());
    return normalized;
}

Coords rotate90(const Coords& shape) 
{
    Coords rotated;
    for (const auto& [r, c] : shape)
        rotated.push_back({ c, -r });

    return normalize(rotated);
}

Coords flipH(const Coords& shape) 
{
    Coords flipped;
    for (const auto& [r, c] : shape)
        flipped.push_back({ r, -c });

    return normalize(flipped);
}

std::vector<Coords> getVariants(const Coords& shape) 
{
    std::set<Coords> uniqueVariants;
    Coords current = shape;

    for (int i = 0; i < 4; i++) 
    {
        uniqueVariants.insert(normalize(current));
        uniqueVariants.insert(normalize(flipH(current)));
        current = rotate90(current);
    }

    return std::vector<Coords>(uniqueVariants.begin(), uniqueVariants.end());
}

bool canPlace(const Grid& grid, const Coords& shape, int row, int col, int w, int h) 
{
    for (const auto& [dr, dc] : shape) 
    {
        int r = row + dr;
        int c = col + dc;
        if (r < 0 || r >= h || c < 0 || c >= w || grid[r][c] != 0)
            return false;
    }

    return true;
}

void place(Grid& grid, const Coords& shape, int row, int col, int id) 
{
    for (const auto& [dr, dc] : shape)
        grid[row + dr][col + dc] = id;
}

void unplace(Grid& grid, const Coords& shape, int row, int col) 
{
    for (const auto& [dr, dc] : shape)
        grid[row + dr][col + dc] = 0;
}

bool solve(Grid& grid, const std::vector<Coords>& presents, int w, int h, int idx = 0) {
    if (idx == presents.size()) return true;

    const Coords& shape = presents[idx];

    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
        {
            if (canPlace(grid, shape, r, c, w, h))
            {
                place(grid, shape, r, c, idx + 1);
                if (solve(grid, presents, w, h, idx + 1))
                    return true;

                unplace(grid, shape, r, c);
            }
        }
    }
    return false;
}

bool canFitPresents(int w, int h, const std::vector<int>& counts, const std::vector<Shape>& shapes) 
{
    std::vector<Coords> baseShapes;
    std::vector<std::vector<Coords>> allVariants;

    for (const auto& shape : shapes) 
    {
        baseShapes.push_back(parseShape(shape.pattern));
        allVariants.push_back(getVariants(baseShapes.back()));
    }

    std::vector<int> presentTypes;
    int totalCells = 0;
    for (int i = 0; i < counts.size(); i++) 
    {
        for (int j = 0; j < counts[i]; j++) 
        {
            presentTypes.push_back(i);
            totalCells += shapes[i].filled;
        }
    }

    if (presentTypes.empty()) return true;
    if (totalCells > w * h) return false;

    std::vector<int> variantIndices(presentTypes.size(), 0);

    std::function<bool(int)> tryVariants = [&](int presIdx) -> bool 
    {
        if (presIdx == presentTypes.size()) 
        {
            Grid grid(h, std::vector<int>(w, 0));
            std::vector<Coords> selectedVariants;
            for (int i = 0; i < presentTypes.size(); i++) 
            {
                selectedVariants.push_back(allVariants[presentTypes[i]][variantIndices[i]]);
            }

            return solve(grid, selectedVariants, w, h);
        }

        int shapeType = presentTypes[presIdx];
        for (int v = 0; v < allVariants[shapeType].size(); v++) 
        {
            variantIndices[presIdx] = v;
            if (tryVariants(presIdx + 1)) return true;
        }
        return false;
    };

    return tryVariants(0);
}


uint64_t adventDay12P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::string line;
    std::vector<Shape> shapes;
    std::vector<Region> regions;

    while (std::getline(input, line)) 
    {
        if (line.empty()) continue;

        if (line.back() == ':' && std::isdigit(line[0])) 
        {
            Shape shape;
            shape.filled = 0;
            shape.pattern.clear();

            std::string pattern_line;
            for (int i = 0; i < 3; i++) 
            {
                if (!std::getline(input, pattern_line)) break;

                shape.pattern.push_back(pattern_line);
                shape.filled += std::count(pattern_line.begin(), pattern_line.end(), '#');
            }
            shapes.push_back(shape);
        }

        if (line.find('x') != std::string::npos && line.find(':') != std::string::npos) 
        {
            Region r;
            int pos1 = line.find('x');
            int pos2 = line.find(':');

            r.w = std::stoi(line.substr(0, pos1));
            r.h = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            std::istringstream ss(line.substr(pos2 + 2));
            int count;
            while (ss >> count) r.counts.push_back(count);

            regions.push_back(r);
        }
    }


    for (const auto& region : regions) 
    {
        long long totalHash = 0;
        for (int i = 0; i < region.counts.size(); i++) 
            totalHash += shapes[i].filled * region.counts[i];

        if (totalHash > region.w * region.h) continue;

        if (canFitPresents(region.w, region.h, region.counts, shapes))
            score++;
    }


    return score;
}



uint64_t adventDay12P22025(std::ifstream& input)
{
    uint64_t score = 0;

    paintAdventCalendar2025();
    std::cout << "        Happy Advent of Code 2025!" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return score;
}