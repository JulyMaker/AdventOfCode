#include <days.h>

struct Points
{
    int64_t x, y;

    Points operator+(Points p2)
    {
        return { x + p2.x, y + p2.y };
    }
    Points operator+(Points p2) const
    {
        return { x + p2.x, y + p2.y };
    }

    bool operator==(Points p2)
    {
        return (x == p2.x) && (y == p2.y);
    }
    bool operator==(const Points p2) const
    {
        return (x == p2.x) && (y == p2.y);
    }

    bool operator<(const Points& p2)
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }

    const bool operator<(const Points& p2) const
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }
};


template <typename T> struct Grid
{
    std::vector<T> data;
    int64_t width;
    int64_t height;
    T const empty;
    T outside;

    constexpr Grid(T const empty = T{}) : empty(empty) {};
    constexpr Grid(int64_t const width, int64_t const height, T const value = T{}, T const empty = T{})
        : width(width), height(height), empty(empty)
    {
        data.resize(width * height, value);
    }

    constexpr bool validPos(Points const& pos) const
    {
        return validPos(pos.x, pos.y);
    }
    constexpr bool validPos(int64_t const x, int64_t const y) const
    {
        return x >= 0 && y >= 0 && x < height && y < width;
    }

    constexpr size_t index(Points const& pos) const
    {
        return index(pos.x, pos.y);
    }
    constexpr size_t index(int64_t const x, int64_t const y) const
    {
        return static_cast<size_t>(x * width + y);
    }

    constexpr T const& operator[](Points const p) const
    {
        if (!validPos(p))
            return empty;

        return data[index(p)];
    }
    constexpr T& operator[](Points const p)
    {
        if (!validPos(p))
            return outside = empty;

        return data[index(p)];
    }

    std::vector<Points> positions() const
    {
        std::vector<Points> coord;
        for (int x = 0; x < height; ++x)
            for (int y = 0; y < width; ++y)
                coord.push_back({ x, y });

        return coord;
    }
};

using Dirs = std::map<char, Points>;
Dirs dirs = { {'<', {0, -1}}, {'v', {1, 0}}, {'>', {0, 1}}, {'^', {-1, 0}} };

void getTimes(Grid<char> const& map, Points const& start, Grid<int64_t>& lengths)
{
    std::deque<std::pair<int64_t, Points>> border;
    border.emplace_back(0, start);
    lengths[start] = 0;

    while (!border.empty()) 
    {
        auto const current = border.begin();
        auto const [len, pos] = *current;

        border.erase(current);
        lengths[pos] = len;

        for(auto& dir : dirs)
        {
            const Points next = pos + dirs[dir.first];
            while (lengths[next] < 0 && map[next] != '#')
            {
                border.emplace_back(len + 1, next);
                break;
            }
        }
    }
}

struct CheatID 
{
    Points start;
    Points goal;
    auto operator<=>(CheatID const& other) const 
    {
        return std::pair(start, goal) <=> std::pair(other.start, other.goal);
    }
};

int64_t manhattan(Points const& from, Points const& to) 
{
    return std::abs(from.x - to.x) + std::abs(from.y - to.y);
}

auto cheat(Grid<int64_t> const& timings, auto const& diamondDir)
{
    std::set<CheatID> cheatpos;
    std::vector<Points> posgen = timings.positions();
    for(auto& pos : posgen)
    {
        while (timings[pos] >= 0) 
        {
            auto dir = std::begin(diamondDir);
            while (dir != std::end(diamondDir)) 
            {
                auto const next = pos + *dir;
                auto const cheatlen = manhattan(pos, next);
                auto const timesave = timings[pos] - timings[next] - cheatlen;
                while (timings[next] >= 0 && timesave > 50) 
                {
                    //std::println("Cheat ({}->{} #{}) saves {}ps", pos, next, cheatlen,timesave);
                    //std::cout << "Cheat (" << pos.x<<","<<pos.y << "->" << next.x<<","<<next.y << " #" << cheatlen << ") saves " << timesave << "ps" << std::endl;
                    while (timesave >= 100) 
                    {
                        cheatpos.emplace(pos, next);
                        break;
                    }
                    break;
                }
                ++dir;
            }
            break;
        }
    }

    return cheatpos.size();
}

template <int64_t size> constexpr auto drawDiamond() 
{
    std::array<Points, 2 * size * size + 2 * size - 4> diamond;
    std::size_t pos = 0;
    int64_t x = 1;
    while (x < size + 1) 
    {
        int64_t y = 1;
        while (y < size + 1 - x) 
        {
            diamond[pos++] = Points{ x, y };
            diamond[pos++] = Points{ -x, y };
            diamond[pos++] = Points{ x, -y };
            diamond[pos++] = Points{ -x, -y };
            ++y;
        }
        ++x;
    }
    x = 2;
    while (x < size + 1) 
    {
        diamond[pos++] = Points{ x, 0 };
        diamond[pos++] = Points{ -x, 0 };
        diamond[pos++] = Points{ 0, x };
        diamond[pos++] = Points{ 0, -x };
        ++x;
    }

    return diamond;
}

constexpr auto diamond2 = drawDiamond<2>();

uint64_t adventDay20P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    Points start, goal;
    Grid<char> track;
    track.height = 0;
    for (auto& line : in)
    {
       track.data.insert(track.data.end(), line.begin(), line.end());
       if (auto c = line.find('S'); c != std::string::npos)
           start = { track.height, (int64_t)c };
       if (auto c = line.find('E'); c != std::string::npos)
           goal = { track.height, (int64_t)c };
 
       track.height++;
       track.width = static_cast<int64_t>(line.size());
    }

    Grid<int64_t> timings{ track.width, track.height, -1000, -1000 };
    timings[goal] = 0;

    getTimes(track, goal, timings);

    score = cheat(timings, diamond2);

    return score; // 1326 Too Low
}

constexpr auto diamond20 = drawDiamond<20>();

uint64_t adventDay20P22025(std::ifstream& input)
{
    uint64_t score = 1;

    std::vector<std::string> in = parseInput(input, '\n');

    Points start, goal;
    Grid<char> track;
    track.height = 0;
    for (auto& line : in)
    {
        track.data.insert(track.data.end(), line.begin(), line.end());
        if (auto c = line.find('S'); c != std::string::npos)
            start = { track.height, (int64_t)c };
        if (auto c = line.find('E'); c != std::string::npos)
            goal = { track.height, (int64_t)c };

        track.height++;
        track.width = static_cast<int64_t>(line.size());
    }

    Grid<int64_t> timings{ track.width, track.height, -1000, -1000 };
    timings[goal] = 0;

    getTimes(track, goal, timings);

    score = cheat(timings, diamond20);

	return score;
}