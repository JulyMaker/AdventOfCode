#include <days.h>

struct Coordinate
{
    double x, y;

    Coordinate operator+(const Coordinate b) const
    {
        return { x + b.x, y + b.y };
    }

    bool operator<(const Coordinate& b) const {
        return (x == b.x) ? y < b.y : x < b.x;
    }

    bool operator!=(const Coordinate& b) const {
        return (x != b.x) || (y != b.y);
    }
};

std::vector<double> minCost(const Coordinate& buttonA, const Coordinate& buttonB, const Coordinate& prize)
{
    double D  = (buttonA.x * buttonB.y) - (buttonA.y * buttonB.x);
    double Dx = (prize.x   * buttonB.y) - (prize.y   * buttonB.x);
    double Dy = (buttonA.x * prize.y  ) - (buttonA.y * prize.x  );

    double x = Dx / D;
    double y = Dy / D;

    return { x, y };
}

uint64_t adventDay13P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    for (int line = 0; line < in.size() - 2; line += 3)
    {
        std::vector<std::string> buttonA = parseInputReg(in[line], R"(Button A: X\+(\d+), Y\+(\d+))");
        std::vector<std::string> buttonB = parseInputReg(in[line + 1], R"(Button B: X\+(\d+), Y\+(\d+))");
        std::vector<std::string> prize = parseInputReg(in[line + 2], R"(Prize: X\=(\d+), Y\=(\d+))");

        std::vector<double> result = minCost({ std::stod(buttonA[1]), std::stod(buttonA[2]) }, 
                                             { std::stod(buttonB[1]), std::stod(buttonB[2]) }, 
                                             { std::stod(prize[1])  , std::stod(prize[2])   });
        double a = result[0];
        double b = result[1];

        if ((a < 100 && b < 100) && ((int)a == a && (int)b == b))
            score += (a * 3) + (b * 1);
    }

    return score;
}

 
uint64_t adventDay13P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    for (int line = 0; line < in.size() - 2; line += 3)
    {
        std::vector<std::string> buttonA = parseInputReg(in[line], R"(Button A: X\+(\d+), Y\+(\d+))");
        std::vector<std::string> buttonB = parseInputReg(in[line + 1], R"(Button B: X\+(\d+), Y\+(\d+))");
        std::vector<std::string> prize = parseInputReg(in[line + 2], R"(Prize: X\=(\d+), Y\=(\d+))");

        std::vector<double> result = minCost({ std::stod(buttonA[1]), std::stod(buttonA[2]) },
                                             { std::stod(buttonB[1]), std::stod(buttonB[2]) },
                                             { std::stod(prize[1]) + 10000000000000  , std::stod(prize[2]) + 10000000000000 });
        double a = result[0];
        double b = result[1];

        if (((uint64_t) a == a && (uint64_t) b == b))
            score += (a * 3) + (b * 1);
    }

    return score;
}