#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>

#define ON 1
#define OFF 0
#define TOGG 2
#define TOGGLE "toggle"

unsigned int adventDay6problem12015(std::string instrucc, std::vector<std::vector<int>>& lights)
{
  std::smatch sm;
  std::regex regExp("(toggle|turn on|turn off) (\\d+),(\\d+) through (\\d+),(\\d+)");

  if (regex_search(instrucc, sm, regExp))
  {
    std::string inst = sm[1].str();
    int luz = (inst == "turn on") ? ON : (inst == "turn off")? OFF : 0;

    for (int i =std::stoi(sm[2].str()) ; i <= std::stoi(sm[4].str()); ++i)
    {
      for (int j = std::stoi(sm[3].str()); j <= std::stoi(sm[5].str()); ++j)
      {   
        luz = (inst == TOGGLE) ? 1- lights[i][j] : luz;

        lights[i][j] = luz;
      }
    }
    
  }

  return 0;
}

int adventDay6problem22015(std::string instrucc, std::vector<std::vector<int>>& lights)
{
  std::smatch sm;
  std::regex regExp("(toggle|turn on|turn off) (\\d+),(\\d+) through (\\d+),(\\d+)");

  if (regex_search(instrucc, sm, regExp))
  {
    std::string inst = sm[1].str();
    int luz = (inst == "turn on") ? ON : (inst == "turn off") ? -1 : TOGG;

    for (int i = std::stoi(sm[2].str()); i <= std::stoi(sm[4].str()); ++i)
    {
      for (int j = std::stoi(sm[3].str()); j <= std::stoi(sm[5].str()); ++j)
      {
        lights[i][j] += luz;
        if (lights[i][j] < 0) lights[i][j] = 0;
      }
    }

  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::vector<int>> lights(1000, std::vector<int>(1000, OFF));

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;
    (problNumber == 1) ? adventDay6problem12015(line, lights)
                       : adventDay6problem22015(line, lights);
  }
  
  infile.close();

  long long int count = 0;

  for(int i=0; i<lights.size(); ++i)
  {
    if (problNumber == 1)
    {
      count += std::count(lights[i].begin(), lights[i].end(), ON);
    }
    else
    {
      for(int j =0; j<lights[i].size(); ++j)
      {
        count += lights[i][j];
      }
    }
    //for (auto j = lights[i].begin(); j != lights[i].end(); ++j)
    //{
    //  char c = (*j == 0) ? ' ' : 'X';
    //  std::cout << c;
    //}
    //std::cout << std::endl;
  }

  return count;

}

int main(int argc, char *argv[])
{
  // argv contain txt path
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