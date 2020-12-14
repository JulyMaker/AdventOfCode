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


int adventDay13problem1(int timestamp, std::string& line)
{
  std::string id;
  std::stringstream input_string(line);

  int earliestTime = timestamp;
  int earliestId = 0;

  while (getline(input_string, id, ','))
  {
    if (id == "x" || id == "") continue;

    int numId = std::stoi(id);
    int time = numId;

    while (time < timestamp)
    {
      time += numId;
    }

    if (time - timestamp < earliestTime)
    {
      earliestTime = time - timestamp;
      earliestId = numId;
    }
  }

  return earliestTime * earliestId;
}

long long adventDay13problem2(std::string& line)
{
  std::string id;
  std::stringstream input_string(line);

  std::vector<std::pair<int, int>> bus;
  int offset = 0;
  
  // Fill bus array
  while (getline(input_string, id, ','))
  {
    if (id == "") continue;
    if (id == "x") { offset++; continue; }

    bus.push_back(std::make_pair(std::stoi(id), offset));
    offset++;
  }

  //We are taking departure time of first bus
  long long step = bus.at(0).first;
  long long time = 0;
  for (std::vector<std::pair<int, int>>::iterator id = bus.begin() + 1; id != bus.end(); id++)
  {
    while ((time + (*id).second) % (*id).first != (long long)0) 
    {
      time += step;
    }
    step *= (*id).first;
  }

  return time;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result = 0;
  int timestamp = 0;
  infile >> timestamp;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;

    result= (problNumber == 1) ? adventDay13problem1(timestamp,  line)
                               : adventDay13problem2( line);
  }
  infile.close();

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