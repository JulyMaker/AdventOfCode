#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <set>

unsigned int adventDay3problem12015(std::string& houses)
{
  std::set<std::pair<int, int>> grid;
  int posX = 0;
  int posY = 0;

  grid.insert(std::make_pair(posX, posY)); // First house

  for(int i =0; i<houses.size(); ++i)
  {
    switch (houses[i])
    {
      case '<':
        posX -= 1;
      break;
      case '>':
        posX += 1;
      break;
      case '^':
        posY += 1;
      break;
      case 'v':
        posY -= 1;
      break;
    }

    grid.insert(std::make_pair(posX, posY));
  }

  return grid.size();
}

int adventDay3problem22015(std::string& houses)
{
  std::set<std::pair<int, int>> grid;
  std::vector<int> pos{0,0,0,0}; // {posSantaX, posSantaY, posRoboX, posRoboY}

  grid.insert(std::make_pair(pos[0], pos[1])); // First house

  for (int i = 0; i < houses.size(); ++i)
  {
    auto posX = (i % 2 == 0) ? &pos[0] : &pos[2];
    auto posY = (i % 2 == 1) ? &pos[1] : &pos[3];

    switch (houses[i])
    {
      case '<':
        *posX -= 1;
        break;
      case '>':
        *posX += 1;
        break;
      case '^':
        *posY += 1;
        break;
      case 'v':
        *posY -= 1;
        break;
    }

    grid.insert(std::make_pair(*posX, *posY));
  }

  return grid.size();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string houses;

  std::getline(infile, houses);

  infile.close();

  return (problNumber == 1) ? adventDay3problem12015(houses)
                            : adventDay3problem22015(houses);
}

int main(int argc, char *argv[])
{
  // argv contain inputTobogan.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputTobogan.txt path or problem number missing" << std::endl;
    return -1;
  }else if((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2) )
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