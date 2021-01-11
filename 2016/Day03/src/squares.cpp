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

struct tri {
  int a;
  int b;
  int c;
};

void process(std::vector<tri>& triangles, std::string& line)
{
  std::smatch sm;
  std::regex regExp("\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");

  if (regex_search(line, sm, regExp))
  {
    tri t;
    t.a = std::stoi(sm[1].str());
    t.b = std::stoi(sm[2].str());
    t.c = std::stoi(sm[3].str());

    triangles.push_back(t);
  }
}

bool isTriangle(int a, int b, int c)
{
  return (a + b + c) > 2 * std::max(a, std::max(b, c));
}

long long adventDay03problem12016(std::vector<tri>& triangles)
{
  int sum= 0 ;
  for(auto& t : triangles)
    sum += isTriangle(t.a, t.b, t.c);

  return sum;
}

long long adventDay03problem22016(std::vector<tri>& triangles)
{
  int sum = 0;
  for (int pos = 0; pos < triangles.size() - 2; pos+=3)
  {
    sum += isTriangle(triangles[pos].a, triangles[pos+1].a, triangles[pos+2].a);
    sum += isTriangle(triangles[pos].b, triangles[pos + 1].b, triangles[pos + 2].b);
    sum += isTriangle(triangles[pos].c, triangles[pos + 1].c, triangles[pos + 2].c);
  }
    
  return sum;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<tri> triangles;
  //int result=0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(triangles, line);
  }
  infile.close();

  return (problNumber == 1)? adventDay03problem12016(triangles)
                           : adventDay03problem22016(triangles);

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