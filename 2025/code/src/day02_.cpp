#include <days.h>

uint64_t adventDay02P12025(std::ifstream& input)
{
    uint64_t score = 0;
    
    std::vector<std::string> levels = parseInput(input,'\n');
    for (auto& level : levels)
    {
        bool safe = true;
        int pos = 0;
        int maskIncreDecre = 0; // 00 - safe, 01 - Incre, 10 - Decre, 11 - Unsafe

        std::vector<int> levelInt = splitI(level, " ");
        while(safe && (pos < levelInt.size() - 1))
        {
            int diff = levelInt[pos + 1] - levelInt[pos] ;

            if (std::abs(diff) < 1 || std::abs(diff) > 3)
                safe = false;
            else
            {
                if (diff > 0)
                    maskIncreDecre |= 0b01; // Incre
                else if (diff < 0)
                    maskIncreDecre |= 0b10; // Decre

                if (maskIncreDecre == 0b11)
                    safe = false;
            }

            pos++;
        }

        score += safe;
    }

    return score;
}

bool isSafe(const std::vector<int>& levels, int& pos) 
{
    int maskIncreDecre = 0; // 00 - safe, 01 - Incre, 10 - Decre, 11 - Unsafe
    for (size_t i = 0; i < levels.size() - 1; ++i) 
    {
        pos = i;
        int diff = levels[i + 1] - levels[i];
        if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;
        if (diff > 0)
            maskIncreDecre |= 0b01; // Incre
        else if (diff < 0)
            maskIncreDecre |= 0b10; // Decre
        if (maskIncreDecre == 0b11) return false;
    }
    return true;
}

uint64_t adventDay02P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> levels = parseInput(input, '\n');
    int aux=0;
    for (auto& level : levels)
    {
        int pos = 0;
        aux++;
        std::vector<int> levelInt = splitI(level, " ");
        if (isSafe(levelInt, pos)) 
        {
            ++score;
            continue;
        }

        bool isSafeWithRemoval = false;
        if (pos == 0) pos++;
        for (size_t i = pos - 1; i < levelInt.size(); ++i) 
        {
            std::vector<int> modifiedLevel = levelInt;
            modifiedLevel.erase(modifiedLevel.begin() + i);
            if (isSafe(modifiedLevel, pos)) 
            {
                isSafeWithRemoval = true;
                break;
            }
        }

        if (isSafeWithRemoval) ++score;
    }

    return score;
}