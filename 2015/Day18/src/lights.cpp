#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <valarray>
#include <functional>
#include <numeric>
#include <array>

#define FORALL(X,Y) for (int Y =1; Y <= N; ++Y) for (size_t X { 1 }; X <= N; ++X)

const int N = 100;
const int SPAN = N + 2;
using Grid = std::array <std::array <int, SPAN>, SPAN>;
static Grid grid[2], temp;

int sum(const Grid & a) {
  int suma= 0;
  FORALL(x, y) suma += a[y][x]; 
  
  return suma;
}

void process (int& y, std::string& line)
{
  int x = 0;
  ++y;

  for (auto && c : line)
    grid[1][y][++x] = ((c == '#') ? 1 : 0);
}

long long adventDay18problem12015()
{
  int prev = 0;
  int curr = 1;

  for (int i= 0; i < N; ++i) {
    std::swap(curr, prev);

    for (auto && row : temp)
      row.fill(0);
    FORALL(x, y) temp[y][x] += grid[prev][y][x - 1] + grid[prev][y][x] + grid[prev][y][x + 1];
    FORALL(x, y) grid[curr][y][x] = temp[y - 1][x] + temp[y][x] + temp[y + 1][x] - grid[prev][y][x];
    FORALL(x, y) grid[curr][y][x] = (grid[curr][y][x] == 3 || (grid[prev][y][x] && grid[curr][y][x] == 2));
  }

  return sum(grid[curr]);
}

long long adventDay18problem22015()
{
  int prev = 0;
  int curr = 1;
  grid[curr][1][1] = grid[curr][1][N] = grid[curr][N][1] = grid[curr][N][N] = 1;

  for (int i = 0; i < N; ++i) {
    std::swap(curr, prev);

    for (auto && row : temp)
      row.fill(0);
    FORALL(x, y) temp[y][x] += grid[prev][y][x - 1] + grid[prev][y][x] + grid[prev][y][x + 1];
    FORALL(x, y) grid[curr][y][x] = temp[y - 1][x] + temp[y][x] + temp[y + 1][x] - grid[prev][y][x];
    FORALL(x, y) grid[curr][y][x] = (grid[curr][y][x] == 3 || (grid[prev][y][x] && grid[curr][y][x] == 2));

    grid[curr][1][1] = grid[curr][1][N] = grid[curr][N][1] = grid[curr][N][N] = 1;
  }

  return sum(grid[curr]);
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  int y =0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(y, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay18problem12015()
                              : adventDay18problem22015();

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain txt path
  if (argc < 3)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The problem number isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}