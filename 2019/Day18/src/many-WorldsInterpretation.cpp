#include "utils.h"

const int letters = 26;

class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int steps = 0, int64_t visited = 0) : 
		x(x), y(y), steps(steps), visited(visited) {}

public:
	int x, y;
	int steps;
	int64_t visited;
};


void readInput(std::ifstream& input, std::vector<std::vector<char>>& map, Coordinate& startCoordinate)
{
	std::vector<char> v;
	std::string line;

	while (std::getline(input, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			v.push_back(line[i]);
			if (v[i] == '@')
			{
				startCoordinate.x = map.size();
				startCoordinate.y = i;
				v[i] = '.';
			}
		}
		map.push_back(v);
		v.clear();
	}
}


bool checkInMap(int x, int y, int lines, int columns)
{
	return x >= 0 && y >= 0 && x < lines&& y < columns;
}


int BFS(const std::vector<std::vector<char>>& map, const Coordinate& startCoordinate)
{
	std::set<std::tuple<int, int, int64_t>> repeated;
	std::vector<int> dirX{ -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	std::bitset<letters> auxVisited;
	std::queue<Coordinate> q;
	Coordinate curr;

	q.push(startCoordinate);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		auxVisited = curr.visited;

		if (auxVisited.all())
			return curr.steps;

		for (int i = 0; i < 4; i++)
		{
			if ((!checkInMap(curr.x, curr.y, map.size(), map[0].size())) || (map[curr.x + dirX[i]][curr.y + dirY[i]] == '#')
				|| repeated.find(std::make_tuple(curr.x + dirX[i], curr.y + dirY[i], curr.visited)) != repeated.end())
				continue;

			if (isupper(map[curr.x + dirX[i]][curr.y + dirY[i]]) && (!auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'A']))
				continue;


			if (islower(map[curr.x + dirX[i]][curr.y + dirY[i]]))
				auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'a'] = true;


			q.push(Coordinate(curr.x + dirX[i], curr.y + dirY[i], curr.steps + 1, auxVisited.to_ullong()));
			repeated.insert(std::make_tuple(curr.x + dirX[i], curr.y + dirY[i], auxVisited.to_ullong()));

			if (islower(map[curr.x + dirX[i]][curr.y + dirY[i]]))
				auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'a'] = false;

		}
	}
}

uint64_t adventDay18problem12019(std::ifstream& input)
{
	std::vector<std::vector<char>> map;
	Coordinate startCoordinate;

	readInput(input, map, startCoordinate);

	return BFS(map, startCoordinate);
}

void readInput2(std::ifstream& input, std::vector<std::vector<char>>& map, std::vector<Coordinate>& startCoordinates)
{
	std::vector<char> v;
	std::string line;
	Coordinate startCoordinate;

	while (std::getline(input, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			v.push_back(line[i]);
			if (v[i] == '@')
			{
				startCoordinate.x = map.size();
				startCoordinate.y = i;
				v[i] = '#';
			}
		}
		map.push_back(v);
		v.clear();
	}

	map[startCoordinate.x - 1][startCoordinate.y] = '#';
	map[startCoordinate.x][startCoordinate.y - 1] = '#';
	map[startCoordinate.x][startCoordinate.y + 1] = '#';
	map[startCoordinate.x + 1][startCoordinate.y] = '#';
	map[startCoordinate.x - 1][startCoordinate.y - 1] = '@';
	map[startCoordinate.x - 1][startCoordinate.y + 1] = '@';
	map[startCoordinate.x + 1][startCoordinate.y - 1] = '@';
	map[startCoordinate.x + 1][startCoordinate.y + 1] = '@';
	startCoordinates.push_back(Coordinate(startCoordinate.x - 1, startCoordinate.y - 1));
	startCoordinates.push_back(Coordinate(startCoordinate.x - 1, startCoordinate.y + 1));
	startCoordinates.push_back(Coordinate(startCoordinate.x + 1, startCoordinate.y - 1));
	startCoordinates.push_back(Coordinate(startCoordinate.x + 1, startCoordinate.y + 1));
}

void ignoreDoors(const std::vector<std::vector<char>>& map, std::vector<std::bitset<letters>>& visitedStart, const std::vector<Coordinate>& startCoordinates)
{
	for (int x = 0; x < map.size(); x++)
		for (int y = 0; y < map[0].size(); y++)
			if (islower(map[x][y]))
			{
				visitedStart[0][map[x][y] - 'a'] = !((x <= startCoordinates[0].x) && (y <= startCoordinates[0].y));
				visitedStart[1][map[x][y] - 'a'] = !((x <= startCoordinates[1].x) && (y >= startCoordinates[1].y));
				visitedStart[2][map[x][y] - 'a'] = !((x >= startCoordinates[2].x) && (y <= startCoordinates[2].y));
				visitedStart[3][map[x][y] - 'a'] = !((x >= startCoordinates[3].x) && (y >= startCoordinates[3].y));
			}
}


uint64_t adventDay18problem22019(std::ifstream& input)
{
	std::vector<std::vector<char>> map;
	std::vector<std::bitset<letters>> visitedStart(4);
	std::vector<Coordinate> startCoordinates;

	readInput2(input, map, startCoordinates);

	ignoreDoors(map, visitedStart, startCoordinates);

	int fewestSteps = 0;
	for (int i = 0; i < 4; i++)
	{
		startCoordinates[i].visited = visitedStart[i].to_ullong();
		fewestSteps += BFS(map, startCoordinates[i]);
	}


	return fewestSteps;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "18";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay18problem12019(inputFile); break;
    case 2: result = adventDay18problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}