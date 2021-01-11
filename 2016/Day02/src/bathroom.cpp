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

template <int R, int C>
struct Pad 
{
  constexpr static const int Rows= R;
  constexpr static const int Cols= C;
  char btns[R][C];

  Pad(std::initializer_list<char>&& list)
  {
    std::copy(list.begin(), list.end(), &btns[0][0]);
  }
};

const Pad<3, 3> P1{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const Pad<5, 5> P2{ ' ', ' ', '1', ' ', ' ', ' ', '2', '3', '4', ' ', '5', '6', '7', '8', '9', ' ', 'A', 'B', 'C', ' ', ' ', ' ', 'D', ' ', ' ' };

long long adventDay02problem12016(std::vector<std::string>& values)
{
  auto clamp = [](auto value, auto min, auto max) 
  {
    return std::max(min, std::min(max, value));
  };

  std::string result= "";
  auto runner = [&](auto& pad, int x, int y) 
  {
    using PadT = std::decay_t<decltype(pad)>;
    //for (std::string line; std::getline(is, line); os << pad.btns[y][x])
    for(auto& line : values)
    {
      for (char d : line)
      {
        int y1 = clamp(y + (d == 'D') - (d == 'U'), 0, PadT::Rows - 1);
        int x1 = clamp(x + (d == 'R') - (d == 'L'), 0, PadT::Cols - 1);
        if (pad.btns[y1][x1] != ' ')
          y = y1, x = x1;
      }   
      result += pad.btns[y][x];
    }    
  };

  runner(P1, 1, 1);

  return std::stoll(result);
}

long long adventDay02problem22016(std::vector<std::string>& values)
{
  auto clamp = [](auto value, auto min, auto max)
  {
    return std::max(min, std::min(max, value));
  };

  std::string result = "";
  auto runner = [&](auto& pad, int x, int y)
  {
    using PadT = std::decay_t<decltype(pad)>;
    //for (std::string line; std::getline(is, line); os << pad.btns[y][x])
    for (auto& line : values)
    {
      for (char d : line)
      {
        int y1 = clamp(y + (d == 'D') - (d == 'U'), 0, PadT::Rows - 1);
        int x1 = clamp(x + (d == 'R') - (d == 'L'), 0, PadT::Cols - 1);
        if (pad.btns[y1][x1] != ' ')
          y = y1, x = x1;
      }
      result += pad.btns[y][x];
    }
  };

  runner(P2, 0, 2);

  std::cout << "Result: " << result << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> values;
  //int result=0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    values.push_back(line);
  }
  infile.close();

  return (problNumber == 1)? adventDay02problem12016(values)
                           : adventDay02problem22016(values);

}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 3)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}