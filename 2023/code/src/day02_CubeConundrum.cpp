#include <days.h>

uint64_t adventDay02P12023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;
    
    const int REDCUBES = 12, GREENCUBES = 13, BLUECUBES = 14;
    std::map<std::string, int> colours =
    {
        {"red", REDCUBES}, {"green", GREENCUBES}, {"blue", BLUECUBES}
    };

    std::vector<std::string> in = parseInputReg(input, "Game (\\d+): (.*)");
    for(unsigned int i= 0; i <= in.size() - 3; i+= 3)
    {
        bool valid = true;

        const int id = std::stoi(in[i + 1]);
        std::vector<std::string> sets = splitS(in[i + 2], ";");
        
        for(auto& subset : sets)
        {       
            if (!valid) break;

            std::vector<std::string> subSetSplit = splitS(subset, ",");
            for (auto& cubes : subSetSplit)
            {
                std::vector<std::string> cubesSplit = splitS(cubes, " ");
                if (std::stoi(cubesSplit[0]) > colours[cubesSplit[1]])
                {
                    valid = false;
                    break;
                }
            }
        }
        
        if (valid) score += id;
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}

uint64_t adventDay02P22023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    std::map<std::string, int> colours =
    {
        {"red", 1}, {"green", 2}, {"blue", 3}
    };

    std::vector<std::string> in = parseInputReg(input, "Game (\\d+): (.*)");
    for (unsigned int i = 0; i <= in.size() - 3; i += 3)
    {
        int minRed= 0, minGreen= 0, minBlue = 0;

        std::vector<std::string> sets = splitS(in[i + 2], ";");
        for (auto& subset : sets)
        {
            std::vector<std::string> subSetSplit = splitS(subset, ",");
            for (auto& cubes : subSetSplit)
            {
                std::vector<std::string> cubesSplit = splitS(cubes, " ");

                switch (colours[cubesSplit[1]])
                {
                case 1: if (std::stoi(cubesSplit[0]) > minRed)   minRed = std::stoi(cubesSplit[0]);
                    break;
                case 2: if (std::stoi(cubesSplit[0]) > minGreen) minGreen = std::stoi(cubesSplit[0]);
                    break;
                case 3: if (std::stoi(cubesSplit[0]) > minBlue)  minBlue = std::stoi(cubesSplit[0]);
                    break;
                }
            }
        }

        score += minRed * minBlue * minGreen;
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}