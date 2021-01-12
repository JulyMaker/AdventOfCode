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

long long decode(std::string::const_iterator s0, std::string::const_iterator s1)
{
  auto i1 = s0;
  while (i1 != s1 && *i1 != '(')
    ++i1;

  if (i1 == s1)
    return std::distance(s0, s1);

  auto i0 = i1;
  int  l = 0, r = 0;
  while (*++i1 != 'x')
    l *= 10, l += (*i1 - '0');

  while (*++i1 != ')')
    r *= 10, r += (*i1 - '0');

  auto s = ++i1 + l;
  return std::distance(s0, i0) + r * std::distance(i1, s) + decode(s, s1);
}

long long decode2(std::string::const_iterator s0, std::string::const_iterator s1)
{
  auto i1 = s0;
  while (i1 != s1 && *i1 != '(')
    ++i1;

  if (i1 == s1)
  {
    long res = std::distance(s0, s1);
    return res;
  }
    

  auto i0 = i1;
  long long  l = 0, r = 0;
  while (*++i1 != 'x')
    l *= 10, l += (*i1 - '0');

  while (*++i1 != ')')
    r *= 10, r += (*i1 - '0');

  auto s = ++i1 + l;
  return  std::distance(s0, i0) + r * decode2(i1, s) + decode2(s, s1);
}

long long adventDay09problem12016(std::vector<std::string>& values)
{
  long long result = 0;
  for (auto& v : values)
    result += decode(v.begin(), v.end());

  return result;
}

long long adventDay09problem22016(std::vector<std::string>& values)
{
  long long result = 0;
  for (auto& v : values)
    result += decode2(v.begin(), v.end());

  return result;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> values;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    values.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay09problem12016(values)
                              : adventDay09problem22016(values);

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