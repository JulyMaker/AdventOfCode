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

enum class color {WHITE, BLACK};

bool foundTile(std::map<std::pair<int, int>, color>& v, int posX, int posY, int& result)
{
    auto it = v.find(std::make_pair(posX, posY));
    if (it != v.end())
    {
      if (it->second == color::BLACK)
      {
        it->second = color::WHITE;
        result--;
      }
      else
      {
        it->second = color::BLACK;
        result++;
      }
      return true;
    }
    
  return false;
}

color changeResult(color c, int black, int&result)
{
  if (c == color::BLACK)
  {
    if (black == 0 || black > 2) { result--; return color::WHITE; }
    else
      return color::BLACK;
  }
  else
  {
    if (black == 2) { result++; return color::BLACK; }
    else
      return color::WHITE;
  }
}

color adjacent(std::map<std::pair<int, int>, color> v,int posX, int posY, int& result)
{
  int black = 0;
  int white = 0;
  color c = v[std::make_pair(posX, posY)];

  auto it = v.find(std::make_pair(posX-1, posY));
  if ( it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  it = v.find(std::make_pair(posX + 1, posY));
  if (it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  it = v.find(std::make_pair(posX, posY-1));
  if (it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  if (black >2) return changeResult(c, black, result);
  it = v.find(std::make_pair(posX, posY+1));
  if (it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  if (black > 2) return changeResult(c, black, result);
  it = v.find(std::make_pair(posX-1, posY + 1));
  if (it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  if (black > 2) return changeResult(c, black, result);
  it = v.find(std::make_pair(posX + 1, posY - 1));
  if (it != v.end())
    (it->second == color::BLACK) ? black++ : white++;

  return changeResult(c, black, result);
}

void addAdjacent(std::map<std::pair<int, int>, color>& v)
{
  std::map<std::pair<int, int>, color> vAux(v);
  int posX = 0;
  int posY = 0;

  for (auto& t : v)
  {
    posX = t.first.first;
    posY = t.first.second;
    if (v[std::make_pair(posX, posY)] == color::WHITE) continue;

    auto it = v.find(std::make_pair(posX - 1, posY));
    if (it == v.end())
      vAux[std::make_pair(posX-1, posY)] = color::WHITE;

    it = v.find(std::make_pair(posX + 1, posY));
    if (it == v.end())
      vAux[std::make_pair(posX + 1, posY)] = color::WHITE;

    it = v.find(std::make_pair(posX, posY - 1));
    if (it == v.end())
      vAux[std::make_pair(posX, posY-1)] = color::WHITE;

    it = v.find(std::make_pair(posX, posY + 1));
    if (it == v.end())
      vAux[std::make_pair(posX, posY+1)] = color::WHITE;

    it = v.find(std::make_pair(posX - 1, posY + 1));
    if (it == v.end())
      vAux[std::make_pair(posX - 1, posY+1)] = color::WHITE;

    it = v.find(std::make_pair(posX + 1, posY - 1));
    if (it == v.end())
      vAux[std::make_pair(posX + 1, posY-1)] = color::WHITE;
  }

  v = vAux;
}

void adventDay24problem1(std::string& line, std::map<std::pair<int, int>, color>& v, int& result)
{
  // e, se, sw, w, nw, and ne
  int posX = 0, posY = 0;
  std::string s = "";
  for (char c : line)
  {
    s.push_back(c);
    if (s == "e")
    {
      posX++;
    }
    else if (s == "w")
    {
      posX--;
    }
    else if (s == "se")
    {
      posY++;
    }
    else if (s == "sw")
    {
      posX--;
      posY++;
    }
    else if (s == "nw")
    {
      posY--;
    }
    else if (s == "ne")
    {
      posX++;
      posY--;
    }
    else
    {
      continue;
    }

    s.clear();
  }

  if (!foundTile(v, posX, posY, result))
  {
    v[std::make_pair(posX, posY)] =  color::BLACK;
    result++;
  }
}

void adventDay24problem2(std::map<std::pair<int, int>, color>& v, int& result)
{
  std::map<std::pair<int, int>, color> vAux;
  for (int i = 0; i < 100; ++i)
  {
    addAdjacent(v);
    for (auto& t : v)
    {
      int posX = t.first.first;
      int posY = t.first.second;
      vAux[std::make_pair(posX, posY)] = adjacent(v, posX, posY, result);
    }

    v = vAux;
    vAux.clear();
  }
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int result=0;
  std::map<std::pair<int, int>, color> v;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    adventDay24problem1(line, v, result);                    
  }
  infile.close();

  if (problNumber == 2) adventDay24problem2(v, result);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 3)
 {
   std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
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