#include <days.h>


uint64_t adventDay01P12023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;


    std::vector<std::string> in = parseInput(input, '\n');
    uint8_t firstN = 0, lastN = 0;
    
    for (auto& line : in)
    {
        firstN = 0, lastN = 0;
        bool noNumber = false;

        for (unsigned int i=0; i < line.size(); i++)
        {
            if(isdigit(line[i]))
            {
                firstN = line[i] - '0';
                break;
            }

            if (i == line.size() - 1) noNumber = true;
        }

        if (!noNumber)
        {
            for (unsigned int i = line.size() -1; i >= 0; i--)
            {
                if (isdigit(line[i]))
                {
                    lastN = line[i] - '0';
                    break;
                }

                if (i == line.size() - 1) noNumber = true;
            }
        }


        score += 10 * firstN + lastN;
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}

bool isNumber(std::string s, std::vector<std::string>& sol, const std::string regExp)
{
    sol = parseInputReg(s, regExp);
    return sol.size() > 0;
}

uint64_t adventDay01P22023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    std::vector<std::string> in = parseInput(input, '\n');
    uint8_t firstN = 0, lastN = 0;
    std::map<std::string, int> numbers =
    {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5},{"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    for (auto& line : in)
    {
        firstN = 0, lastN = 0;
        bool noNumber = false;

        for (unsigned int i = 0; i < line.size(); i++)
        {
            if (isdigit(line[i]))
            {
                firstN = line[i] - '0';
                break;
            }
            
            std::vector<std::string> number;
            if(isNumber(line.substr(i, line.size()), number, "(one|two|three|four|five|six|seven|eight|nine)(\\w+)"))
            {
                firstN = numbers[number[1]];
                break;
            }

            if (i == line.size() - 1) noNumber = true;
        }

        if (!noNumber)
        {
            for (unsigned int i = line.size() - 1; i >= 0; i--)
            {
                if (isdigit(line[i]))
                {
                    lastN = line[i] - '0';
                    break;
                }

                std::vector<std::string> number;
                if (isNumber(line.substr(0, i+1), number, "(\\w+)(one|two|three|four|five|six|seven|eight|nine)"))
                {
                    lastN = numbers[number[2]];
                    break;
                }

                if (i == line.size() - 1) noNumber = true;
            }
        }


        score += 10 * firstN + lastN;
    }

 
    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}