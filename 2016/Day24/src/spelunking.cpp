#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <array>
#include <mutex>
#include <numeric>
#include <intrin.h>


struct Point 
{
  int x, y;

  bool operator==(const Point& p1) const 
  {
    return y == p1.y && x == p1.x;
  }

  Point& operator+=(const Point& p1) 
  {
    return y += p1.y, x += p1.x, *this;
  }
};

Point operator+(const Point& p1, const Point& p2) 
{
  Point p3 = p1;

  return p3 += p2;
}

static const Point DIRS[4] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

void process(std::vector<std::pair<int, Point>>& locsByIndex, int& y, std::string& line)
{
  int x = 0;
  for (char c : line)
  {
    if (c != '.' && c != '#')
    {
      locsByIndex.push_back(std::make_pair(c - '0', Point{ x, y }));
    }
    ++x;
  }
  ++y;
}

long long adventDay24problem12016(std::vector<std::pair<int, Point>>& locsByIndex, std::vector<std::string>& maze)
{     
  const int POINTS = locsByIndex.size();
  const int WIDTH  = maze[0].size();
  const int HEIGHT = maze.size();

  std::vector<std::vector<int>> dist(POINTS, std::vector<int>(POINTS, -1));
  
  std::vector<Point> queue, next;
  
  for (int i0 = 0; i0 < POINTS; ++i0)
  {
    for (int i1 = i0 + 1; i1 < POINTS; ++i1)
    {
      if (dist[i0][i1] == -1)
      {
        std::vector<std::vector<bool>> visited(WIDTH, std::vector<bool>(HEIGHT, false));
        const Point START = locsByIndex[i0].second;
        const Point  GOAL = locsByIndex[i1].second;
        bool visitGoal = visited[GOAL.x][GOAL.y];
        int         steps = 1;

        queue.clear(), next.clear(), queue.emplace_back(START);

        while(  queue.size() != 0 && !visitGoal)
        {
          for (const auto& q : queue)
          {
            for (const auto& d : DIRS) {
              Point n{ q + d };
              if (n.x >= WIDTH || n.y >= HEIGHT) continue;
              if (maze[n.y][n.x] != '#' && !visited[n.x][n.y])
              {
                if (n == GOAL)
                  dist[i0][i1] = dist[i1][i0] = steps;

                next.emplace_back(n);
                visited[n.x][n.y] = true;
                visitGoal = visited[GOAL.x][GOAL.y];
              }
            }
          }
          queue.swap(next), next.clear(), ++steps;
        }
      }
    }
  }

  std::vector<int> order(POINTS - 1);
  std::iota(order.begin(), order.end(), 1);
  int min= INT_MAX;

  do min = std::min(min, std::accumulate(order.begin(), order.end()-1,
    dist[0][order[0]],
    [&](int sum, int& idx) 
  {
    return sum + dist[idx][*(&idx + 1)];
  }));
  while (std::next_permutation(order.begin(), order.end()));


  return min;
}

long long adventDay24problem22016(std::vector<std::pair<int, Point>>& locsByIndex, std::vector<std::string>& maze)
{ 
  const int POINTS = locsByIndex.size();
  const int WIDTH = maze[0].size();
  const int HEIGHT = maze.size();

  std::vector<std::vector<int>> dist(POINTS, std::vector<int>(POINTS, -1));

  std::vector<Point> queue, next;

  for (int i0 = 0; i0 < POINTS; ++i0)
  {
    for (int i1 = i0 + 1; i1 < POINTS; ++i1)
    {
      if (dist[i0][i1] == -1)
      {
        std::vector<std::vector<bool>> visited(WIDTH, std::vector<bool>(HEIGHT, false));
        const Point START = locsByIndex[i0].second;
        const Point  GOAL = locsByIndex[i1].second;
        bool visitGoal = visited[GOAL.x][GOAL.y];
        int         steps = 1;

        queue.clear(), next.clear(), queue.emplace_back(START);

        while (queue.size() != 0 && !visitGoal)
        {
          for (const auto& q : queue)
          {
            for (const auto& d : DIRS) {
              Point n{ q + d };
              if (n.x >= WIDTH || n.y >= HEIGHT) continue;
              if (maze[n.y][n.x] != '#' && !visited[n.x][n.y])
              {
                if (n == GOAL)
                  dist[i0][i1] = dist[i1][i0] = steps;

                next.emplace_back(n);
                visited[n.x][n.y] = true;
                visitGoal = visited[GOAL.x][GOAL.y];
              }
            }
          }
          queue.swap(next), next.clear(), ++steps;
        }
      }
    }
  }

  std::vector<int> order(POINTS - 1);
  std::iota(order.begin(), order.end(), 1);
  int min = INT_MAX;

  do min = std::min(min, std::accumulate(order.begin(), order.end()-1,
    dist[0][order[0]] + dist[0][order[POINTS - 2]],
    [&](int sum, int& idx)
  {
    return sum + dist[idx][*(&idx + 1)];
  }));
  while (std::next_permutation(order.begin(), order.end()));


  return min;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
 
  std::vector<std::pair<int, Point>> locsByIndex;
  std::vector<std::string> maze;
  int y = 0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(locsByIndex, y, line);
    maze.push_back(line);
  }
  infile.close();

  std::sort(locsByIndex.begin(), locsByIndex.end(), [](const std::pair<int, Point> &a, const std::pair<int, Point> &b) { return (a.first < b.first); });
  result = (problNumber == 1) ? adventDay24problem12016(locsByIndex, maze)
                              : adventDay24problem22016(locsByIndex, maze);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  const int N = 0;
 if (argc < 3 - N)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2 - N]) < 1) || (std::stoi(argv[2 - N]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2-N]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}