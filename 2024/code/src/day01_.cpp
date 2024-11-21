#include <days.h>


uint64_t adventDay01P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    uint8_t firstN = 0, lastN = 0;
    
    for (auto& line : in)
    {
       
        score += 0;
    }

    return score;
}

bool isNumber(std::string s, std::vector<std::string>& sol, const std::string regExp)
{
    sol = parseInputReg(s, regExp);
    return sol.size() > 0;
}

uint64_t adventDay01P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    uint8_t firstN = 0, lastN = 0;
    std::map<std::string, int> numbers =
    {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5},{"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    for (auto& line : in)
    {
        
        score += 0;
    }

    return score;
}