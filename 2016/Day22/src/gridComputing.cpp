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
#include <intrin.h>

struct Node 
{
  int size;
  int used;
  int avail;
};

const int HEIGHT = 30;
const int WIDTH = 34;

void process(std::vector<std::vector<Node>>& nodes, std::string& line)
{
  Node n;
  int x, y;
  if (sscanf(line.c_str(), "/dev/grid/node-x%d-y%d %dT %dT %dT %*d%%", &x, &y, &n.size, &n.used, &n.avail))
  {
    if(nodes.size() < x+1)
    {
      std::vector<Node> aux{ n };
      nodes.push_back(aux);
    }
    else
      nodes[x].push_back(n);  
  }   
}

long long adventDay22problem12016(std::vector<std::vector<Node>>& nodes)
{     
  int pairs = 0;
  const int width = nodes.size();
  const int height = nodes[0].size();

  for (int n1= 0; n1 < width; ++n1)
  {
    for (int n2 = 0; n2 < height; ++n2)
    {
      for (int n3 = 0; n3 < width; ++n3)
      {
        for (int n4 = 0; n4 < height; ++n4)
        {
          pairs += ((n1 != n3 || n2 != n4) && (nodes[n1][n2].used != 0) && (nodes[n1][n2].used <= nodes[n3][n4].avail));
        }
      }
    }
  }

  return pairs;
}

void print(std::vector<std::vector<Node>>& nodes)
{
  int i = 0;
  for (auto& n1 : nodes)
  {
    for (auto& n2 : n1)
    {
      std::cout << "[" << n2.used << "/"<<n2.size<<"]--";
    }
    std::cout << std::endl;
  }
}

unsigned int moveEmptyToSquare(std::vector<std::vector<Node>>& nodes, unsigned int emptyX, unsigned int emptyY, unsigned int maxSize)
{
  unsigned int dist = 0;
  unsigned int distAux = 0;

  while (emptyX != nodes.size()-1 || emptyY != 0)
  {
    if (emptyY > 0) // Up move
    {
      if (nodes[emptyX + distAux][emptyY - 1].used <= maxSize)
        --emptyY, emptyX += distAux, distAux = 0, ++dist;
      else if (nodes[emptyX - distAux][emptyY - 1].used <= maxSize)
        --emptyY, emptyX -= distAux, distAux = 0, ++dist;
      else
        ++distAux, ++dist;
    }
    else
    {
      dist +=  nodes.size() - 1 - emptyX; // Warning I supouse that nodes in first row have memory used < than maxSize
      emptyX = nodes.size() - 1;
    }
  }

  return dist;
}

long long adventDay22problem22016(std::vector<std::vector<Node>>& nodes)
{
  unsigned int emptyX = 0;
  unsigned int emptyY = 0;
  unsigned int maxSize = 0;

  //print(nodes);
  
  //empty pos 
  for (int n1= 0; n1 < nodes.size(); ++n1)
    for (int n2 = 0; n2 < nodes[0].size(); ++n2)
      if (nodes[n1][n2].used == 0)
        emptyX = n1, emptyY = n2 , maxSize = nodes[n1][n2].size;

  return (moveEmptyToSquare(nodes, emptyX, emptyY, maxSize) + (nodes.size() -2) * 5); // 42 move _ to square, change _ to G generate 5 moves
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
 
  std::vector<std::vector<Node>> nodes;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(nodes, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay22problem12016(nodes)
                              : adventDay22problem22016(nodes);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  const int N = 0;
 if (argc < 3 - N)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2 - N]) < 1) || (std::stoi(argv[2 - N]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2-N]))
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