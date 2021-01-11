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

bool abba(const std::string& s)
{
  bool out= false, in= false, hyper= false;

  for (int i= 0; i < s.size() - 3; ++i)
    if (hyper ^= (s[i] < 'a'), s[i] != s[i + 1] && s[i + 1] == s[i + 2] && s[i] == s[i + 3])
      in |= hyper, out |= !hyper;
  return out && !in;
}

bool aba(const std::string& s)
{
  static bool look[2][26][26];
  ::memset(look, 0, sizeof(bool) * 2 * 26 * 26);
  bool hyper= false;

  for (int i= 0; i < s.size() - 2; ++i)
    if (hyper ^= (s[i] < 'a'), s[i] == s[i + 2] && s[i] != s[i + 1]) 
    {
      int c1= s[i + hyper] - 'a' ;
      int c2= s[i + !hyper] - 'a' ;
      look[hyper][c1][c2] = true;

      if (look[!hyper][c1][c2])
        return true;
    }
  return false;
}


long long adventDay07problem12016(std::string& line)
{
  
  return abba(line);
}

long long adventDay07problem22016(std::string& line)
{
  return aba(line);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::map<char, int>> values;
  int result=0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    result+= (problNumber == 1) ? adventDay07problem12016(line)
                                : adventDay07problem22016(line);
  }
  infile.close();

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