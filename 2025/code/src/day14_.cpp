#include <days.h>

struct Coordinates
{
    int x, y;

    Coordinates operator+(const Coordinates& b) const
    {
        return { x + b.x, y + b.y };
    }

    Coordinates operator*(const int& b) const
    {
        return { x * b, y * b };
    }

    bool operator<(const Coordinates& b) const {
        return (x == b.x) ? y < b.y : x < b.x;
    }

    bool operator!=(const Coordinates& b) const {
        return (x != b.x) || (y != b.y);
    }
};

int mod(int64_t a, int64_t b)
{
    return (a % b + b) % b;
}

struct Robot 
{
    Coordinates start;
    Coordinates dir;

    Coordinates dest(const int64_t seconds, int64_t width, int64_t height) const
    {
        //Coordinate mul = dir * seconds;
        //Coordinate sum = start + mul;
        Coordinates pos = start + dir * seconds;
        pos = Coordinates{ mod(pos.x, width), mod(pos.y, height) };

        return pos;
    }
};

uint64_t adventDay14P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInput(input, '\n');
    bool USE_TEST_CASE = in.size() < 13;

    int64_t width = USE_TEST_CASE ? 11 : 101;
    int64_t height = USE_TEST_CASE ? 7 : 103;
    const int64_t SECONDS = 100;

    std::vector<Robot> robots{};
    for (auto& line : in)
    {
        std::vector<std::string> lineStr = parseInputReg(line, R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");

        Coordinates c1 = {std::stod(lineStr[1]), std::stod(lineStr[2])};
        Coordinates c2 = {std::stod(lineStr[3]), std::stod(lineStr[4]) };
        robots.emplace_back(c1, c2);
    }

    std::array<uint64_t, 4> quad{};
    for (auto const robot : robots) 
    {
        const Coordinates dest = robot.dest(SECONDS, width, height);

        if (dest.x < (width / 2)) 
        {
            if (dest.y < height / 2) ++quad[0];
            if (dest.y > height / 2) ++quad[1];
        }

        if (dest.x > width / 2) 
        {
            if (dest.y < height / 2) ++quad[2];
            if (dest.y > height / 2) ++quad[3];
        }
    }

    score+= quad[0] * quad[1] * quad[2] * quad[3];


    return score;
}

std::vector<std::vector<char>> render(const std::vector<Robot>& robots, const int64_t second, const int64_t width, const int64_t height)
{
    std::vector<std::vector<char>> frame(height, std::vector<char>(width, ' '));
    for (auto& robot : robots) 
    {
        const Coordinates dest = robot.dest(second, width, height);
        switch (frame[dest.y][dest.x])
        {
          case ' ':
              frame[dest.y][dest.x] = '.';
              break;
          case '.':
              frame[dest.y][dest.x] = '+';
              break;
          case '+':
              frame[dest.y][dest.x] = '*';
              break;
        }
    }
    return frame;
}

void print(const std::vector<Robot>& robots, const int64_t second, const int64_t width, const int64_t height) 
{ 
    std::vector<std::vector<char>> grid = render(robots, second, width, height);
    for (auto& line : grid)
    {
      std::copy(line.begin(), line.end(), std::ostream_iterator<char>(std::cout));
      std::cout << std::endl;
    }
}

std::vector<Coordinates> diagonals(const int64_t width, const int64_t height)
{
    std::vector<Coordinates> coords;

    for (int x = 0; x < width; ++x)
    {
      for (int y = 0; y < height; ++y)
      {
        Coordinates pos = { x - y / 2 , y };
        if (pos.x >= 0)
        { 
          coords.push_back(pos);
        }     
      }
    }      

    return coords;
}

int64_t treeThreshold(auto const& robots, const int64_t second, const int64_t width, const int64_t height)
{
    int64_t maxCount = 0;
    int64_t count = 0;
    bool onDiagonal = false;
    auto const frame = render(robots, second, width, height);

    std::vector<Coordinates> diag = diagonals(width, height);
    for (auto& pos : diag)
    {
        if (frame[pos.y][pos.x] == ' ')
        {
            if (onDiagonal) 
            {
                onDiagonal = false;
                maxCount = std::max(maxCount, count);
            }
        }
        else if (!onDiagonal) 
        {
            onDiagonal = true;
            count = 1;
        }
        else 
            ++count;
    }

    return maxCount;
}

uint64_t adventDay14P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    bool USE_TEST_CASE = in.size() < 13;

    int64_t width = USE_TEST_CASE ? 11 : 101;
    int64_t height = USE_TEST_CASE ? 7 : 103;
    const int64_t SECONDS = 100;

    std::vector<Robot> robots{};
    for (auto& line : in)
    {
        std::vector<std::string> lineStr = parseInputReg(line, R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");

        Coordinates c1 = { std::stod(lineStr[1]), std::stod(lineStr[2]) };
        Coordinates c2 = { std::stod(lineStr[3]), std::stod(lineStr[4]) };
        robots.emplace_back(c1, c2);
    }

    int64_t maxFree = 0;
    for (int i =0; i < width * height; ++i)
    {
        const int64_t thisFree = treeThreshold(robots, i, width, height);
        if (maxFree < thisFree)
        {
            print(robots, i, width, height);
            std::cout <<"Seconds " << i << " longest diagonal " << thisFree << std::endl;
            score = i;
            maxFree = thisFree;
        }
    }
    
    return score;
}