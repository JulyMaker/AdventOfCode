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

using VI  = std::vector< int >; 
using VVI = std::vector< VI >;
struct Answer { int power{ 0 }, row{ 0 }, col{ 0 }, size{ 0 }; };
const int N{ 301 };

long long adventDay11problem120182(int serialNumber)
{
  Answer ans = {};
  VVI G(N, VI(N, 0));

  for (int row{ 1 }; row < N; ++row)
    for (int col{ 1 }; col < N; ++col)
      G[row][col] = (((((col + 10) * row) + serialNumber) * (col + 10)) / 100 % 10) - 5;

  for (int row{ 1 }; row < N; ++row) 
    for (int col{ 1 }; col < N; ++col)
      for (int size{ 2 }, power{ 0 }; size < N; ++size, power = 0)
        if (row < N - size && col < N - size)
          for (int i{ row }; i <= row + size; ++i)
            for (int j{ col }; j <= col + size; ++j, ans = (ans.power < power) ? Answer{ power, row, col, size + 1 } : ans)
              power += G[i][j];
  
  std::cout << "( " << ans.col << ", " << ans.row << " ), size: " << ans.size << std::endl;

  return ans.size;
}

long long adventDay11problem12018(int serialNumber)
{
  const int GRIDSIZE = 300;
  int sumGrid[GRIDSIZE + 1][GRIDSIZE + 1];

  int powerLevel, rackID;
  for (int j = 0; j < GRIDSIZE + 1; j++)
  {
    for (int i = 0; i < GRIDSIZE + 1; i++) 
    {
      if (i == 0 || j == 0) 
      { 
        sumGrid[i][j] = 0; 
        continue; 
      }
      rackID = i + 10;
      powerLevel = rackID * (j)+serialNumber;
      powerLevel *= rackID;
      powerLevel = ((powerLevel / 100) % 10) - 5;
      sumGrid[i][j] = powerLevel + sumGrid[i][j - 1] + sumGrid[i - 1][j] - sumGrid[i - 1][j - 1];
    }
  }

  int maxSum = INT_MIN, sum, maxX = 0, maxY = 0, maxSumSize = 0;

  for (int j = 3; j < GRIDSIZE + 1; j++) 
  {
    for (int i = 3; i < GRIDSIZE + 1; i++) 
    {
      sum = sumGrid[i][j] - sumGrid[i - 3][j] - sumGrid[i][j - 3] + sumGrid[i - 3][j - 3];
      if (sum > maxSum) 
      {
        maxSum = sum;
        maxX = i - 2; 
        maxY = j - 2;
      }
    }
  }

  std::cout << "Answer: " << maxX << "," << maxY << std::endl;

  return 0;
}

long long adventDay11problem22018(int serialNumber)
{
  const int GRIDSIZE = 300;
  int sumGrid[GRIDSIZE + 1][GRIDSIZE + 1];

  int powerLevel, rackID;
  for (int j = 0; j < GRIDSIZE + 1; j++)
  {
    for (int i = 0; i < GRIDSIZE + 1; i++)
    {
      if (i == 0 || j == 0)
      {
        sumGrid[i][j] = 0;
        continue;
      }
      rackID = i + 10;
      powerLevel = rackID * (j)+serialNumber;
      powerLevel *= rackID;
      powerLevel = ((powerLevel / 100) % 10) - 5;
      sumGrid[i][j] = powerLevel + sumGrid[i][j - 1] + sumGrid[i - 1][j] - sumGrid[i - 1][j - 1];
    }
  }

  int maxSum = INT_MIN, sum, maxX = 0, maxY = 0, maxSumSize = 0;

  for (int size = 1; size <= 300; size++) 
  {
    for (int j = size; j < GRIDSIZE + 1; j++)
    {
      for (int i = size; i < GRIDSIZE + 1; i++)
      {
        sum = sumGrid[i][j] - sumGrid[i - size][j] - sumGrid[i][j - size] + sumGrid[i - size][j - size];
        if (sum > maxSum) 
        {
          maxSum = sum;
          maxX = i - size + 1; 
          maxY = j - size + 1;
          maxSumSize = size;
        }
      }
    }
  }

  std::cout << "Answer: " << maxX << "," << maxY << "," << maxSumSize << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  int num = 0;
  infile >> num;

  long long result = (problNumber == 1) ? adventDay11problem12018(num)
                                        : adventDay11problem22018(num);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day11/input11.txt";
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