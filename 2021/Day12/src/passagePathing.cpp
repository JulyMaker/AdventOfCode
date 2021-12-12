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
#include <stack>
#include <queue>

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}

void parseEdges(std::ifstream& infile, std::unordered_map<std::string, std::unordered_set<std::string>>& edges)
{
  std::string line;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      std::vector<std::string> caves = split(line, "-");

      edges[caves.front()].insert(caves.back());
      edges[caves.back()].insert(caves.front());
    }
  }
  infile.close();
}

int countPaths(const std::unordered_map<std::string, std::unordered_set<std::string>>& edges,
               std::unordered_set<std::string>& visited_small, std::string current_cave) 
{
  if (current_cave == "end") return 1;

  int paths = 0;
  for (const std::string& next : edges.at(current_cave)) 
  {
    if (visited_small.find(next) == visited_small.end())
    {
      if (!isupper(next.front())) 
        visited_small.insert(next);

      paths += countPaths(edges, visited_small, next);

      if (!isupper(next.front())) 
        visited_small.erase(next);
    }
  }

  return paths;
}

long long adventDay12problem12021(std::ifstream& infile)
{
  std::unordered_map<std::string, std::unordered_set<std::string>> edges;
  std::unordered_set<std::string> visited_small{ "start" };

  parseEdges(infile, edges);

  return countPaths(edges, visited_small, "start");
}
  
int countPaths( const std::unordered_map<std::string, std::unordered_set<std::string>>& edges,
  std::unordered_set<std::string>& visited_small, std::string current_cave, bool double_small)
{
  if (current_cave == "end") return 1;

  int paths = 0;
  for (const std::string& next : edges.at(current_cave)) 
  {
    if (visited_small.find(next) == visited_small.end())
    {
      if (!isupper(next.front())) 
        visited_small.insert(next);

      paths += countPaths(edges, visited_small, next, double_small);

      if (!isupper(next.front())) 
        visited_small.erase(next);
    }
    else if (!double_small && next != "start") 
    {
      paths += countPaths(edges, visited_small, next, true);
    }
  }

  return paths;
}

long long adventDay12problem22021(std::ifstream& infile)
{
  std::unordered_map<std::string, std::unordered_set<std::string>> edges;
  std::unordered_set<std::string> visited_small{ "start" };

  parseEdges(infile, edges);

  return countPaths(edges, visited_small, "start", false);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay12problem12021(infile)
                                        : adventDay12problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day12/input01.txt";
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