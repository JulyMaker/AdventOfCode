#include <days.h>


uint64_t adventDay03P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> mulInst = searchInputReg(input, R"(mul\((\d{1,3}),(\d{1,3})\))");
    
    for (auto& instruction : mulInst)
    {
        std::vector<std::string> instNum = parseInputReg(instruction, R"(mul\((\d{1,3}),(\d{1,3})\))");
        score += std::stoll(instNum[1]) * std::stoll(instNum[2]);
    }
        
    return score;
}

uint64_t adventDay03P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> mulInst = searchInputReg(input, R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    bool doit = true;
    for (auto& instruction : mulInst)
    {
        if (instruction == "do()" || instruction == "don't()")
        {
            doit = (instruction == "do()")? true: false;
            continue;
        }

        if (doit)
        {
          std::vector<std::string> instNum = parseInputReg(instruction, R"(mul\((\d{1,3}),(\d{1,3})\))");
          score += std::stoll(instNum[1]) * std::stoll(instNum[2]);
        }
    }


    return score;
}