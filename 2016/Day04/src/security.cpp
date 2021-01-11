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


long long adventDay04problem12016(std::vector<std::string>& values)
{
  const int SIZE = 26;
  int sum= 0;
  int sector = 0;

  for (auto& line :values ) 
  {
    auto numLoc = std::find_if(line.begin(), line.end(), ::isdigit);
    auto checkLoc = ++std::find(numLoc, line.end(), '[');
    std::string input{ line.begin(), numLoc - 1 };
    std::string check{ checkLoc, checkLoc + 5 };
    std::string res = "";

    sector = ::atoi(&*numLoc); 
    std::vector<std::pair<char, int>> s(SIZE);

    for (int i= 0; i < SIZE; ++i)
      s[i] = { 'a' + i, 0 };

    for (char c : input)
      (c != '-') && ++s[c - 'a'].second;

    std::stable_sort(s.begin(), s.end(), [](auto p1, auto p2) {
      return p1.second > p2.second;
    });

    for (auto& p : s)
      res += p.first;

    sum += sector * !res.compare(0, check.size(), check);
  }

  return sum;
}

long long adventDay04problem22016(std::vector<std::string>& values)
{
  const int SIZE = 26;
  int sum = 0;
  int sector = 0;

  for (auto& line : values)
  {
    auto numLoc = std::find_if(line.begin(), line.end(), ::isdigit);
    std::string input{ line.begin(), numLoc - 1 };
    sector = ::atoi(&*numLoc);

    for (char &c : input)
      c = (c == '-') ? c : ((c - 'a' + sector) % SIZE) + 'a';

    if (input.find("north") != std::string::npos)
      break; 
  }

  return sector;
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

  return (problNumber == 1)? adventDay04problem12016(values)
                           : adventDay04problem22016(values);

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