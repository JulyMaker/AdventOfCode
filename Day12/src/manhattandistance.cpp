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

enum class CARDINALS : char{EAST = 'E', SOUTH = 'S', WEST = 'W', NORTH = 'N' };

struct WAYPOINT 
{
  int latitude;
  int longitude;
};

CARDINALS& operator++(CARDINALS& cardinal)
{
  if (cardinal == CARDINALS::EAST) cardinal = CARDINALS::SOUTH;
  else if (cardinal == CARDINALS::SOUTH) cardinal = CARDINALS::WEST;
  else if (cardinal == CARDINALS::WEST) cardinal = CARDINALS::NORTH;
  else if (cardinal == CARDINALS::NORTH) cardinal = CARDINALS::EAST;
  return cardinal;
}

CARDINALS& operator--(CARDINALS& cardinal)
{
  if (cardinal == CARDINALS::EAST) cardinal = CARDINALS::NORTH;
  else if(cardinal == CARDINALS::NORTH) cardinal = CARDINALS::WEST;
  else if(cardinal == CARDINALS::WEST) cardinal = CARDINALS::SOUTH;
  else if (cardinal == CARDINALS::SOUTH) cardinal = CARDINALS::EAST;
  return cardinal;
}

void turn(char turnTo, int degree, CARDINALS& head)
{
  int turns = degree / 90;

  for (int i = 0; i < turns; ++i)
    head = (turnTo=='R')? ++head: --head;
}

void adventDay12problem1(int& latitude, int& longitude, CARDINALS& head, std::string line)
{
  std::smatch sm;
  std::regex regExp("(\\w)(\\d+)");

  if (regex_search(line, sm, regExp))
  {
    std::string action = sm[1].str();
    int num = std::stoi(sm[2].str());

    if (action == "F") action[0] = static_cast<char>(head);
    int mul = (action == "S" || action == "W") ? -1 : 1;

    switch(action[0])
    {
      case 'N':
      case 'S':
        latitude += num * mul;
        break;
      case 'E':
      case 'W':
        longitude += num * mul;
        break;
      case 'L':
      case 'R':
        turn(action[0], num, head);
        break;
    }
  }
}

void turn(char turnTo, int degree, WAYPOINT& way_point)
{
  int turns = degree / 90;
  int aux = 0;

  for (int i = 0; i < turns; ++i)
  {
    int lat = 1;
    int lon = 1;

    (turnTo == 'R') ? lat = -1 : lon = -1;

    aux = way_point.latitude;
    way_point.latitude = way_point.longitude * lat;
    way_point.longitude = aux * lon;
  }   
}

void adventDay12problem2(int& latitude, int& longitude, WAYPOINT& way_point, std::string line)
{
  std::smatch sm;
  std::regex regExp("(\\w)(\\d+)");

  if (regex_search(line, sm, regExp))
  {
    std::string action = sm[1].str();
    int num = std::stoi(sm[2].str());

    //if (action == "F") action[0] = static_cast<char>(head);
    int mul = (action == "S" || action == "W") ? -1 : 1;

    switch (action[0])
    {
    case 'N':
    case 'S':
      way_point.latitude += num * mul;
      break;
    case 'E':
    case 'W':
      way_point.longitude += num * mul;
      break;
    case 'L':
    case 'R':
      turn(action[0],num, way_point);
      break;
    case 'F':
      latitude += num * way_point.latitude;
      longitude += num * way_point.longitude;
      break;
    }
  }
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int latitude = 0;
  int longitude = 0;
  CARDINALS head = CARDINALS::EAST;
  WAYPOINT way_point{1, 10};

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;

    (problNumber == 1) ? adventDay12problem1(latitude, longitude, head, line)
                       : adventDay12problem2(latitude, longitude, way_point, line);
  }
  infile.close();

  return std::abs(latitude) + std::abs(longitude);
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