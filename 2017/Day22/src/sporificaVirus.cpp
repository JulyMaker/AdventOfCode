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

struct point 
{
  int x, y;

  void rotL() { x = -std::exchange(y, x); }
  void rotR() { y = -std::exchange(x, y); }
  void reverse() { x = -x, y = -y; }

  point& operator+=(point const & d) 
  {
    x += d.x, y += d.y;
    return *this;
  }

  bool operator==(point const & p) const 
  {
    return x == p.x && y == p.y;
  }

  struct hash 
  {
    std::size_t operator()(point const & c) const {
      return *reinterpret_cast<std::size_t const *>(&c.x);
    }
  };
};

long long adventDay22problem12017(std::vector<std::string>& input)
{
  std::unordered_map<point, char, point::hash> cluster;

  auto loc = [&]() -> point 
  {
    int midX= -1, y= 0;
    for (std::string line : input)
    {
      for (int x= 0; x < static_cast<int>(line.size()); ++x)
        if (line[x] == '#')
          cluster[{x, y}] = '#';
      midX = line.size() / 2; --y;
    }
    return { midX, y / 2 };
  }();

  point dir{ 0,1 };
  int bursts = 0;
  int iterations = 10000 ;

  while (iterations--) 
  {
    if (auto p = cluster.find(loc); p != cluster.end()) 
    {   
      dir.rotR(); cluster.erase(p);
    }
    else 
    {
      dir.rotL(); ++bursts; cluster[loc] = '#';
    }
    loc += dir;
  }

  return bursts;
}

long long adventDay22problem22017(std::vector<std::string>& input)
{
  std::unordered_map<point, char, point::hash> cluster;

  auto loc = [&]() -> point
  {
    int midX = -1, y = 0;
    for (std::string line : input)
    {
      for (int x{ 0 }; x < static_cast<int>(line.size()); ++x)
        if (line[x] == '#')
          cluster[{x, y}] = '#';
      midX = line.size() / 2; --y;
    }
    return { midX, y / 2 };
  }();

  point dir{ 0,1 };
  int bursts = 0;
  int iterations = 10000000;

  while (iterations--)
  {
    if (auto p = cluster.find(loc); p != cluster.end()) {
        switch (p->second) 
        {
          case 'W': ++bursts;      p->second = '#';  break;
          case '#': dir.rotR();    p->second = 'F';  break;
          case 'F': dir.reverse(); cluster.erase(p); break;
        }
    }
    else
    {
      dir.rotL(); cluster[loc] = 'W';
    }
    
    loc += dir;
  }

  return bursts;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> input;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    input.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay22problem12017(input)
                              : adventDay22problem22017(input);

  return result;
}

int main(int argc, char *argv[])
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