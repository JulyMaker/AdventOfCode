#include <days.h>

using Grid = std::vector<std::string>;
using GridExtended = std::vector<std::vector<std::pair<char, bool>>>;

struct Coordinate 
{
	int x, y;

	Coordinate operator+(const Coordinate b) const
	{
		return { x + b.x, y + b.y };
	}
};

constexpr Coordinate up    = { -1,  0 };
constexpr Coordinate down  = {  1,  0 };
constexpr Coordinate left  = {  0, -1 };
constexpr Coordinate right = {  0,  1 };

static const std::vector<Coordinate> DIRS = { right, left, down, up };

size_t travelAux(GridExtended& grid, Coordinate pos)
{
	grid[pos.y][pos.x].second = true;
	size_t neighborsSum = 0;
	
	for (auto direction : DIRS)
	{
		auto nextPos = pos + direction;
		if (grid[nextPos.y][nextPos.x].first - grid[pos.y][pos.x].first == 1 && !grid[nextPos.y][nextPos.x].second)
			neighborsSum += travelAux(grid, nextPos);
	}
	
	return neighborsSum + (grid[pos.y][pos.x].first == '9');
}

size_t travel(GridExtended matrix, Coordinate pos) 
{
	return travelAux(matrix, pos);
}

uint64_t adventDay10P12025(std::ifstream& input)
{
    uint64_t score = 0;

	Grid map = parseInput(input,'\n');

	GridExtended auxMap;
	const std::pair<char, bool> basic = { 'Y', false };
	std::vector<Coordinate> start;
	int row = 1;
	int col = 1;

	std::vector<std::pair<char, bool>> basicVec = std::vector<std::pair<char, bool>>(map[0].size() + 2, basic);
	auxMap.push_back(basicVec); // First line

	for (auto& str : map)
	{
      static std::vector<std::pair<char, bool>> line(str.size() + 2, basic);

      auto line_it = line.begin() + 1;
	  col = 1;
	  for (char c : str)
	  {
		  line_it++->first = c;
		  if (c == '0') start.push_back({ col, row });
		  ++col;
	  }

	  auxMap.push_back(line);
	  ++row;
	}

	auxMap.push_back(basicVec); // Last line

	for (auto& pos : start)
	  score += travel(auxMap, pos);

    return score;
}

size_t travel2(GridExtended grid, Coordinate pos)
{
	grid[pos.y][pos.x].second = true;
	size_t neighborsSum = 0;

	for (auto direction : DIRS)
	{
		auto nextPos = pos + direction;
		if (grid[nextPos.y][nextPos.x].first - grid[pos.y][pos.x].first == 1 && !grid[nextPos.y][nextPos.x].second)
			neighborsSum += travel2(grid, nextPos);
	}

	return neighborsSum + (grid[pos.y][pos.x].first == '9');
}

uint64_t adventDay10P22025(std::ifstream& input)
{
    uint64_t score = 0;

	Grid map = parseInput(input, '\n');

	GridExtended auxMap;
	const std::pair<char, bool> basic = { 'Y', false };
	std::vector<Coordinate> start;
	int row = 1;
	int col = 1;

	std::vector<std::pair<char, bool>> basicVec = std::vector<std::pair<char, bool>>(map[0].size() + 2, basic);
	auxMap.push_back(basicVec); // First line

	for (auto& str : map)
	{
		static std::vector<std::pair<char, bool>> line(str.size() + 2, basic);

		auto line_it = line.begin() + 1;
		col = 1;
		for (char c : str)
		{
			line_it++->first = c;
			if (c == '0') start.push_back({ col, row });
			++col;
		}

		auxMap.push_back(line);
		++row;
	}

	auxMap.push_back(basicVec); // Last line

	for (auto& pos : start)
		score += travel2(auxMap, pos);

    return score;
}