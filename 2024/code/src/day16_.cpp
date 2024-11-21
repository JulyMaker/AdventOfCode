#include <days.h>

using Grid = std::vector<std::vector<char>>;
using DIR = std::pair<int, int>;
using POS = std::pair<int, int>;

struct Node {
	POS pos;
	DIR dir;

	bool operator==(const Node& p2) const {
		return (pos == p2.pos && dir == p2.dir);
	}

	bool operator!=(const Node& p2) const {
		return (pos != p2.pos || dir != p2.dir);
	}

	bool operator<(const Node& p2) const {
		return (pos < p2.pos);
	}

	Node operator+(const DIR& dir) const {
		return Node{ {pos.first + dir.first, pos.second + dir.second}, dir };
	}
};

struct NodeHash {
	std::size_t operator()(const Node& node) const {
		std::size_t hashPos = std::hash<POS>()(node.pos);
		std::size_t hashDir = std::hash<DIR>()(node.dir);

		return hashPos ^ (hashDir + 0x9e3779b9 + (hashPos << 6) + (hashPos >> 2));
	}
};

constexpr DIR UP = { -1,  0 };
constexpr DIR DOWN = { 1,  0 };
constexpr DIR LEFT = { 0, -1 };
constexpr DIR RIGHT = { 0,  1 };

void printGrid(Grid grid, std::unordered_set<Node, NodeHash>& set)
{
	for (auto& g : grid)
		for (auto& c : g)
			c = '.';

	for (auto& node : set)
	{
		auto [x, y] = node.pos;
		grid[x][y] = '#';
	}

	for (auto& g : grid)
	{
		for (auto& c : g)
			std::cout << c;

		std::cout << std::endl;
	}
	std::cout << std::endl;
		
}

uint64_t energizesTiles(const Grid& grid, const POS& pos, const DIR& dir)
{
	std::unordered_set<Node, NodeHash> posanddir;
	std::stack<Node> toExplore;
	std::unordered_set<POS> visited;

	toExplore.emplace(Node{ pos, dir });
	while (!toExplore.empty())
	{
		Node newPos = toExplore.top();
		toExplore.pop();

		auto [x, y] = newPos.pos;
		// Out of grid or pos and dir repeat
		if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || posanddir.contains(newPos)) continue;

		posanddir.insert(newPos);
		visited.insert(newPos.pos);

		DIR dir = newPos.dir;
		char c = grid[x][y];
		switch (c)
		{
		case '|':
			if (dir == LEFT || dir == RIGHT)
			{
				toExplore.emplace(newPos + UP);
				toExplore.emplace(newPos + DOWN);
			}
			else
				toExplore.emplace(newPos + dir);
			break;
		case '-':
			if (dir == DOWN || dir == UP)
			{
				toExplore.emplace(newPos + LEFT);
				toExplore.emplace(newPos + RIGHT);
			}
			else
				toExplore.emplace(newPos + dir);
			break;
		case '/':
			if (dir == DOWN)
				toExplore.emplace(newPos + LEFT);
			else if (dir == RIGHT)
				toExplore.emplace(newPos + UP);
			else if (dir == LEFT)
				toExplore.emplace(newPos + DOWN);
			else
				toExplore.emplace(newPos + RIGHT);
			break;
		case '\\':
			if (dir == DOWN)
				toExplore.emplace(newPos + RIGHT);
			else if (dir == RIGHT)
				toExplore.emplace(newPos + DOWN);
			else if (dir == LEFT)
				toExplore.emplace(newPos + UP);
			else
				toExplore.emplace(newPos + LEFT);
			break;
		default:
			toExplore.emplace(newPos + dir);
		}
	}

	return visited.size();
}

uint64_t adventDay16P12024(std::ifstream& input)
{
    uint64_t score = 0;

	Grid grid = parseInputChars(input);
	score = energizesTiles(grid, {0 , 0}, RIGHT);

    return score;
}

uint64_t adventDay16P22024(std::ifstream& input)
{
    uint64_t score = 0;

	Grid grid = parseInputChars(input);

	// Top - Bottom - Left - Right
	for (int i = 0; i < grid.size(); i++)
	{
		score= std::max(score, energizesTiles(grid, { 0, i }, DOWN));
		score= std::max(score, energizesTiles(grid, { grid.size() - 1, i }, UP));
		score= std::max(score, energizesTiles(grid, { i, 0 }, RIGHT));
		score= std::max(score, energizesTiles(grid, { i, grid[0].size() - 1 }, LEFT));
	}
		
    return score;
}