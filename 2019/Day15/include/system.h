#include <utils.h>

class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

public:
	int x, y;
};


class State
{
public:
	State(std::vector<int64_t> integers, Coordinate droid, int64_t currPos, int64_t relativeBase) : 
		integers(integers), droid(droid), currPos(currPos), relativeBase(relativeBase) {}

public:
	std::vector<int64_t> integers;
	Coordinate droid;
	int64_t currPos;
	int64_t relativeBase;
};


class Node
{
public:
	Node(int x = 0, int y = 0, int steps = 0) : x(x), y(y), steps(steps) {}

public:
	int x, y;
	int steps;
};


void setPosModes(std::vector<int64_t>& integers, int64_t currPos, int64_t relativeBase, int64_t& posMode1, int64_t& posMode2, int64_t& posMode3, int64_t opcode)
{
	if (currPos + 3 >= integers.size())
	{
		integers.resize(currPos + 4);
	}

	switch (integers[currPos] / 100 % 10)
	{
	  case 0:
	  	posMode1 = integers[currPos + 1];
	  	break;
	  
	  case 1:
	  	posMode1 = currPos + 1;
	  	break;
	  
	  case 2:
	  	posMode1 = relativeBase + integers[currPos + 1];
	  	break;
	}

	switch (integers[currPos] / 1000 % 10)
	{
	  case 0:
	  	posMode2 = integers[currPos + 2];
	  	break;
	  
	  case 1:
	  	posMode2 = currPos + 2;
	  	break;
	  
	  case 2:
	  	posMode2 = relativeBase + integers[currPos + 2];
	  	break;
	}

	switch (integers[currPos] / 10000 % 10)
	{
	  case 0:
	  	posMode3 = integers[currPos + 3];
	  	break;
	  
	  case 1:
	  	posMode3 = currPos + 3;
	  	break;
	  
	  case 2:
	  	posMode3 = relativeBase + integers[currPos + 3];
	  	break;
	}

	if (posMode1 >= integers.size())
		integers.resize(posMode1 + 1);

	if (posMode2 >= integers.size() && ((opcode == 1) || (opcode == 2) || (opcode == 5) || (opcode == 6) || (opcode == 7) || (opcode == 8)))
		integers.resize(posMode2 + 1);

	if ((posMode3 >= integers.size()) && ((opcode == 1) || (opcode == 2) || (opcode == 7) || (opcode == 8)))
		integers.resize(posMode3 + 1);
}


void intCodeProgram(std::vector<int64_t>& integers, const int64_t input, std::vector<std::vector<char>>& map, Coordinate& droid, int64_t& currPos, int64_t& relativeBase, Coordinate& oxygenSystem)
{
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;

	while (integers[currPos] != 99)
	{
		setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3, integers[currPos] % 100);

		switch (integers[currPos] % 100)
		{
		  case 1:
		  	integers[posMode3] = integers[posMode2] + integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 2:
		  	integers[posMode3] = integers[posMode2] * integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 3:
		  	integers[posMode1] = input;
		  	currPos = currPos + 2;
		  	break;
		  
		  case 4:
		  	switch (integers[posMode1])
		  	{
		  	  case 0:
		  	  	switch (input)
		  	  	{
		  	  	  case 1:
		  	  	  	map[droid.x - 1][droid.y] = '#';
		  	  	  	break;
		  	  	  
		  	  	  case 2:
		  	  	  	map[droid.x + 1][droid.y] = '#';
		  	  	  	break;
		  	  	  
		  	  	  case 3:
		  	  	  	map[droid.x][droid.y - 1] = '#';
		  	  	  	break;
		  	  	  
		  	  	  case 4:
		  	  	  	map[droid.x][droid.y + 1] = '#';
		  	  	  	break;
		  	  	}
		  	  	break;
		  	  
		  	  case 1:
		  	  	switch (input)
		  	  	{
		  	  	  case 1:
		  	  	  	droid.x--;
		  	  	  	break;
		  	  	  
		  	  	  case 2:
		  	  	  	droid.x++;
		  	  	  	break;
		  	  	  
		  	  	  case 3:
		  	  	  	droid.y--;
		  	  	  	break;
		  	  	  
		  	  	  case 4:
		  	  	  	droid.y++;
		  	  	  	break;
		  	  	}
		  	  	map[droid.x][droid.y] = '.';
		  	  	break;
		  	  
		  	  case 2:
		  	  	oxygenSystem = droid;
		  	  	break;
		  	}
		  
		  	currPos = currPos + 2;
		  	return;
		  
		  case 5:
		  	currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 6:
		  	currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 7:
		  	integers[posMode3] = integers[posMode1] < integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 8:
		  	integers[posMode3] = integers[posMode1] == integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 9:
		  	relativeBase += integers[posMode1];
		  	currPos = currPos + 2;
		  	break;
		}
	}
}


Coordinate findOxygenSystem(std::vector<int64_t>& integers, std::vector<std::vector<char>>& map)
{
	std::vector<int> dirX{ 2,-1,1,0,0 };
	std::vector<int> dirY{ 2,0,0,-1,1 };
	std::queue<State> states;
	Coordinate droid(map.size() / 2, map.size() / 2), oxygenSystem;
	State currState(integers, droid, 0, 0);
	int64_t auxCurrPos = 0, auxRelativeBase = 0;

	states.push(State(integers, droid, 0, 0));
	map[droid.x][droid.y] = '.';

	while (!states.empty())
	{
		currState = states.front();
		states.pop();

		for (int moveCommand = 1; moveCommand <= 4; moveCommand++)
		{
			if (map[currState.droid.x + dirX[moveCommand]][currState.droid.y + dirY[moveCommand]] != '-')
				continue;

			integers = currState.integers;
			droid = currState.droid;
			auxCurrPos = currState.currPos;
			auxRelativeBase = currState.relativeBase;

			intCodeProgram(integers, moveCommand, map, droid, auxCurrPos, auxRelativeBase, oxygenSystem);

			if (map[currState.droid.x + dirX[moveCommand]][currState.droid.y + dirY[moveCommand]] == '.')
			{
				states.push(State(integers, Coordinate(currState.droid.x + dirX[moveCommand], currState.droid.y + dirY[moveCommand]), auxCurrPos, auxRelativeBase));
			}
		}
	}

	return oxygenSystem;
}


int64_t BFS(std::vector<std::vector<char>>& map, const Coordinate oxygenSystem)
{
	std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map.size(), false));
	std::queue<Node> queue;
	std::vector<int> dirX{ 2,-1,1,0,0 };
	std::vector<int> dirY{ 2,0,0,-1,1 };
	queue.push(Node(map.size() / 2, map.size() / 2, 1));
	visited[map.size() / 2][map.size() / 2] = true;

	Node currNode;
	while (!queue.empty())
	{
		currNode = queue.front();
		queue.pop();

		if ((currNode.x == oxygenSystem.x) && (currNode.y == oxygenSystem.y))
		{
			return currNode.steps;
			break;
		}
		else
		{
			for (int i = 1; i <= 4; i++)
			{
				if ((map[currNode.x + dirX[i]][currNode.y + dirY[i]] == '.') && (!visited[currNode.x + dirX[i]][currNode.y + dirY[i]]))
				{
					queue.push(Node(currNode.x + dirX[i], currNode.y + dirY[i], currNode.steps + 1));
					visited[currNode.x + dirX[i]][currNode.y + dirY[i]] = true;
				}
			}
		}
	}
}

int64_t BFS2(std::vector<std::vector<char>>& map, const Coordinate oxygenSystem)
{
	std::vector<std::vector<bool>> visited(5000, std::vector<bool>(5000, false));
	std::vector<Coordinate> locationsToFill;
	std::vector<Coordinate> nextLocationsToFill;
	std::vector<int> dirX{ 2,-1,1,0,0 };
	std::vector<int> dirY{ 2,0,0,-1,1 };
	int minutes = 0;

	nextLocationsToFill.push_back(oxygenSystem);
	visited[oxygenSystem.x][oxygenSystem.y] = true;

	while (nextLocationsToFill.size() > 0)
	{
		minutes++;
		locationsToFill = nextLocationsToFill;
		nextLocationsToFill.clear();

		for (const auto& currLocation : locationsToFill)
		{
			for (int i = 1; i <= 4; i++)
			{
				if ((map[currLocation.x + dirX[i]][currLocation.y + dirY[i]] == '.') && (!visited[currLocation.x + dirX[i]][currLocation.y + dirY[i]]))
				{
					nextLocationsToFill.push_back(Coordinate(currLocation.x + dirX[i], currLocation.y + dirY[i]));
					visited[currLocation.x + dirX[i]][currLocation.y + dirY[i]] = true;
				}
			}
		}
	}

	return minutes;
}