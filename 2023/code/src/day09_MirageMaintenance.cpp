#include <days.h>

uint64_t adventDay09P12023(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInput(input, '\n');
    for (auto& lineStr : in)
    {
        std::vector<int> line = splitI(lineStr, " ");
        bool zero = std::all_of(line.begin(), line.end(), [](int x) { return x == 0; });
        while (!zero)
        {
            score+= line.back();
            for (int i = 0; i < line.size() - 1; i++)
                line[i] = line[i + 1] - line[i];

            line.pop_back();
            zero = std::all_of(line.begin(), line.end(), [](int x) { return x == 0; });
        }  
    }

    return score;
}

uint64_t adventDay09P22023(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<int> firsts;
    for (auto& lineStr : in)
    {
        std::vector<int> line = splitI(lineStr, " ");
        bool zero = std::all_of(line.begin(), line.end(), [](int x) { return x == 0; });
        while (!zero)
        {
            firsts.push_back(line[0]);
            for (int i = 0; i < line.size() - 1; i++)
                line[i] = line[i + 1] - line[i];

            line.pop_back();
            zero = std::all_of(line.begin(), line.end(), [](int x) { return x == 0; });
        }

        int result = 0;
        for (int i= firsts.size() - 1; i >= 0; i--)
            result = firsts[i] - result;

        score += result;
        firsts.clear();
    }

    return score;
}