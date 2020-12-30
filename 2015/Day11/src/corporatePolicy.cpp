#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>

bool scanPass(std::string passw)
{
  bool increasingStraight = false;
  int countPairs = 0;

  for (int i = 1; i < passw.size() - 1; ++i)
  {
    if (passw[i - 1] == (passw[i] - 1) && passw[i + 1] == (passw[i] + 1))
    {
      increasingStraight = true;
      break;
    }   
  }

  for (int j = 0; j < passw.size()-1; ++j)
  {
    if (passw[j] == passw[j+1])
    {
      countPairs++;
      ++j;
    }
  }

  return increasingStraight && (countPairs >1);
}

std::string adventDay11problem12015(std::string passw)
{ 
  bool found = false;
  bool increment = false;
  int last = passw.size() - 1;
  char aux = 'a';

  while (!found)
  {
    last = passw.size() - 1;
    increment = false;
    while (!increment)
    {
      for(int i=0; i < passw.size(); ++i)
      {
        aux = passw[i];
        if (aux == 'i' || aux == 'o' || aux == 'l')
        {
          passw[i] = static_cast<char>(passw[i] + 1);
          for (int j = i+1; j < passw.size(); ++j)
          {
            passw[j] = 'a';
          }
          increment = true;
          break;
        }
      }

      if (passw[last] == 'z' && !increment)
      {
        passw[last] = 'a';
        last--;
      }
      else if(!increment)
      {
        passw[last] = static_cast<char>(passw[last] + 1);
        increment = true;
      }
    }
  
    found = scanPass(passw);
  }

  return passw;
}

std::string adventDay11problem22015(std::string passw)
{
  passw = adventDay11problem12015(passw);

  passw = adventDay11problem12015(passw);

  return passw;
}

long long readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string passw="vzbxkghb";

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  //infile >> line;
  //
  //  if (line == "") continue;
  //  process(routes, cities, line);
  //  
  //}
  //infile.close();

  passw= (problNumber == 1) ? adventDay11problem12015(passw)
                            : adventDay11problem22015(passw);

  std::cout << passw << std::endl;
  return 0;
}

int main(int argc, char *argv[])
{
  // argv contain txt path
  if (argc < 2)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long result = 0;
  switch (std::stoi(argv[1]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The problem number isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}