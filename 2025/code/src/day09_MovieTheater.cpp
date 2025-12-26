#include <days.h>

struct PointUI
{
    int64_t x, y;

    PointUI() : x(0), y(0) {}
    PointUI(int64_t x, int64_t y) : x(x), y(y) {}

    PointUI operator+(const PointUI b) const
    {
        return { x + b.x, y + b.y };
    }

    PointUI operator-(const PointUI b) const
    {
        return { x - b.x, y - b.y };
    }

    PointUI& operator+=(const PointUI& b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    PointUI operator-() const
    {
        return { -x, -y };
    }

    bool operator==(const PointUI& b) const {
        return (x == b.x) && (y == b.y);
    }

    bool operator!=(const PointUI& b) const {
        return (x != b.x) || (y != b.y);
    }

    struct Hash {
        size_t operator()(const PointUI& p) const 
        {
            size_t h1 = std::hash<int64_t>()(p.x);
            size_t h2 = std::hash<int64_t>()(p.y);
            return h1 ^ (h2 << 1);
        }
    };
};

using points_t = std::vector<PointUI>;
using areas_map_t = std::multimap<uint64_t, std::array<PointUI, 2>>;
using map_t = std::unordered_map<PointUI, std::array<PointUI, 2>, PointUI::Hash>;
using keepout_map_t = std::unordered_map<PointUI, char, PointUI::Hash>;

areas_map_t findAreas(const points_t& points)
{
    areas_map_t areas;

    for (auto i = points.begin(); i < points.end(); i++) 
    {
        for (auto j = i + 1; j < points.end(); j++) 
        {
            const int64_t i_x = static_cast<uint64_t>((*i).x);
            const int64_t i_y = static_cast<uint64_t>((*i).y);
            const int64_t j_x = static_cast<uint64_t>((*j).x);
            const int64_t j_y = static_cast<uint64_t>((*j).y);

            const uint64_t area = (std::abs(i_x - j_x) + 1) * (std::abs(i_y - j_y) + 1);

            areas.emplace(area, std::array<PointUI, 2>{ (*i), (*j) });
        }
    }

    return areas;
}

uint64_t adventDay09P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    points_t points;
    for(auto& line : in)
    {
        std::vector<uint64_t> p = splitUInt(line, ",");
        points.push_back(PointUI(p[0], p[1]));
    }

    const auto areas = findAreas(points);

    score= (*areas.rbegin()).first;

    return score;
}

void normalizeDir(PointUI& dir)
{
    const int max = std::max(std::abs(static_cast<int64_t>(dir.x)), std::abs(static_cast<int64_t>(dir.y)));
    if (max == 0)
        throw std::runtime_error("Max is zero!");
    dir.x /= max;
    dir.y /= max;
}

int determineTurn(const PointUI& last_dir, const PointUI& dir)
{
    if ((last_dir == PointUI{ 1, 0 } && dir  == PointUI{ 0, 1 }) ||
        (last_dir == PointUI{ 0, 1 } && dir  == PointUI{ -1, 0 }) ||
        (last_dir == PointUI{ -1, 0 } && dir == PointUI{ 0, -1 }) ||
        (last_dir == PointUI{ 0, -1 } && dir == PointUI{ 1, 0 }))
        return 90;
    if ((last_dir == PointUI{ 0, 1 } && dir  == PointUI{ 1, 0 }) ||
        (last_dir == PointUI{ 1, 0 } && dir  == PointUI{ 0, -1 }) ||
        (last_dir == PointUI{ 0, -1 } && dir == PointUI{ -1, 0 }) ||
        (last_dir == PointUI{ -1, 0 } && dir == PointUI{ 0, 1 }))
        return -90;

    return 0;
}

std::tuple<map_t, bool> tracePoints(const points_t& points)
{
    int degrees{ 0 };
    map_t map;
    PointUI last_dir{ 0, 0 };
    PointUI to_last_point{ 0, 0 };

    for (auto i = points.begin(); i < points.end(); ++i) 
    {
        auto i2 = i + 1;
        if (i2 == points.end())
            i2 = points.begin();

        PointUI dir = (*i2) - (*i);

        normalizeDir(dir);
        PointUI trace = *i;
        to_last_point = -last_dir;

        while (trace != *i2) 
        {
            map.emplace(trace, std::array<PointUI, 2>{ dir, to_last_point });
            trace += dir;
            to_last_point = -dir;
        }
        degrees += determineTurn(last_dir, dir);
        last_dir = dir;
    }

    map.at(points.at(0)).at(1) = -last_dir;

    return { map, degrees > 0 };
}

PointUI createTurn(const PointUI& dir, bool clockwise)
{
    if (clockwise) 
    {
        if (dir == PointUI{ 1, 0 })
            return PointUI{ 0, 1 };
        if (dir == PointUI{ 0, 1 })
            return PointUI{ -1, 0 };
        if (dir == PointUI{ -1, 0 })
            return PointUI{ 0, -1 };
        if (dir == PointUI{ 0, -1 })
            return PointUI{ 1, 0 };
    }
    else 
    {
        if (dir == PointUI{ 1, 0 })
            return PointUI{ 0, -1 };
        if (dir == PointUI{ 0, -1 })
            return PointUI{ -1, 0 };
        if (dir == PointUI{ -1, 0 })
            return PointUI{ 0, 1 };
        if (dir == PointUI{ 0, 1 })
            return PointUI{ 1, 0 };
    }
    throw std::runtime_error("Cannot determine turn!");
}

keepout_map_t genKeepout(const map_t& map, bool clockwise)
{
    keepout_map_t keepout;
    for (const auto& point : map) 
    {
        const auto dir = createTurn(point.second.at(0), !clockwise);
        const auto pt1 = point.first + dir;
        const auto dir2 = createTurn(point.second.at(1), clockwise);
        const auto pt2 = point.first + dir2;
        if (!keepout.contains(pt1) && !map.contains(pt1))
            keepout.emplace(pt1, 0);
        if (!keepout.contains(pt2) && !map.contains(pt2))
            keepout.emplace(pt2, 0);
    }
    return keepout;
}

bool checkRectangle(const std::array<PointUI, 2>& rect, const keepout_map_t& keepout)
{
    const int64_t low_x = std::min(rect[0].x, rect[1].x);
    const int64_t high_x = std::max(rect[0].x, rect[1].x);
    const int64_t low_y = std::min(rect[0].y, rect[1].y);
    const int64_t high_y = std::max(rect[0].y, rect[1].y);

    return std::ranges::all_of(keepout, [&low_x, &high_x, &low_y, &high_y](const auto& a) {
        return !(a.first.x >= low_x && a.first.x <= high_x && a.first.y >= low_y && a.first.y <= high_y);
        });
}

uint64_t adventDay09P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    points_t points;
    for (auto& line : in)
    {
        std::vector<int64_t> p = splitUInt64(line, ",");
        points.push_back(PointUI(p[0], p[1]));
    }

    const auto areas = findAreas(points);

    const auto [map, clockwise] = tracePoints(points);

    const auto keepout = genKeepout(map, clockwise);

    long part2_answer{ 0 };

    for (auto i = areas.rbegin(); i != areas.rend(); i++) 
    {
        const bool pass = checkRectangle((*i).second, keepout);
        if (pass) 
        {
            score = (*i).first;
            break;
        }
    }

    return score;
}