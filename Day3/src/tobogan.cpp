#include <iostream>
#include <string>
#include <fstream>
#include <regex>

unsigned int adventDay3problem1(std::vector<std::string>& tobogan)
{
  unsigned int count = 0;
  unsigned int col = 3;

  for (int row = 1; row < tobogan.size(); row++)
  {
    count += tobogan[row][col % tobogan[row].size()] == '#';
    col += 3;
  }

  return count;
}

long long int adventDay3problem2(std::vector<std::string>& tobogan)
{
  std::vector<std::pair<int, int>> slopes{ { 1, 1 }, { 1, 3 }, { 1, 5 }, { 1, 7 }, { 2, 1 } };
  long long int multi = 1;

  for (int slops = 0; slops < slopes.size(); ++slops)
  {
    int count = 0;
    int col = slopes[slops].second;

    for (int row = slopes[slops].first; row < tobogan.size(); row+= slopes[slops].first)
    {
      count += tobogan[row][col % tobogan[row].size()] == '#';
      col += slopes[slops].second;
    }

    multi *= count;
  }
  
  return multi;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> tobogan;

  while (!infile.eof()) 
  {
    std::getline(infile, line);
    if(line != "") tobogan.push_back(line);
  }
  infile.close();

  return (problNumber == 1) ? adventDay3problem1(tobogan)
                            : adventDay3problem2(tobogan);
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