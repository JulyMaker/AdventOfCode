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


std::vector<std::string> parseLines(std::ifstream& input)
{
  std::vector<std::string> lines;

  for (std::string line; getline(input, line);)
  {
    if (line != "")
      lines.push_back(line);
  }

  return lines;
}

char newAcre(const std::vector<std::string>& lca, const int x, const int y, int& woodedCount, int& lumberyardCount)
{
  int neighbourCounts[3] = { 0 }; // open, wooded, lumberyard
  for (int yy = std::max(y - 1, 0); yy <= std::min(y + 1, (int)lca.size() - 1); yy++) 
  {
    for (int xx = std::max(x - 1, 0); xx <= std::min(x + 1, (int)lca[yy].size() - 1); xx++) 
    {
      if (yy == y && xx == x) continue;
      else if (lca[yy][xx] == '.') neighbourCounts[0]++;
      else if (lca[yy][xx] == '|') neighbourCounts[1]++;
      else if (lca[yy][xx] == '#') neighbourCounts[2]++;
    }
  }

  switch (lca[y][x]) 
  {
    case '.':
      if (neighbourCounts[1] >= 3) {
        woodedCount++;
        return '|';
      }
      else return '.';
    case '|':
      if (neighbourCounts[2] >= 3) {
        woodedCount--;
        lumberyardCount++;
        return '#';
      }
      else return '|';
    case '#':
      if (neighbourCounts[2] >= 1 && neighbourCounts[1] >= 1) return '#';
      else {
        lumberyardCount--;
        return '.';
      }
    default:
      return lca[y][x];
  }
}

int64_t adventDay18problem12018(std::ifstream& input)
{
  std::vector<std::string> lumberCollectionArea = parseLines(input);
  std::vector<std::string> updatedArea(lumberCollectionArea);

  int woodedCount = 0;
  int lumberyardCount = 0;
  for (int j = 0; j < lumberCollectionArea.size(); j++) 
  {
    for (int i = 0; i < lumberCollectionArea[j].size(); i++) 
    {
      if (lumberCollectionArea[j][i] == '|') 
        woodedCount++;
      else if (lumberCollectionArea[j][i] == '#') 
        lumberyardCount++;
    }
  }

  for (int min = 0; min < 10; min++) 
  {
    for (int j = 0; j < lumberCollectionArea.size(); j++) 
    {
      for (int i = 0; i < lumberCollectionArea[j].length(); i++)
        updatedArea[j][i] = newAcre(lumberCollectionArea, i, j, woodedCount, lumberyardCount);
    }
    lumberCollectionArea = updatedArea;
  }

  return woodedCount * lumberyardCount;
}

int64_t adventDay18problem22018(std::ifstream& input)
{
  std::vector<std::string> lumberCollectionArea = parseLines(input);
  std::vector<std::string> updatedArea(lumberCollectionArea);

  int woodedCount = 0;
  int lumberyardCount = 0;
  for (int j = 0; j < lumberCollectionArea.size(); j++)
  {
    for (int i = 0; i < lumberCollectionArea[j].size(); i++)
    {
      if (lumberCollectionArea[j][i] == '|')
        woodedCount++;
      else if (lumberCollectionArea[j][i] == '#')
        lumberyardCount++;
    }
  }

  std::map<std::vector<std::string>, int> seen;
  bool repeated = false;

  for (int min = 0; min < 1e9; min++) 
  {
    for (int j = 0; j < lumberCollectionArea.size(); j++) 
    {
      for (int i = 0; i < lumberCollectionArea[j].length(); i++)
        updatedArea[j][i] = newAcre(lumberCollectionArea, i, j, woodedCount, lumberyardCount);
    }
    if (!repeated) 
    {
      if (seen.find(updatedArea) != seen.end()) 
      {
        repeated = true;
        min = 1e9 - ((int)(1e9 - min) % (min - seen[updatedArea]));
      }
      else seen[updatedArea] = min;
    }
    lumberCollectionArea = updatedArea;
  }

  return woodedCount * lumberyardCount;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay18problem12018(infile)
                                        : adventDay18problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day18/input18.txt";
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