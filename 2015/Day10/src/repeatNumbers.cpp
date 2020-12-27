#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>

#define LOOP 40
#define LOOP2 50

long long adventDay10problem12015(std::string& number, int loopSize)
{ 
  for (int loop = 0; loop < loopSize; ++loop)
  {
    int repeat = 1;
    char num = number[0];
    std::string numAux = "";
    for (int i = 1; i < number.size(); ++i)
    {    
      if(i == number.size()-1)
      {
        if (number[i] != num) { numAux += std::to_string(repeat) + num; num = number[i]; repeat = 0; }
        repeat++;
        numAux += std::to_string(repeat) + num;
      }
      else
      {
        if (number[i] == num)
        {
          repeat++;
        }
        else
        {
          numAux += std::to_string(repeat) + num;
          repeat = 1;
          num = number[i];
        }
      } 
    }
    number = numAux;
    numAux.clear();
  }
  

  return number.size();
}

long long adventDay10problem22015(std::string& number, int loopSize)
{
  
  return adventDay10problem12015(number, loopSize);
}

long long readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string number="3113322113";

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

  return (problNumber == 1) ? adventDay10problem12015(number, LOOP)
                            : adventDay10problem22015(number, LOOP2);
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