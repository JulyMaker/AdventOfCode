#include <days.h>

struct Coordinate
{
    int x;
    int y;

    Coordinate() : x(0), y(0) {}
    Coordinate(int _x, int _y) : x(_x), y(_y) {}

    Coordinate operator-(const Coordinate b) const
    {
      return { (x - b.x), (y - b.y) };
    }
    void operator-=(const Coordinate& b)
    {
        x -= b.x;
        y -= b.y;
    }

    Coordinate operator+(const Coordinate b) const
    {
        return {x + b.x, y + b.y};
    }

    void operator+=(const Coordinate& b) 
    {
        x += b.x;
        y += b.y;
    }

    bool operator<(const Coordinate& b) const {
        return (x == b.x)? y < b.y : x < b.x  ;
    }
};


uint64_t adventDay08P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> in = parseInputChars(input);
    int rows = in.size();
    int columns = in[0].size();

    std::map<char, std::vector<Coordinate>> antennas;
    for (int row= 0; row < rows; ++row)
      for (int col=0; col < columns; ++col)
        if (in[row][col] != '.') antennas[in[row][col]].push_back({ col, row });

    std::set<Coordinate> antinodes;
    for (const auto& antenna : antennas) 
    {
        const auto& locations = antenna.second;
        for (size_t i = 0; i < locations.size() - 1; ++i) 
        {
            for (size_t j = i + 1; j < locations.size(); ++j) 
            {
                auto diff = locations[i] - locations[j];
                auto antinode = locations[i] + diff;

                if (antinode.x >= 0 && antinode.x < columns && antinode.y >= 0 && antinode.y < rows)
                    antinodes.insert(antinode);

                antinode = locations[j] - diff;
                if (antinode.x >= 0 && antinode.x < columns && antinode.y >= 0 && antinode.y < rows)
                    antinodes.insert(antinode);
            }
        }
    }

    score+= antinodes.size();

    return score;
}


uint64_t adventDay08P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> in = parseInputChars(input);
    int rows = in.size();
    int columns = in[0].size();

    std::map<char, std::vector<Coordinate>> antennas;
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < columns; ++col)
            if (in[row][col] != '.') antennas[in[row][col]].push_back({ col, row });

    std::set<Coordinate> antinodes;
    for (const auto& antenna : antennas) 
    {
        const auto& locations = antenna.second;
        for (size_t i = 0; i < locations.size() - 1; ++i) 
        {
            for (size_t j = i + 1; j < locations.size(); ++j) 
            {
                antinodes.insert(locations[i]);
                antinodes.insert(locations[j]);

                auto diff = locations[i] - locations[j];
                auto antinode = locations[i] + diff;
                while (antinode.x >= 0 && antinode.x < columns && antinode.y >= 0 && antinode.y < rows) 
                {
                    antinodes.insert(antinode);
                    antinode += diff;
                }

                antinode = locations[j] - diff;
                while (antinode.x >= 0 && antinode.x < columns && antinode.y >= 0 && antinode.y < rows) 
                {
                    antinodes.insert(antinode);
                    antinode -= diff;
                }
            }
        }
    }

    score += antinodes.size();

    return score;
}