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

void process(std::vector<std::string>& values, std::string& line)
{
  std::istringstream split(line);
  
  for (std::string each; std::getline(split, each, ','); values.push_back(each));
}

long long adventDay01problem12016(std::vector<std::string>& values)
{
  int  pos[2]{ 0, 0 };
  int index = 1;
  char turn = ' ';
  int distance = 0;
 
  for(auto& v: values)
  {
    if (v[0] == ' ') v.erase(0, 1);
    turn = v[0];
    distance = std::stoi(v.substr(1,v.size()-1));

    index += ~turn & 3;
    for (int i= 0; i < distance; ++i)
    {
      pos[index & 1] += 1 - (index & 2);
    }
  }

  return std::abs(pos[0]) + std::abs(pos[1]);
}

long long adventDay01problem22016(std::vector<std::string>& values)
{
  std::set<std::pair<int, int>> visited;
  int  pos[2]{ 0, 0 };
  int index = 1;
  char turn = ' ';
  int distance = 0;

  for (auto& v : values)
  {
    if (v[0] == ' ') v.erase(0, 1);
    turn = v[0];
    distance = std::stoi(v.substr(1, v.size() - 1));

    index += ~turn & 3;
    for (int i = 0; i < distance; ++i)
    {
      pos[index & 1] += 1 - (index & 2);
      if (!visited.emplace(pos[0], pos[1]).second)
        return std::abs(pos[0]) + std::abs(pos[1]);
    }
  }

  return std::abs(pos[0]) + std::abs(pos[1]);
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
  
    process(values, line);
  }
  infile.close();

  return (problNumber == 1)? adventDay01problem12016(values)
                           : adventDay01problem22016(values);

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