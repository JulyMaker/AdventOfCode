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

#define END 2020
#define END2 30000000

long long adventDay15problem1(std::vector<int>& serialNum)
{
  std::map<int, int> numberTurns;

  for (int i = 0; i < serialNum.size()-1; ++i)
  {
    numberTurns[serialNum[i]] = i+1;
  }

  int currentNum = serialNum.at(serialNum.size() - 1); //Last serial number
  for(int i= serialNum.size(); i< END; ++i)
  {
    std::map<int, int>::iterator it = numberTurns.find(currentNum);
    if (it != numberTurns.end())
    {
      int aux = i - it->second;
      numberTurns[currentNum] = i;
      currentNum = aux;
    }
    else
    {
      numberTurns[currentNum] = i;
      currentNum = 0;
    }
  }

  return currentNum;
}

long long adventDay15problem2(std::vector<int>& serialNum)
{
  std::map<int, int> numberTurns;

  for (int i = 0; i < serialNum.size() - 1; ++i)
  {
    numberTurns[serialNum[i]] = i + 1;
  }

  int currentNum = serialNum.at(serialNum.size() - 1); //Last serial number
  for (int i = serialNum.size(); i < END2; ++i)
  {
    std::map<int, int>::iterator it = numberTurns.find(currentNum);
    if (it != numberTurns.end())
    {
      int aux = i - it->second;
      numberTurns[currentNum] = i;
      currentNum = aux;
    }
    else
    {
      numberTurns[currentNum] = i;
      currentNum = 0;
    }
  }

  return currentNum;
}

long long int readFile(int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  long long result = 0;
  std::vector<int> serialNum{ 0,12,6,13,20,1,17 };

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //
  //  result= (problNumber == 1) ? adventDay14problem1(mem, mask, line)
  //                             : adventDay14problem2(mem, mask, line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay15problem1(serialNum)
                              : adventDay15problem2(serialNum);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  //if (argc < 3)
  //{
  //  std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
  //  return -1;
  //}
  //else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  //{
  //  std::cout << "Problem 1 or 2" << std::endl;
  //  return -1;
  //}

  if (argc < 2)
  {
    std::cout << "ERROR: number missing" << std::endl;
    return -1;
  }

  long long int result = 0;
  switch (std::stoi(argv[1]))
  {
  case 1:
    result = readFile(1);
    break;
  case 2:
    result = readFile(2);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}