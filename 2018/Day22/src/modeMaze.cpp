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
#include <tuple>
#include <iomanip>
#include <cctype> 
#include <random>
#include <valarray>
#include <thread>
#include <unordered_set>
#include <optional>
#include <deque>
#include <queue>
#include <ctype.h>

std::vector<int> split(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(std::stoi(text.substr(start, end - start)));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(std::stoi(text.substr(start)));
  return tokens;
}

int64_t adventDay22problem12018(std::ifstream& input)
{
  const int64_t MOD= 20183;

  std::string stringName;
  int64_t depth;
  input >> stringName >> depth;

  std::string target;
  input >> stringName >> target;
  std::vector<int> aux = split(target, ",");
  int64_t M= aux[0], N= aux[1];

  std::vector<std::vector< int64_t>> GI = std::vector<std::vector< int64_t >> (M + 1, std::vector<int64_t>(N + 1, 0)), EroLevel{ GI }; // (G)eological (I)ndexes and (E)rosion (L)evels
  for (int x=0; x <= M; ++x) 
    for (int y=0; y <= N; EroLevel[x][y] = (GI[x][y] + depth) % MOD, ++y)
      if (x == 0 && y == 0)
        GI[x][y] = 0;
      else if (x == 0)
        GI[x][y] = y * 48271;
      else if (y == 0)
        GI[x][y] = x * 16807;
      else
        GI[x][y] = EroLevel[x - 1][y] * EroLevel[x][y - 1];

  int64_t sum= 0;
  for (auto& erolv : EroLevel)
    std::transform(erolv.begin(), erolv.end(), erolv.begin(), [](auto& x) { return x % 3; }),
                    sum += std::accumulate(erolv.cbegin(), erolv.cend(), 0ULL);
  
  return sum;
}

class gear 
{
public:
  int x, y;
  // Type of gear == Type of cave where it 
  // cannot be used
  int type;
  int dist;
};

class cmpGear 
{
public:
  // Returning the reversed comparision, because priority_queue
  // returns the maximal element and Dijkstra needs the minimal
  // distance
  bool operator () (gear a, gear b) {
    return a.dist > b.dist;
  }
};

const int MAXN = 1000;
int  cave[MAXN][MAXN];
int  sol [MAXN][MAXN][3];
bool bio [MAXN][MAXN][3];

int64_t adventDay22problem22018(std::ifstream& input)
{
  const int TAM = 1000;
  const int XC = 16807;
  const int YC = 48271;
  const int64_t MOD = 20183;
  
  std::string stringName;
  int64_t d;
  input >> stringName >> d;
  
  std::string target;
  input >> stringName >> target;
  std::vector<int> aux = split(target, ",");
  int x = aux[1], y = aux[0];
  //////////////////////////////////////////////////////////////////////
  
  int smjx[] = { -1, 0, 1, 0 };
  int smjy[] = { 0, 1, 0, -1 };
  
  // Initialize the cave
  for (int i = 0; i < TAM; i++) 
  {
    for (int j = 0; j < TAM; j++) 
    {
      if (i == 0 && j == 0)
        cave[i][j] = 0;
      else if (i == x && j == y) 
        cave[i][j] = 0;
      else if (i == 0)
        cave[i][j] = (j * XC) % MOD;
      else if (j == 0)
        cave[i][j] = (i * YC) % MOD;
      else
        cave[i][j] = (cave[i - 1][j] * cave[i][j - 1]) % MOD;
  
      cave[i][j] = (cave[i][j] + d) % MOD;
    }
  }
  
  for (int i = 0; i < TAM; i++)
    for (int j = 0; j < TAM; j++)
      cave[i][j] %= 3;
  
  gear start;
  start.x = 0;
  start.y = 0;
  start.type = 1;
  start.dist = 0;
  
  std::priority_queue<gear, std::vector<gear>, cmpGear> pq;
  pq.push(start);
  
  while (!pq.empty() && !bio[x][y][1]) 
  {
    gear cur = pq.top();
    pq.pop();
  
    if (bio[cur.x][cur.y][cur.type]) continue;
  
    bio[cur.x][cur.y][cur.type] = true;
    sol[cur.x][cur.y][cur.type] = cur.dist;
  
    // Move around
    for (int i = 0; i < 4; i++) 
    {
      gear tmp;
  
      tmp.x = cur.x + smjx[i];
      tmp.y = cur.y + smjy[i];
      tmp.type = cur.type;
      tmp.dist = cur.dist + 1;
  
      if (tmp.x >= 0 && tmp.y >= 0 && cave[tmp.x][tmp.y] != tmp.type && !bio[tmp.x][tmp.y][tmp.type]) 
      {
        pq.push(tmp);
      }
    }
  
    // Switch gear
    for (int i = 0; i < 3; i++) 
    {
      gear tmp;
  
      tmp.x = cur.x;
      tmp.y = cur.y;
      tmp.type = i;
      tmp.dist = cur.dist + 7;
  
      if (cave[tmp.x][tmp.y] != tmp.type && !bio[tmp.x][tmp.y][tmp.type]) 
      {
        pq.push(tmp);
      }
    }
  }

  return sol[x][y][1];
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay22problem12018(infile)
                                        : adventDay22problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day22/input22.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return -1;
  }


  long long int result = 0;
  switch (problem)
  {
  case 1:
    result = readFile(fileName, problem);
    break;
  case 2:
    result = readFile(fileName, problem);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}