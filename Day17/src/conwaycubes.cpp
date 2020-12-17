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

#define CICLES 6

struct pos
{
  int x;
  int y;
  int z;
};

struct posw
{
  int x;
  int y;
  int z;
  int w;
};

void extraLines(std::vector<std::vector<std::string>>& conwayCube)
{
  for (int z = 0; z < conwayCube.size(); ++z)
  {
    for (int y = 0; y < conwayCube[z].size(); ++y)
    {
      conwayCube[z][y] = "."+ conwayCube[z][y] + ".";
    }
    std::string extraLine(conwayCube[z][0].size(), '.');

    conwayCube[z].insert(conwayCube[z].begin(), extraLine);
    conwayCube[z].push_back(extraLine);
  }

  std::string extraLine2(conwayCube[0][0].size(), '.');
  std::vector<std::string > extraZ (conwayCube[0].size(), extraLine2);

  conwayCube.insert(conwayCube.begin(), extraZ);
  conwayCube.push_back(extraZ);
}

void extraLines(std::vector <std::vector<std::vector<std::string>>>& conwayCube)
{
  for (int w = 0; w < conwayCube.size(); ++w)
  {
    for (int z = 0; z < conwayCube[w].size(); ++z)
    {
      for (int y = 0; y < conwayCube[w][z].size(); ++y)
      {
        conwayCube[w][z][y] = "." + conwayCube[w][z][y] + ".";
      }
      std::string extraLine(conwayCube[w][z][0].size(), '.');

      conwayCube[w][z].insert(conwayCube[w][z].begin(), extraLine);
      conwayCube[w][z].push_back(extraLine);
    }

    std::string extraLine2(conwayCube[0][0][0].size(), '.');
    std::vector<std::string > extraZ(conwayCube[0][0].size(), extraLine2);

    conwayCube[w].insert(conwayCube[w].begin(), extraZ);
    conwayCube[w].push_back(extraZ);
  }

  std::string extraLine3(conwayCube[0][0][0].size(), '.');
  std::vector<std::string > extraZ2(conwayCube[0][0].size(), extraLine3);
  std::vector <std::vector<std::string>> extraW(conwayCube[0].size(), extraZ2);;


  conwayCube.insert(conwayCube.begin(), extraW);
  conwayCube.push_back(extraW);
}


long long numActives(std::vector<std::vector<std::string>>& conwayCube)
{
  long long actives = 0;

  for (int z = 0; z < conwayCube.size(); ++z)
  {
    for (int y = 0; y < conwayCube[z].size(); ++y)
    {
      for (int x = 0; x < conwayCube[z][y].size(); ++x)
      {
        if (conwayCube[z][y][x] == '#') actives++;
      }
    }
  }

  return actives;
}

long long numActives(std::vector <std::vector<std::vector<std::string>>>& conwayCube)
{
  long long actives = 0;
  for (int w = 0; w < conwayCube.size(); ++w)
  {
    for (int z = 0; z < conwayCube[w].size(); ++z)
    {
      for (int y = 0; y < conwayCube[w][z].size(); ++y)
      {
        for (int x = 0; x < conwayCube[w][z][y].size(); ++x)
        {
          if (conwayCube[w][z][y][x] == '#') actives++;
        }
      }
    }
  }

  return actives;
}

int neighborsActives(std::vector<std::vector<std::string>>& conwayCube, pos coordinate)
{
  int neighbors = 0;

  for(int z= coordinate.z -1; z <= coordinate.z + 1; ++z)
  {
    for (int y = coordinate.y - 1; y <= coordinate.y + 1; ++y)
    {
      for (int x = coordinate.x - 1; x <= coordinate.x + 1; ++x)
      {
        if (z >= 0 && z < conwayCube.size() && y >= 0 && y < conwayCube[z].size() && x >= 0 && x < conwayCube[z][y].size() &&
          (x != coordinate.x || y != coordinate.y || z != coordinate.z))

          neighbors += conwayCube[z][y][x] == '#';

        if (neighbors > 3) return neighbors;
      }
    }
  }

  return neighbors;
}

int neighborsActives(std::vector < std::vector<std::vector<std::string>>>& conwayCube, posw coordinate)
{
  int neighbors = 0;

  for (int w = coordinate.w - 1; w <= coordinate.w + 1; ++w)
  {
    for (int z = coordinate.z - 1; z <= coordinate.z + 1; ++z)
    {
      for (int y = coordinate.y - 1; y <= coordinate.y + 1; ++y)
      {
        for (int x = coordinate.x - 1; x <= coordinate.x + 1; ++x)
        {
          if (w >= 0 && w < conwayCube.size() && z >= 0 && z < conwayCube[w].size() && y >= 0 
            && y < conwayCube[w][z].size() && x >= 0 && x < conwayCube[w][z][y].size()&&
            (x != coordinate.x || y != coordinate.y || z != coordinate.z || w != coordinate.w))

            neighbors += conwayCube[w][z][y][x] == '#';

          if (neighbors > 3) return neighbors;
        }
      }
    }
  }

  return neighbors;
}

int adventDay17problem1(std::vector<std::vector<std::string>>& conwayCube, std::vector<std::vector<std::string>>& conwayCubeAux, int& cicles)
{
  if (cicles == CICLES)
    return numActives(conwayCube);

  extraLines(conwayCube);

  conwayCubeAux.clear();
  conwayCubeAux = conwayCube;

  for(int z=0; z< conwayCube.size(); ++z)
  {
    for(int y=0; y < conwayCube[z].size(); ++y)
    {
      for (int x = 0; x < conwayCube[z][y].size(); ++x)
      {
        pos coordinate{x, y, z};
        int neighbors = neighborsActives(conwayCube, coordinate);

        if (conwayCube[z][y][x] == '.' && neighbors == 3)
          conwayCubeAux[z][y][x] = '#';
        else if(conwayCube[z][y][x] == '#' && (neighbors != 2 && neighbors != 3))
          conwayCubeAux[z][y][x] = '.';

      }
    }
  }

  adventDay17problem1(conwayCubeAux, conwayCube, ++cicles);
}

long long adventDay17problem2(std::vector < std::vector<std::vector<std::string>>>& conwayCube, std::vector < std::vector<std::vector<std::string>>>& conwayCubeAux, int& cicles)
{

  if (cicles == CICLES)
    return numActives(conwayCube);

  extraLines(conwayCube);

  conwayCubeAux.clear();
  conwayCubeAux = conwayCube;

  for (int w = 0; w < conwayCube.size(); ++w)
  {
    for (int z = 0; z < conwayCube[w].size(); ++z)
    {
      for (int y = 0; y < conwayCube[w][z].size(); ++y)
      {
        for (int x = 0; x < conwayCube[w][z][y].size(); ++x)
        {
          posw coordinate{ x, y, z, w };
          int neighbors = neighborsActives(conwayCube, coordinate);

          if (conwayCube[w][z][y][x] == '.' && neighbors == 3)
            conwayCubeAux[w][z][y][x] = '#';
          else if (conwayCube[w][z][y][x] == '#' && (neighbors != 2 && neighbors != 3))
            conwayCubeAux[w][z][y][x] = '.';

        }
      }
    }
  }

  adventDay17problem2(conwayCubeAux, conwayCube, ++cicles);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::vector<std::string>> conwayCube;
  std::vector<std::vector<std::string>> conwayCubeAux;
  std::vector < std::vector<std::vector<std::string>>> conwayCube2;
  std::vector < std::vector<std::vector<std::string>>> conwayCubeAux2;
  std::vector<std::string> aux;

  int result = 0;
  int cicle = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    if (line == "") { conwayCube.push_back(aux); conwayCube2.push_back(conwayCube); }
    
    aux.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay17problem1(conwayCube, conwayCubeAux, cicle)
                              : adventDay17problem2(conwayCube2, conwayCubeAux2, cicle);

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