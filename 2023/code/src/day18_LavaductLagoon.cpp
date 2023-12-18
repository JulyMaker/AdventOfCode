#include <days.h>


struct Point
{
    int64_t x, y;

    Point operator+(Point p2) {
        return { x + p2.x, y + p2.y };
    }

    Point operator*(int64_t times) {
        return { x * times, y * times };
    }
};

std::map<char, Point> instruc = { {'R', {0, 1 } }, {'L', { 0, -1 } }, {'D', { 1, 0 } }, {'U', { -1, 0 } } };

uint64_t adventDay18P12023(std::ifstream& input)
{
    uint64_t score = 0;

    int shoelace= 0;
    uint64_t perimeter= 0;
    Point position{0, 0};

    std::vector<std::string> in= parseInputReg(input, "(.*) (\\d+) .*");
    for (int i=0; i < in.size(); i+=3)
    {
        char dir = in[i + 1][0];
        int times = std::stoi(in[i + 2]);

        Point next = position + instruc[dir] * times;
        shoelace+= (next.x + position.x) * (next.y - position.y);
        perimeter+= times;
        position= next;
    }
    
    score = std::abs(shoelace) / 2 + perimeter / 2 + 1; // gridArea

    return score;
}

char numdirMap[] = { 'R', 'D', 'L', 'U' };

uint64_t adventDay18P22023(std::ifstream& input)
{
    uint64_t score = 0;

    int64_t shoelace = 0;
    int64_t perimeter = 0;
    Point position{ 0, 0 };

    std::vector<std::string> in = parseInputReg(input, ".* \\d+ \\(#(.*)\\)");
    for (int i = 0; i < in.size(); i += 2)
    {
        std::string hex= in[i + 1];

        char dir = numdirMap[hex.back() - '0'];
        hex.pop_back();

        char* end;
        int64_t times = std::strtoll(hex.c_str(), &end, 16);
        
        Point next = position + instruc[dir] * times;
        shoelace+= (next.x + position.x) * (next.y - position.y);
        perimeter+= times;
        position = next;
    }
    
    score = std::abs(shoelace) / 2 + perimeter / 2 + 1; // gridArea

    return score;
}