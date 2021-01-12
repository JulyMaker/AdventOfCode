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

static const std::unordered_map<unsigned int, char> OCR{
{{0x19297A52, 'a'}, {0x392E4A5C, 'b'}, {0x1928424C, 'c'}, {0x39294A5C, 'd'}, {0x3D0E421E, 'e'}, {0x3D0E4210, 'f'}, {0x19285A4E, 'g'},
 {0x252F4A52, 'h'}, {0x1C42108E, 'i'}, {0x0C210A4C, 'j'}, {0x254C5292, 'k'}, {0x2108421E, 'l'}, {0x23BAC631, 'm'}, {0x252D5A52, 'n'},
 {0x19294A4C, 'o'}, {0x39297210, 'p'}, {0x19295A4D, 'q'}, {0x39297292, 'r'}, {0x1D08305C, 's'}, {0x1C421084, 't'}, {0x25294A4C, 'u'},
 {0x2318A944, 'v'}, {0x231AD6AA, 'w'}, {0x22A22951, 'x'}, {0x23151084, 'y'}, {0x3C22221E, 'z'}, {0x00000000, ' '}} };

const unsigned int X = 50, Y = 6, W = 5;

void process(std::valarray<int>& s, std::string& line)
{
  const unsigned int X = 50, Y = 6;
  auto slice = [X, Y](char type, unsigned int idx) { return (type == 'y') ? std::slice{ X * idx, X, 1 } : std::slice{ idx, Y, X }; };

  char c;
  unsigned int a, b;

  sscanf(line.c_str(), "rotate %*s %c=%d by %d", &c, &a, &b) || sscanf(line.c_str(), "%c%*s %dx%d", &c, &a, &b);
  if (c == 'r')
    s[std::gslice{ 0, {b, a}, {X, 1} }] = 1;
  else
    s[slice(c, a)] = std::valarray<int>{ s[slice(c, a)] }.cshift(-b);
  
}

long long adventDay08problem12016(std::valarray<int>& s)
{ 
  return s.sum();
}

long long adventDay08problem22016(std::valarray<int>& s)
{
  std::string result = "";
  for (unsigned int i= 0; i < X / W; ++i)
  {
    unsigned int j= W * Y - 1;
    unsigned int val= 0;

    for (const auto v : std::valarray<int>{ s[std::gslice{i * W, {Y, W}, {X, 1}}] })
      val |= (v << j--);
    result+= OCR.at(val);
  }

  std::cout<<"Result: " << result << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::valarray<int> s(X * Y);
  int result=0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(s, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay08problem12016(s)
                              : adventDay08problem22016(s);

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