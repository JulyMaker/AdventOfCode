#include <days.h>

uint64_t getSum(std::vector<std::vector<char>>& grid, const int ROWLIMIT, const int COLLIMIT, const int initialX, const int initialY)
{
    int suma = 0;

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;

            if ( (ROWLIMIT > initialX + x >= 0) && (COLLIMIT > initialY + y >= 0) )
            {
                if (std::isdigit(grid[initialX + x][initialY + y]))
                {
                    int auxY = initialY + y;
                    while ( auxY - 1 >= 0 && std::isdigit(grid[initialX + x][auxY - 1]))
                        auxY--;
                    
                    int number = grid[initialX + x][auxY] - '0';
                    grid[initialX + x][auxY] = '.';

                    while (auxY + 1 < COLLIMIT && std::isdigit(grid[initialX + x][auxY + 1]))
                    {
                        auxY++;
                        number= 10 * number + (grid[initialX + x][auxY] - '0');
                        grid[initialX + x][auxY] = '.';
                    }
     
                    suma+= number;
                }
            } 
        }
    }
        

    return suma;
}

uint64_t adventDay03P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> grid = parseInputChars(input);
    const int ROWLIMIT = grid.size();
    const int COLLIMIT = grid[0].size();
    
    for(int x=0; x < ROWLIMIT; x++)
    {
        for (int y = 0; y < COLLIMIT; y++)
        {
            if (grid[x][y] != '.' && !std::isdigit(grid[x][y]))
            {
                score+= getSum(grid, ROWLIMIT, COLLIMIT, x, y);
            }
        }
    }
        
    return score;
}

uint64_t getGears(std::vector<std::vector<char>>& grid, const int ROWLIMIT, const int COLLIMIT, const int initialX, const int initialY)
{
    int suma = 1;
    int parts = 0;

    for (int x = -1; x <= 1; x++)
    {
        if (parts > 2) break;

        for (int y = -1; y <= 1; y++)
        {
            if (parts > 2) break;
          
            if (x == 0 && y == 0)
                continue;

            if ((ROWLIMIT > initialX + x >= 0) && (COLLIMIT > initialY + y >= 0))
            {
                if (std::isdigit(grid[initialX + x][initialY + y]))
                {
                    int auxY = initialY + y;
                    while (auxY - 1 >= 0 && std::isdigit(grid[initialX + x][auxY - 1]))
                        auxY--;

                    int number = grid[initialX + x][auxY] - '0';
                    grid[initialX + x][auxY] = '.';

                    while (auxY + 1 < COLLIMIT && std::isdigit(grid[initialX + x][auxY + 1]))
                    {
                        auxY++;
                        number = 10 * number + (grid[initialX + x][auxY] - '0');
                        grid[initialX + x][auxY] = '.';
                    }

                    suma *= number;
                    parts++;
                }
            }
        }
    }

    return (parts == 2) ? suma : 0;;
}

uint64_t adventDay03P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::vector<char>> grid = parseInputChars(input);
    const int ROWLIMIT = grid.size();
    const int COLLIMIT = grid[0].size();

    for (int x = 0; x < ROWLIMIT; x++)
    {
        for (int y = 0; y < COLLIMIT; y++)
        {
            if (grid[x][y] == '*')
            {
                score += getGears(grid, ROWLIMIT, COLLIMIT, x, y);
            }
        }
    }

    return score;
}