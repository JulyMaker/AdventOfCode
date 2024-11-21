#include <days.h>

void printGrid(std::vector<std::string>& in)
{
    for (int x = 0; x < in.size(); x++)
    {
        for (int y = 0; y < in[0].size(); y++)
        {
            std::cout << in[x][y];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

uint64_t north(std::vector<std::string>& in)
{
    uint64_t sum = 0;
    for (int y = 0; y < in[0].size(); y++)
    {
        int freeX = 0;
        for (int x = 0; x < in.size(); x++)
        {
            if (in[x][y] == '#')
                freeX = x + 1;
            else if (in[x][y] == 'O')
            {
                in[x][y] = '.';
                in[freeX][y] = 'O';
                sum += in.size() - freeX;
                freeX++;
            }
        }
    }

    return sum;
}

uint64_t adventDay14P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInput(input, '\n');

    score = north(in);

    return score;
}

constexpr int TOTAL = 1'000'000'000;

void west(std::vector<std::string>& in)
{
    for (int x = 0; x < in.size(); x++) 
    {
        int freeY = 0;
        for (int y = 0; y < in[0].size(); y++)
        {
            if (in[x][y] == '#')
                freeY = y + 1;
            else if (in[x][y] == 'O')
            {
                in[x][y] = '.';
                in[x][freeY] = 'O';
                freeY++;
            }
        }
    }
}

void south(std::vector<std::string>& in)
{
    for (int y= 0; y < in[0].size(); y++)
    {
        int freeX = in[0].size() - 1;
        for (int x = in.size() -1; x >= 0; x--)
        {
            if (in[x][y] == '#')
                freeX = x - 1;
            else if (in[x][y] == 'O')
            {
                in[x][y] = '.';
                in[freeX][y] = 'O';
                freeX--;
            }
        }
    }
}

uint64_t east(std::vector<std::string>& in)
{
    uint64_t sum = 0;
    for (int x = 0; x < in.size(); x++)
    {
        int freeY = in[0].size() - 1;
        for (int y = in[0].size() - 1; y >= 0; y--)
        {
            if (in[x][y] == '#')
                freeY = y - 1;
            else if (in[x][y] == 'O')
            {
                in[x][y] = '.';
                in[x][freeY] = 'O';
                sum+= in.size() - x;
                freeY--;
            }
        }
    }

    return sum;
}

uint64_t adventDay14P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    std::map<std::string, uint64_t> cache;
    for (int count = 0; count < TOTAL; count++)
    {
        north(in);
        west(in);
        south(in);
        score= east(in);

        std::string currentState;
        for (int x = 0; x < in.size(); x++)
                currentState+= in[x];


        if (auto repeat = cache.find(currentState); repeat != cache.end())
        {
            uint64_t loopOffset = repeat->second;
            uint64_t loopLength = count - loopOffset;

            count= TOTAL - (TOTAL - loopOffset) % loopLength;

            cache.clear();
        }

        cache[currentState] = count;
    }
    
    return score;
}