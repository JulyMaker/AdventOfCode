#include <days.h>

size_t xmas_count(std::vector<std::vector<char>>& xMasGrid, int i, int j)
{
    const char xmas[] = "XMAS";

    size_t count = 0;
    for (int dy = -1; dy <= 1; dy++) 
    {
        for (int dx = -1; dx <= 1; dx++) 
        {
            if (dy == 0 && dx == 0) continue;
            bool isXmas = true;
            for (int k = 1; k <= 3; k++) 
            {
                int newi = i + k * dx;
                int newj = j + k * dy;
                if (newi < 0 || newj < 0 || static_cast<size_t>(newi) >= xMasGrid.size() || static_cast<size_t>(newj) >= xMasGrid[0].size()) 
                {
                    isXmas = false;
                    break;
                }

                if (xMasGrid[newi][newj] != xmas[k]) isXmas = false;
            }

            if (isXmas) count++;
        }
    }
    return count;
}


uint64_t adventDay04P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> xMasGrid = parseInputChars(input);
    size_t ROWLIMIT = xMasGrid.size();
    size_t COLLIMIT = xMasGrid[0].size();

    for (size_t i = 0; i < ROWLIMIT; i++)
        for (size_t j = 0; j < COLLIMIT; j++)
            if (xMasGrid[i][j] == 'X')
                score += ::xmas_count(xMasGrid, i, j);

    return score;
}

bool isXmas(std::vector<std::vector<char>>& xMasGrid, int i, int j) {
    char d1 = xMasGrid[i - 1][j - 1];
    char d2 = xMasGrid[i + 1][j + 1];

    char o1 = xMasGrid[i - 1][j + 1];
    char o2 = xMasGrid[i + 1][j - 1];

    return (d1 == 'M' && d2 == 'S' && o1 == 'M' && o2 == 'S')
        || (d1 == 'M' && d2 == 'S' && o1 == 'S' && o2 == 'M')
        || (d1 == 'S' && d2 == 'M' && o1 == 'M' && o2 == 'S')
        || (d1 == 'S' && d2 == 'M' && o1 == 'S' && o2 == 'M');
}


uint64_t adventDay04P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> xMasGrid = parseInputChars(input);
    size_t ROWLIMIT = xMasGrid.size();
    size_t COLLIMIT = xMasGrid[0].size();

    for (size_t i = 1; i < ROWLIMIT - 1; i++)
        for (size_t j = 1; j < COLLIMIT - 1; j++)
            if (xMasGrid[i][j] == 'A' && isXmas(xMasGrid, i, j))
                score ++;


    return score;
}
