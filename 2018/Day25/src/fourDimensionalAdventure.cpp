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

struct Stea
{
  int x, y, z, t;
};

Stea allStars[2000];
std::vector<int> allMuc[2000];
int viz[2000];


int parseInput(std::ifstream& infile)
{
  std::string line;
  int noStars = 0;

  while (!infile.eof())
  {
    getline(infile, line);
    if (line != "")
    {
      std::vector<int> nums = split(line, ",");
      allStars[noStars].x = nums[0];
      allStars[noStars].y = nums[1];
      allStars[noStars].z = nums[2];
      allStars[noStars++].t = nums[3];
    }
  }
  infile.close();

  return noStars;
}

int calcDist(int a, int b) 
{
  return abs(allStars[a].x - allStars[b].x) + abs(allStars[a].y - allStars[b].y) + abs(allStars[a].z - allStars[b].z) + abs(allStars[a].t - allStars[b].t);
}

void dfs(int crNode) 
{
  viz[crNode] = 1;

  for (int vec : allMuc[crNode]) 
    if (viz[vec] == 0) 
      dfs(vec);
}

int64_t adventDay25problem12018(std::ifstream& input)
{
  int noStars = parseInput(input);

  for (int i = 0; i < noStars; i++) 
  {
    for (int j = i + 1; j < noStars; j++) 
    {
      int crDist = calcDist(i, j);
      if (crDist <= 3) 
      {
        allMuc[i].push_back(j);
        allMuc[j].push_back(i);
      }
    }
  }

  int noConst = 0;
  for (int i = 0; i < noStars; i++) 
  {
    if (viz[i] == 0) 
    {
      dfs(i);
      noConst++;
    }
  }

  return noConst;
}

int64_t adventDay25problem22018(std::ifstream& input)
{
  
  return 0;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay25problem12018(infile)
                                        : adventDay25problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day25/input25.txt";
  int problem = 1;

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