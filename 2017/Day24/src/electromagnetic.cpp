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

struct bridge 
{
  int port1, port2;
  bool avail;
};

std::istream& operator>> (std::istream& is, bridge & b) 
{
  (is >> b.port1).ignore(1, '/') >> b.port2;
  b.avail = true;
  return is;
}

template <typename Fn>
int search(std::vector<bridge> & comp, Fn && f, int end = 0, int len = 0, int str = 0) 
{
  for (auto &[p1, p2, avail] : comp) 
  {
    if (avail && (p1 == end || p2 == end)) 
    {
      avail = false;
      search(comp, std::forward<Fn>(f), end ^ p1 ^ p2, len + 1, str + p1 + p2);
      avail = true;
    }
  }
  return f(len, str);
}

long long adventDay24problem12017(std::ifstream& is)
{
  std::vector<bridge> bridges{ std::istream_iterator<bridge>{is}, {} };

  auto result = search(bridges, [strength = 0](int, int s) mutable 
  {
    return strength = std::max(strength, s);
  });
  
  return result;
}

long long adventDay24problem22017(std::ifstream& is)
{
  std::vector<bridge> bridges{ std::istream_iterator<bridge>{is}, {} };
  
  auto result = search(bridges, [strength = 0, length = 0](int l, int s) mutable 
  {
    if (l > length) 
    {
      strength = s, length = l;
    }
    else if (l == length) 
    {
      strength = std::max(strength, s);
    }
    return strength;
  });

  return result;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  //std::string line;
  //
  //std::vector<std::string> input;
  long long result = 0;
  //
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay24problem12017(infile)
                              : adventDay24problem22017(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day24/input24.txt";
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