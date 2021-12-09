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
#include <deque>


long long adventDay09problem12021(std::vector<std::vector<int>>& matrix)
{
  long long total = 0;

  for(unsigned int i=0; i< matrix.size(); i++)
    for (unsigned int j = 0; j < matrix[0].size(); j++)
    {
      bool lowPoints = true;

      if (i > 0)                                 lowPoints = matrix[i -1][j] > matrix[i][j];
      if (i < matrix.size() -1 && lowPoints)     lowPoints = matrix[i + 1][j] > matrix[i][j];
      if (j > 0 && lowPoints)                    lowPoints = matrix[i][j - 1] > matrix[i][j];
      if (j < matrix[0].size() - 1 && lowPoints) lowPoints = matrix[i][j + 1] > matrix[i][j];
      
      if (lowPoints)
        total += matrix[i][j] + 1;
    }
  
  return total;
}

int calculateBasin(int x, int y, std::vector<std::vector<int>>& matrix)
{
  int num = matrix[x][y];
  if (num == 9 || num == -1) return 0;

  matrix[x][y] = -1;
  int total = 1;

  if (x > 0)                    total += calculateBasin(x - 1, y, matrix);
  if (x < matrix.size() - 1)    total += calculateBasin(x + 1, y, matrix);
  if (y > 0)                    total += calculateBasin(x, y - 1, matrix);
  if (y < matrix[0].size() - 1) total += calculateBasin(x, y + 1, matrix);

  return total;
}

long long adventDay09problem22021(std::vector<std::vector<int>>& matrix)
{
  std::vector<long> basins (3);

  for (unsigned int i = 0; i < matrix.size(); i++)
    for (unsigned int j = 0; j < matrix[0].size(); j++)
    {
      bool lowPoints = true;

      if (i > 0)                                 lowPoints = matrix[i - 1][j] > matrix[i][j];
      if (i < matrix.size() - 1 && lowPoints)    lowPoints = matrix[i + 1][j] > matrix[i][j];
      if (j > 0 && lowPoints)                    lowPoints = matrix[i][j - 1] > matrix[i][j];
      if (j < matrix[0].size() - 1 && lowPoints) lowPoints = matrix[i][j + 1] > matrix[i][j];

      if (lowPoints)
      {
        std::vector<std::vector<int>> matrixAux = matrix;
        basins.push_back( calculateBasin(i, j, matrixAux) );
      }
    }

  std::sort(basins.begin(), basins.end());
  int size = basins.size();

  return basins[size-3] * basins[size-2] * basins[size-1];
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  
  std::vector<std::vector<int>> matrix;
  std::string line;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      std::vector<int> aux;
      for (auto& l : line)
      {
        std::string num(1, l);
        aux.push_back(std::stoi(num));
      }
        
      matrix.push_back(aux);
    }
  }

  infile.close();


  long long result = (problNumber == 1) ? adventDay09problem12021(matrix)
                                        : adventDay09problem22021(matrix);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day09/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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