#include <days.h>

using Grid = std::vector<std::vector<char>>;

struct Coord {
	int64_t x, y;

	int64_t distance(const Coord& c2)
	{
		return std::abs(x - c2.x) + std::abs(y - c2.y);
	}
};

void expandColY(std::vector<Coord>& galaxies, const int y, const int expandY, const int64_t TIMES)
{
	for (auto& galaxy : galaxies)
		if ((galaxy.y - expandY) > y)
			galaxy.y += TIMES - 1;
}

uint64_t adventDay11P12023(std::ifstream& input)
{
    uint64_t score = 0;

	const int64_t TIMES = 2;
    Grid grid = parseInputChars(input);
	std::vector<Coord> galaxies;
	int expandX = 0;
	for (int x=0; x < grid.size(); x++)
	{
		bool emptySpace = std::all_of(grid[x].begin(), grid[x].end(), [](char c) { return c == '.'; });
		if (emptySpace)
			expandX+= TIMES - 1;
		else{
			for (int y = 0; y < grid[x].size(); y++)
			{
				if (grid[x][y] == '#')
				{
					Coord galaxy = {x+expandX, y};
					galaxies.push_back(galaxy);
				}
			}
		}
	}

	int expandY = 0;
	for (int y = 0; y < grid[0].size(); y++)
	{
		bool emptySpaceY = true;
		for (int x = 0; x < grid.size(); x++)
		{
			if(grid[x][y] == '#')
			{
				emptySpaceY = false;
				break;
			}
		}

		if (emptySpaceY) 
		{
			expandColY(galaxies, y, expandY, TIMES);
			expandY+= TIMES - 1;
		}	
	}

	for(int i=0; i < galaxies.size() - 1; i++)
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			score+= galaxies[i].distance(galaxies[j]);
		}

    return score;
}

uint64_t adventDay11P22023(std::ifstream& input)
{
    uint64_t score = 0;
	const int64_t TIMES = 1000000; //Problem
	//const int64_t TIMES = 100;     //Example

	Grid grid = parseInputChars(input);
	std::vector<Coord> galaxies;
	int expandX = 0;
	for (int x = 0; x < grid.size(); x++)
	{
		bool emptySpace = std::all_of(grid[x].begin(), grid[x].end(), [](char c) { return c == '.'; });
		if (emptySpace)
			expandX+= TIMES - 1;
		else {
			for (int y = 0; y < grid[x].size(); y++)
			{
				if (grid[x][y] == '#')
				{
					Coord galaxy = { x + expandX, y };
					galaxies.push_back(galaxy);
				}
			}
		}
	}

	int expandY = 0;
	for (int y = 0; y < grid[0].size(); y++)
	{
		bool emptySpaceY = true;
		for (int x = 0; x < grid.size(); x++)
		{
			if (grid[x][y] == '#')
			{
				emptySpaceY = false;
				break;
			}
		}

		if (emptySpaceY)
		{
			expandColY(galaxies, y, expandY, TIMES);
			expandY+= TIMES - 1;
		}
	}

	for (int i = 0; i < galaxies.size() - 1; i++)
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			score += galaxies[i].distance(galaxies[j]);
		}

    return score;
}