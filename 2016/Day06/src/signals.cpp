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
#include <thread>

void process(std::vector<std::map<char,int>>& values, std::string& line)
{
  for (int i = 0; i < line.size(); ++i)
  {
    if (i >= values.size())
    {
      std::map<char, int> map;
      values.push_back(map);
    }

    ++values[i][line[i]];
  }
}

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_max(const std::map<KeyType, ValueType>& x) {
  using pairtype = std::pair<KeyType, ValueType>;
  return *std::max_element(x.begin(), x.end(), [](const pairtype & p1, const pairtype & p2) {
    return p1.second < p2.second;
  });
}

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_min(const std::map<KeyType, ValueType>& x) {
  using pairtype = std::pair<KeyType, ValueType>;
  return *std::min_element(x.begin(), x.end(), [](const pairtype & p1, const pairtype & p2) {
    return p1.second < p2.second;
  });
}

long long adventDay06problem12016(std::vector<std::map<char, int>>& values)
{
  std::string signal="";
  for (const auto &c : values)
    signal+= get_max(c).first;

  std::cout << "Result: " << signal <<std::endl;
  return 0;
}

long long adventDay06problem22016(std::vector<std::map<char, int>>& values)
{
  std::string signal = "";
  for (const auto &c : values)
    signal += get_min(c).first;

  std::cout << "Result: " << signal << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::map<char, int>> values;
  //int result=0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(values, line);
  }
  infile.close();

  return (problNumber == 1)? adventDay06problem12016(values)
                           : adventDay06problem22016(values);

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