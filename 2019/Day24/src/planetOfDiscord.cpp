#include "utils.h"

bool checkInMap(int x, int y, int lines, int columns)
{
  return x >= 0 && y >= 0 && x < lines&& y < columns;
}

uint64_t adventDay24problem12019(std::ifstream& input)
{
	std::vector<std::vector<char>> map = parseInputChars(input);

	std::vector< std::vector<std::vector<char>>> visit;
	std::vector<std::vector<char>> newMap(map);
	std::vector<int> dirX{ -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	int bugs{ 0 };

	visit.push_back(map);
	while (true)
	{
		for (int l = 0; l < 5; l++)
		{
			for (int c = 0; c < 5; c++)
			{
				bugs = 0;
				for (int k = 0; k < 4; k++)
				{
					if (checkInMap(l + dirX[k], c + dirY[k], 5, 5) && (map[l + dirX[k]][c + dirY[k]] == '#'))
						bugs++;
				}

				if ((map[l][c] == '#') && (bugs != 1))
					newMap[l][c] = '.';

				if ((map[l][c] == '.') && ((bugs == 1) || (bugs == 2)))
					newMap[l][c] = '#';
			}
		}

		map = newMap;

		for (int it = 0; it < visit.size(); it++)
		{
			if (visit[it] == map)
			{
				int sum = 0;
				for (int l = 0; l < 5; l++)
				{
					for (int c = 0; c < 5; c++)
					{
						if (map[l][c] == '#')
						{
							sum += pow(2, l * 5 + c);
						}
					}
				}
				return sum;
			}
		}

		visit.push_back(map);
	}

	return 0;
}


uint64_t adventDay24problem22019(std::ifstream& input)
{
	std::vector<std::vector<char>> map = parseInputChars(input);
	const int minutes = 200;
	
	std::vector<std::vector<char>> emptyGrid(5, std::vector<char>(5, '.'));
	std::vector< std::vector<std::vector<char>>> levels;
	std::vector<int> dirX{ -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	int bugs = 0, lowestDepth{ minutes }, highestDepth{ minutes + 2 };

	emptyGrid[2][2] = '?';
	map[2][2] = '?';

	for (int i = 0; i <= minutes; i++)
		levels.push_back(emptyGrid);

	levels.push_back(map);
	for (int i = 0; i <= minutes; i++)
		levels.push_back(emptyGrid);

	std::vector< std::vector<std::vector<char>>> newLevels(levels);
	std::vector<std::vector<char>> newMap(emptyGrid);

	for (int it = 0; it < minutes; it++)
	{
		for (int lvl = lowestDepth; lvl <= highestDepth; lvl++)
		{
			newMap = levels[lvl];
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					bugs = 0;
					for (int k = 0; k < 4; k++)
					{
						if (checkInMap(i + dirX[k], j + dirY[k], 5, 5))
						{
							if (levels[lvl][i + dirX[k]][j + dirY[k]] == '?')
							{
								switch (k)
								{
								  case 0:
								  	for (int l = 0; l < 5; l++)
								  		if (levels[lvl + 1][4][l] == '#')	bugs++;
								  
								  	break;
								  
								  case 1:
								  	for (int l = 0; l < 5; l++)
								  		if (levels[lvl + 1][l][4] == '#')	bugs++;
								  
								  	break;
								  
								  case 2:
								  	for (int l = 0; l < 5; l++)
								  		if (levels[lvl + 1][l][0] == '#')	bugs++;
								  
								  	break;
								  
								  case 3:
								  	for (int l = 0; l < 5; l++)
								  		if (levels[lvl + 1][0][l] == '#')	bugs++;
								  
								  	break;
								}
							}
							else
							{
								if (levels[lvl][i + dirX[k]][j + dirY[k]] == '#')
									bugs++;
							}
						}
						else
						{
							if (levels[lvl - 1][2 + dirX[k]][2 + dirY[k]] == '#')
								bugs++;
						}
					}

					if ((levels[lvl][i][j] == '#') && (bugs != 1))
						newMap[i][j] = '.';

					if ((levels[lvl][i][j] == '.') && ((bugs == 1) || (bugs == 2)))
						newMap[i][j] = '#';
				}
			}
			newLevels[lvl] = newMap;
		}
		lowestDepth--;
		highestDepth++;
		levels = newLevels;
	}

	int countBugs = 0;
	for (int i = 0; i <= minutes * 2 + 1; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				if (levels[i][j][k] == '#')
					countBugs++;

	return countBugs;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "24";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay24problem12019(inputFile); break;
    case 2: result = adventDay24problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}