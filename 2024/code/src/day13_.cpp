#include <days.h>

using Mirrors = std::vector<std::vector<std::string>>;
using Mirror = std::vector<std::string>;

int reflectionLines(const Mirror& mirror) 
{
    for (int x = 0; x < mirror.size() - 1; x++) 
    {
        int incr= 0;
        while (x - incr >= 0 && x + incr + 1 < mirror.size() && 
               mirror[x - incr] == mirror[x + incr + 1])
            incr++;

        if (x - incr + 1 == 0 || x + incr + 1 == mirror.size())
            return x + 1;
    }

    return 0;
}

Mirror transposedMirror(Mirror mirror)
{
    Mirror transposedMirror(mirror[0].size());
    for (int y = 0; y < mirror[0].size(); y++)
        for (int x = 0; x < mirror.size(); x++)
            transposedMirror[y] += mirror[x][y];

    return transposedMirror;
}

uint64_t adventDay13P12024(std::ifstream& input)
{
    uint64_t score = 0;

    Mirrors mirrors;
    //readInput13_2024(input, mirrors);
    
    for (auto& mirror : mirrors) {
        uint64_t verticalLines = reflectionLines(mirror) * 100;
        score += (verticalLines > 0) ? verticalLines : reflectionLines(transposedMirror(mirror));
    }

    return score;
}

bool fixSmudge(std::string_view row1, std::string_view row2, bool& fixed) 
{
    if (fixed) return false;

    bool onediff= false;
    for (int i = 0; i < row1.size(); ++i)
    {
        if (row1[i] != row2[i])
        {
            if (onediff) return false;

            onediff = true;
        }
    }

    fixed = true;
    return true;
}

int reflectionLinesSmudge(const Mirror& mirror) 
{
    for (int x = 0; x < mirror.size() - 1; x++)
    {
        int incr = 0;
        bool fixed= false;

        while (x - incr >= 0 && x + incr + 1 < mirror.size()) 
        {
            if (!(mirror[x - incr] == mirror[x + incr + 1]) &&
                !fixSmudge(mirror[x - incr], mirror[x + incr + 1], fixed))
                break;

            incr++;
        }

        if ((x - incr + 1 == 0 || x + incr + 1 == mirror.size()) && fixed)
            return x + 1;
    }

    return 0;
}

uint64_t adventDay13P22024(std::ifstream& input)
{
    uint64_t score = 0;

    Mirrors mirrors;
    //readInput13_2024(input, mirrors);

    for (auto& mirror : mirrors) {
        uint64_t verticalLines = reflectionLinesSmudge(mirror) * 100;
        score +=  (verticalLines > 0)? verticalLines : reflectionLinesSmudge(transposedMirror(mirror));
    }

    return score;
}