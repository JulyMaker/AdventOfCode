#include <utils.h>

#define mp std::make_pair

std::pair<int, int> searchEnd(const std::vector<std::string>& grid)
{
  std::pair<int, int> aux = {0, 0};

  for(int row=0; row < grid.size(); row++)
    for (int col=0; col < grid[row].size(); col++)
      if (grid[row][col] == 'E')
        return aux = { row, col};

  return aux;
}

bool isOut(int row, int col, int h, int w) 
{
  return (row >= h || col >= w || row < 0 || col < 0);
}

uint64_t adventDay12problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<std::string> grid = parseInput(input, '\n');
  const int h = grid.size();
  const int w = grid[0].size();
  const int dx[4] = { 1, -1, 0, 0};
  const int dy[4] = { 0, 0, 1, -1};

  std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
  std::queue<std::pair<int, std::pair<int, int>>> road;

  std::pair<int, int> end = searchEnd(grid);
  grid[end.first][end.second] = 'z';
  visited[end.first][end.second] = true;

  road.push(mp(0, end));
  while (!road.empty()) 
  {
    int dist = road.front().first;
    int row = road.front().second.first;
    int col = road.front().second.second;
    road.pop();

    if (grid[row][col] == 'S')
      return dist;

    for (int i = 0; i < 4; i++) 
    {
      if (!isOut(row + dx[i], col + dy[i], h, w) && !visited[row + dx[i]][col + dy[i]]) 
      {
        char prev = (grid[row + dx[i]][col + dy[i]] == 'S') ? 'a' : grid[row + dx[i]][col + dy[i]];
        if (grid[row][col] - prev < 2) 
        {
          visited[row + dx[i]][col + dy[i]] = true;
          road.push(mp(dist + 1, mp(row + dx[i], col + dy[i])));
        }
      }
    }
  }

  return score;
}

uint64_t adventDay12problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  std::vector<std::string> grid = parseInput(input, '\n');
  const int h = grid.size();
  const int w = grid[0].size();
  const int dx[4] = { 1, -1, 0, 0 };
  const int dy[4] = { 0, 0, 1, -1 };

  std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
  std::queue<std::pair<int, std::pair<int, int>>> road;

  std::pair<int, int> end = searchEnd(grid);
  grid[end.first][end.second] = 'z';
  visited[end.first][end.second] = true;

  road.push(mp(0, end));
  while (!road.empty())
  {
    int dist = road.front().first;
    int row = road.front().second.first;
    int col = road.front().second.second;
    road.pop();

    if (grid[row][col] == 'S' || grid[row][col] == 'a')
      return dist;

    for (int i = 0; i < 4; i++)
    {
      if (!isOut(row + dx[i], col + dy[i], h, w) && !visited[row + dx[i]][col + dy[i]])
      {
        char prevChar = (grid[row + dx[i]][col + dy[i]] == 'S') ? 'a' : grid[row + dx[i]][col + dy[i]];
        if (grid[row][col] - prevChar < 2)
        {
          visited[row + dx[i]][col + dy[i]] = true;
          road.push(mp(dist + 1, mp(row + dx[i], col + dy[i])));
        }
      }
    }
  }

  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "12";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay12problem12022(inputFile); break;
    case 2: result = adventDay12problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}