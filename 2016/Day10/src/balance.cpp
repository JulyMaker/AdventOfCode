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
#include <valarray>

struct Data 
{
  int  min= INT_MAX, max= INT_MIN, size= 0;
  bool vis= false;

  Data& insert(int v) 
  {
    if (size == 2)
      return *this;
    int& toInsert = (size == 0 || v < min) ? min : max;
    if (size == 1 && v < min)
      std::swap(min, max);
    toInsert = v, ++size;
    return *this;
  }

  Data& visit() 
  {
    vis = true;
    return *this;
  }

  bool ready() const {
    return size == 2 && !vis;
  }
};

void process(std::map<char, std::map<int, Data>>& data, std::vector<std::function<int()>>& bots, std::map<int, int>& ids, std::string& line, bool part2)
{
  int bot, v1, v2;
  char t1, t2;

  if (sscanf(line.c_str(), "value %d goes to bot %d", &v1, &bot))
    data['b'][bot].insert(v1);
  else if (sscanf(line.c_str(), "bot %d gives low to %c%*s %d and high to %c%*s %d", &bot, &t1, &v1, &t2, &v2)) 
  {
    ids.emplace(bot, bots.size());
    bots.push_back([part2, bot, v1, v2, t1, t2, &data, &ids, &bots]() 
    {
      auto& d = data['b'][bot].visit();
      int ret= 0;

      if (d.min == 17 && d.max == 61)
        ret = bot;

      if (data[t1][v1].insert(d.min).ready() && t1 == 'b')
        ret += bots[ids[v1]]();

      if (data[t2][v2].insert(d.max).ready() && t2 == 'b')
        ret += bots[ids[v2]]();

      return ret;
    });
  }
}

long long adventDay10problem12016(std::map<char, std::map<int, Data>>& data, std::vector<std::function<int()>>& bots, std::map<int, int>& ids)
{
  for (auto& b : data['b'])
  {
    if (b.second.ready())
    {
      auto res = bots[ids[b.first]]();

      return res;
    }
  }
    
  return 0;
}

long long adventDay10problem22016(std::map<char, std::map<int, Data>>& data, std::vector<std::function<int()>>& bots, std::map<int, int>& ids)
{
  for (auto& b : data['b'])
  {
    if (b.second.ready())
    {
      auto res = bots[ids[b.first]]();
      auto get = [&data](int i) { return data['o'][i].min; };

      int result = get(0) * get(1) * get(2);
      return result;
    }
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::map<char, std::map<int, Data>> data;
  std::vector<std::function<int()>> bots;
  std::map<int, int> ids;
  long long result = 0;
  bool part2 = false;
  if (problNumber == 2) part2 = true;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    process(data, bots, ids, line, part2);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay10problem12016(data, bots, ids)
                              : adventDay10problem22016(data, bots, ids);

  return result;
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