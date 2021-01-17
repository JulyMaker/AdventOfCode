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

struct Point 
{
  int x= 0, y= 0;

  operator std::uint64_t() const 
  {
    auto as_u32 = [](int a) { return *reinterpret_cast<std::uint32_t*>(&a); };
    return static_cast<std::uint64_t>(as_u32(x)) << 32 | as_u32(y);
  }

  Point& operator+=(Point const& p) 
  {
    x += p.x;
    y += p.y;
    return *this;
  }

  Point operator+(Point const& p) const 
  {
    Point p2 = *this;
    return p2 += p;
  }
};

long long adventDay03problem12017(std::string& input)
{ 
  int num = std::stoi(input);

  if (num == 1) 
  {
    return 0;
  }
  else {
    auto revs = static_cast<int>(std::ceil(std::sqrt(num)) / 2);
    int offset= (num - (revs * 2 - 1) * (revs * 2 - 1)) % (revs * 2);
    return (revs + std::abs(offset - revs));
  }

  return 0;
}

long long adventDay03problem22017(std::string& input)
{
  int num = std::stoi(input);
  static std::array<Point, 8> const neighbors{ {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}} };
  int limit= 1, step= 0;
  bool sawTwo= true ;

  Point loc{ 0, 0 }, dir{ 1, 0 };
  std::unordered_map<std::uint64_t, int> vals;
  vals[loc] = 1;

  while (vals[loc] <= num) 
  {
    loc += dir;
    if (++step == limit) 
    {
      step = 0;
      if ((sawTwo = !sawTwo)) 
      {
        limit++;
      }
      dir = Point{ -dir.y, dir.x };
    }
    int sum= 0;
    for (auto const& n : neighbors) 
    {
      sum += vals[loc + n];
    }
    vals[loc] = sum;
  }

  return vals[loc];
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;
 
  std::string input="368078";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input = line;
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay03problem12017(input)
                              : adventDay03problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day03/input03.txt";
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
  else if(argc != 1)
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