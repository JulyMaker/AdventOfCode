#include <days.h>

using Grid = std::vector<std::vector<char>>;
using GridDis = std::vector<std::vector<int>>;

struct Position {
	int x, y;

	Position operator+(const Position& p2) const {
		return Position(x + p2.x, y + p2.y);
	}

	bool operator!=(const Position& p2) const {
		return (x != p2.x || y != p2.y);
	}
};

constexpr Position up    = { -1,  0 };
constexpr Position down  = {  1,  0 };
constexpr Position left  = {  0, -1 };
constexpr Position right = {  0,  1 };

std::vector<char> SYMBOLS = { '|', '-', 'L', 'J', '7', 'F' };

std::vector<Position> getConnectedPipes(Grid& grid, const Position& position)
{
	std::array<Position, 2> candidatePipes;
	char c = grid[position.x][position.y];
	switch (c)
	{
	  case '|':
	  	candidatePipes[0] = position + up;
	  	candidatePipes[1] = position + down;
	  	break;
	  case '-':
	  	candidatePipes[0] = position + left;
	  	candidatePipes[1] = position + right;
	  	break;
	  case 'L':
	  	candidatePipes[0] = position + up;
	  	candidatePipes[1] = position + right;
	  	break;
	  case 'J':
	  	candidatePipes[0] = position + up;
	  	candidatePipes[1] = position + left;
	  	break;
	  case '7':
	  	candidatePipes[0] = position + down;
	  	candidatePipes[1] = position + left;
	  	break;
	  case 'F':
	  	candidatePipes[0] = position + down;
	  	candidatePipes[1] = position + right;
	  	break;
	}

	std::vector<Position> connectedPipes;
	for (const Position& candidate : candidatePipes)
	{
		if(candidate.x >= 0 && candidate.x < grid.size() && candidate.y >= 0 && candidate.y < grid[0].size())
			connectedPipes.push_back(candidate);
	}

	return connectedPipes;
}

Position getSPipe(Grid& grid)
{
	Position sPosition = {0 , 0};
	for (int i = 0; i < grid.size(); i++)
	{
		auto it = std::find(grid[i].begin(), grid[i].end(), 'S');

		if (it != grid[i].end())
		{
			sPosition = { i, (int)std::distance(grid[i].begin(), it) };
			break;
		}
	}
	
	for (char pipeType : SYMBOLS)
	{
		grid[sPosition.x][sPosition.y] = pipeType;

		std::vector<Position> connectedPipes = getConnectedPipes(grid, sPosition);

		bool areConnectedPipesValid = connectedPipes.size() == 2;
		if (!areConnectedPipesValid)
			continue;

		for (const Position& connectedPipe : connectedPipes)
		{
			char c = grid[connectedPipe.x][connectedPipe.y];
			switch (c)
			{
			case '|':
				if (connectedPipe != (sPosition + down) && connectedPipe != (sPosition + up))
					areConnectedPipesValid = false;
				break;
			case '-':
				if (connectedPipe != (sPosition + left) && connectedPipe != (sPosition + right))
					areConnectedPipesValid = false;
				break;
			case 'L':
				if (connectedPipe != (sPosition + down) && connectedPipe != (sPosition + left))
					areConnectedPipesValid = false;
				break;
			case 'J':
				if (connectedPipe != (sPosition + down) && connectedPipe != (sPosition + right))
					areConnectedPipesValid = false;
				break;
			case '7':
				if (connectedPipe != (sPosition + up) && connectedPipe != (sPosition + right))
					areConnectedPipesValid = false;
				break;
			case 'F':
				if (connectedPipe != (sPosition + up) && connectedPipe != (sPosition + left))
					areConnectedPipesValid = false;
				break;
			case '.':
				areConnectedPipesValid = false;
				break;
			}
		}

		if (areConnectedPipesValid)
			return sPosition;
	}
}

uint64_t adventDay10P12024(std::ifstream& input)
{
    uint64_t score = 0;

	Grid grid = parseInputChars(input);

	Position sPosition = getSPipe(grid);

	GridDis distances( grid.size(), std::vector<int>(grid[0].size(), -1));
	distances[sPosition.x][sPosition.y] = 0;

	std::queue<std::pair<Position, Position>> toExplore;
	for (const Position& connectedPipe : getConnectedPipes(grid, sPosition))
		toExplore.emplace(sPosition, connectedPipe);


	while (!toExplore.empty())
	{
		auto [from, to] = toExplore.front();
		toExplore.pop();

		if (distances[to.x][to.y] != -1)
			continue;

		distances[to.x][to.y] = distances[from.x][from.y] + 1;

		score = (distances[to.x][to.y] > score)? distances[to.x][to.y] : score;

		for (const Position& connectedPipe : getConnectedPipes(grid, to))
			toExplore.emplace(to, connectedPipe);
	}

    return score;
}

void printGrid(const Grid& grid)
{
	for (int x = 0; x < grid.size(); ++x)
	{
		for (int y = 0; y < grid[0].size(); ++y)
		{
			std::cout << grid[x][y];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

uint64_t adventDay10P22024(std::ifstream& input)
{
    uint64_t score = 0;

	Grid grid = parseInputChars(input);

	Position sPosition = getSPipe(grid);

	GridDis distances(grid.size(), std::vector<int>(grid[0].size(), -1));
	distances[sPosition.x][sPosition.y] = 0;

	std::queue<std::pair<Position, Position>> toExplore;
	for (const Position& connectedPipe : getConnectedPipes(grid, sPosition))
		toExplore.emplace(sPosition, connectedPipe);


	while (!toExplore.empty())
	{
		auto [from, to] = toExplore.front();
		toExplore.pop();

		if (distances[to.x][to.y] != -1)
			continue;

		distances[to.x][to.y] = distances[from.x][from.y] + 1;

		for (const Position& connectedPipe : getConnectedPipes(grid, to))
			toExplore.emplace(to, connectedPipe);
	}

	for (int x = 0; x < grid.size(); ++x)
		for (int y = 0; y < grid[0].size(); ++y)
		{
			char c = grid[x][y];
			if (c != '.' && distances[x][y] == -1)
				grid[x][y] = '.';
			
		}
	//printGrid(grid);

	Grid bigGrid{ grid.size()*2, std::vector<char>(grid[0].size()*2,' ') };

	// Border to zero
	for (int y = 0; y < bigGrid[0].size(); ++y)
	{
		bigGrid[0][y] = '0';
		bigGrid[bigGrid.size() - 1][y] = '0';
	}
	for (int x = 0; x < bigGrid.size(); ++x)
	{
		bigGrid[x][0] = '0';
		bigGrid[x][bigGrid[0].size() - 1] = '0';
	}

	// Pipes and I
	for (int x = 0; x < grid.size(); ++x)
		for (int y = 0; y < grid[0].size(); ++y)
		{
			char c = grid[x][y];
			if (c != '.' && distances[x][y] != -1)
			{
				bigGrid[x*2][y*2] = c;
				continue;
			}

			if (x == 0 || x == grid.size() - 1 || y == 0 || y == grid[0].size() - 1)
				continue;

			bigGrid[x*2][y*2] = 'I';
		}


	for (int x = 0; x < grid.size(); ++x)
	{
		for (int y = 0; y < grid[0].size(); ++y)
		{
			if (y < grid[0].size() - 1)
			{
				char westPipe = grid[x][y];
				char eastPipe = grid[x][y + 1];
				switch (westPipe)
				{
				  case '-':
				  case 'L':
				  case 'F':
				  	switch (eastPipe)
				  	{
				  	  case '-':
				  	  case 'J':
				  	  case '7':
				  	  	bigGrid[x*2][y*2 + 1] = 'X';
				  	  	break;
				  	}
				  	break;
				}
			}

			if (x < grid.size() - 1)
			{
				char northPipe = grid[x][y];
				char southPipe = grid[x+1][y];
				switch (northPipe)
				{
				  case '|':
				  case '7':
				  case 'F':
					switch (southPipe)
					{
					  case '|':
					  case 'J':
					  case 'L':
					  	bigGrid[x*2 + 1][y*2] = 'X';
					  	break;
					}
					break;
				}
			}
		}
	}

	//printGrid(bigGrid);
	// Fill with zeros
	for (int x = 0; x < bigGrid.size(); ++x)
	{
		for (int y = 0; y < bigGrid[0].size(); ++y)
		{
			char c = bigGrid[x][y];
			if (c != '0')
				continue;

			Position currentPos{ x, y };
			std::stack<Position> toFill;
			toFill.emplace(currentPos + up);
			toFill.emplace(currentPos + left);
			toFill.emplace(currentPos + down);
			toFill.emplace(currentPos + right);
			while (!toFill.empty())
			{
				Position nextPosition = toFill.top();
				toFill.pop();

				bool isIn = nextPosition.x >= 0 && nextPosition.x < bigGrid.size() && nextPosition.y >= 0 && nextPosition.y < bigGrid[0].size();
				if (!isIn)
					continue;

				char c = bigGrid[nextPosition.x][nextPosition.y];
				if (c != ' ' && c != 'I')
					continue;

				bigGrid[nextPosition.x][nextPosition.y] = '0';
				toFill.emplace(nextPosition + up);
				toFill.emplace(nextPosition + left);
				toFill.emplace(nextPosition + down);
				toFill.emplace(nextPosition + right);
			}
		}
	}

	//printGrid(bigGrid);
	for(auto& b: bigGrid)
		score+= std::ranges::count(b, 'I');

    return score;
}