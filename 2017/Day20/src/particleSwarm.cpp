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

struct particle 
{
  std::valarray<long> p{ 0,0,0 }, v{ 0,0,0 }, a{ 0,0,0 };
};

void process(std::vector<particle>& ps, std::string& line)
{
  particle p;
  std::sscanf(line.c_str(), "p=<%ld,%ld,%ld>, v=<%ld,%ld,%ld>, a=<%ld,%ld,%ld>",
    &p.p[0], &p.p[1], &p.p[2], &p.v[0], &p.v[1], &p.v[2], &p.a[0], &p.a[1], &p.a[2]);
  ps.emplace_back(std::move(p));
}

long long adventDay20problem12017(std::vector<particle>& ps)
{
  auto cmp = [](particle const & p1, particle const & p2) 
  {
    return std::abs(p1.a).sum() < std::abs(p2.a).sum();
  };
  
  auto const min = std::min_element(std::begin(ps), std::end(ps), cmp);
  
  return std::distance(std::begin(ps), min);
}

long long adventDay20problem22017(std::vector<particle>& ps)
{
  auto cmp = [](particle const & p1, particle const & p2) 
  {
    return std::abs(p1.a).sum() < std::abs(p2.a).sum();
  };
 
  auto const max = std::max_element(std::begin(ps), std::end(ps), cmp);
  auto const LIMIT = std::abs(max->a).sum();

  std::vector<bool> cs(ps.size(), true);
  for (long t{ 0 }; t < LIMIT; ++t) 
  {
    for (auto & p : ps) 
    {
      p.p += (p.v += p.a);
    }
    for (auto[p1, c1] = std::pair(std::begin(ps), std::begin(cs));
      p1 != std::end(ps); std::advance(p1, 1), std::advance(c1, 1))
      if (*c1)
        for (auto[p2, c2] = std::pair(std::next(p1), std::next(c1));
          p2 != std::end(ps); std::advance(p2, 1), std::advance(c2, 1))
          if (*c2 && std::abs(p1->p - p2->p).sum() == 0)
            *c1 = *c2 = false;
  }
  
  return std::count(std::begin(cs), std::end(cs), true);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<particle> ps;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(ps, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay20problem12017(ps)
                              : adventDay20problem22017(ps);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day20/input20.txt";
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