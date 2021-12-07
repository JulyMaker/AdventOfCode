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

using Pair = std::pair<int, int>;

long long adventDay05problem12021(std::vector<std::vector<Pair>> coordsSystem, Pair boardMax)
{
  std::vector<std::vector<int>> board(boardMax.first, std::vector<int>(boardMax.second, 0));
  int count=0;

  for (auto& coords : coordsSystem)
  {
    Pair pair1 = coords.at(0);
    Pair pair2 = coords.at(1);

    if (pair1.first == pair2.first)
    {
      int init = std::min(pair1.second, pair2.second);
      int finish = std::max(pair1.second, pair2.second);

      for (int i = init; i <= finish; i++)
      {
        board[i][pair1.first] += 1;
        if (board[i][pair1.first] == 2) count++;
      }
    }

    if (pair1.second == pair2.second)
    {
      int init = std::min(pair1.first, pair2.first);
      int finish = std::max(pair1.first, pair2.first);

      for (int i = init; i <= finish; i++)
      {
        board[pair1.second][i]+= 1;
        if (board[pair1.second][i] == 2) count++;
      }
    }
  }

  return count;
}


long long adventDay05problem22021(std::vector<std::vector<Pair>> coordsSystem, Pair boardMax)
{
  std::vector<std::vector<int>> board(boardMax.first, std::vector<int>(boardMax.second, 0));
  int count = 0;

  for (auto& coords : coordsSystem)
  {
    Pair pair1 = coords.at(0);
    Pair pair2 = coords.at(1);

    if (pair1.first == pair2.first)
    {
      int init = std::min(pair1.second, pair2.second);
      int finish = std::max(pair1.second, pair2.second);

      for (int i = init; i <= finish; i++)
      {
        board[i][pair1.first] += 1;
        if (board[i][pair1.first] == 2) count++;
      }
    }
    else if (pair1.second == pair2.second)
    {
      int init = std::min(pair1.first, pair2.first);
      int finish = std::max(pair1.first, pair2.first);

      for (int i = init; i <= finish; i++)
      {
        board[pair1.second][i] += 1;
        if (board[pair1.second][i] == 2) count++;
      }
    }
    else
    {
      int aux1 = -(pair1.first - pair2.first);
      int aux2 = std::abs(pair1.first - pair2.first);
      int aux3 = -(pair1.second - pair2.second);
      int aux4 = std::abs(pair1.second - pair2.second);

      Pair inc = { (aux1 /aux2 ), ( aux3 / aux4) };
      int indX = pair1.first;
      int indY = pair1.second;

      while(indX != pair2.first && indY != pair2.second)
      {
        board[indY][indX] += 1;
        if (board[indY][indX] == 2) count++;

        indX += inc.first;
        indY += inc.second;
      }

      board[indY][indX] += 1;
      if (board[indY][indX] == 2) count++;
    }
  }

  return count;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  std::smatch sm;
  std::regex regExp("(\\d+)[,|.](\\d+) -> (\\d+)[.|,](\\d+)");

  std::string line;
  std::vector<std::vector<Pair>> coordsSystem;
  
  int rowMax=0, colMax=0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (regex_search(line, sm, regExp))
    {
      int x1 = std::stoi(sm[1].str());
      int y1 = std::stoi(sm[2].str());
      int x2 = std::stoi(sm[3].str());
      int y2 = std::stoi(sm[4].str());

      rowMax = std::max(std::max(rowMax,x1), x2);
      colMax = std::max(std::max(colMax, y1), y2);

      std::vector<Pair> coords;
      coords.emplace_back(x1, y1);
      coords.emplace_back(x2, y2); 

      coordsSystem.push_back(coords);
    }  
  }

  infile.close();

  long long result = (problNumber == 1) ? adventDay05problem12021(coordsSystem, {++colMax, ++rowMax})
                                        : adventDay05problem22021(coordsSystem, {++colMax, ++rowMax});

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day05/input01.txt";
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