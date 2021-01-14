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
#include "md5.h"

struct State {
  int         x, y;
  std::string path;
};

long long adventDay17problem12016(std::string input)
{    
  const std::array<int, 4> DX{ {-1, 1, 0, 0} }, DY{ {0, 0, -1, 1} };
  const std::string PATH{ "UDLR" };
  std::string       prefix = input;
  std::string       hash;
  std::list<State>  queue, found;
  int               max= 0;

  for (queue.push_back(State{ 0, 0, prefix }); queue.size() != 0 && found.size() == 0; queue.pop_front()) 
  {
    const auto& curr = queue.front();
    hash = md5(curr.path);

    for (unsigned int i= 0; i < 4; ++i) 
    {
      if ((hash[i] > 'a') && (!DX[i] || !((curr.x + DX[i]) >> 2)) && (!DY[i] || !((curr.y + DY[i]) >> 2))) {
        State next{ curr.x + DX[i], curr.y + DY[i], curr.path + PATH[i] };
        ((next.x == 3 && next.y == 3) ? max = std::max(max, int(next.path.size())), found : queue).push_back(next);
      }
    }
  }

  std::cout <<"Result: " << found.front().path.substr(prefix.size()) << std::endl;

  return 0;
}

long long adventDay17problem22016(std::string input)
{
  const std::array<int, 4> DX{ {-1, 1, 0, 0} }, DY{ {0, 0, -1, 1} };
  const std::string PATH{ "UDLR" };
  std::string       prefix= input;
  std::string                hash;
  std::list<State>   queue, found;
  int                      max= 0;

  for (queue.push_back(State{ 0, 0, prefix }); queue.size() != 0; queue.pop_front()) 
  {
    const auto& curr = queue.front();
    hash = md5(curr.path);

    for (unsigned int i= 0; i < 4; ++i) 
    {
      if ((hash[i] > 'a') && (!DX[i] || !((curr.x + DX[i]) >> 2)) && (!DY[i] || !((curr.y + DY[i]) >> 2))) {
        State next{ curr.x + DX[i], curr.y + DY[i], curr.path + PATH[i] };
        ((next.x == 3 && next.y == 3) ? max = std::max(max, int(next.path.size())), found : queue).push_back(next);
      }
    }
  }

  return max - prefix.size();
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string input="vkjiggvb";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay17problem12016(input)
                              : adventDay17problem22016(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 2)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[1]))
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