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

int adventDay10problem1(std::vector<int>& jolts)
{
  int diffOne = 0;
  int diffThree = 0;

  for(int i=1; i < jolts.size(); ++i)
  {
    (jolts[i]- jolts[i - 1] == 1) ? diffOne++ : (jolts[i] - jolts[i - 1] == 3)? diffThree++ : 0;
  }

  return diffOne * diffThree;
}

int sumatorio(int ini, int n)
{
  int sum = 0;
  for (int i = ini; i < n; i++)
    sum += i;

  return sum;
}

long long adventDay10problem2(std::vector<int>& jolts, int ptr)
{
  long long count = 1;
  int aux = 0;

  if (ptr== jolts.size() -1) return 1;

  for (int i = ptr; i < jolts.size()-1; ++i)
  {
    if (jolts[i + 1] - jolts[i] == 1)
    {
      aux++;
    }
    else
    {
      ptr = i + 1;
      break;
    }   
  }

  int sum = sumatorio(1, aux) + 1;  // sumatorio (1 until aux-1) +1

  return count *= sum * adventDay10problem2(jolts, ptr);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  //std::string line;

  std::vector<int> jolts;
  int readAux;

  while (!infile.eof())
  {
    //std::getline(infile, line);
    infile >> readAux;

    //if (readAux == "") continue;
    jolts.push_back(readAux);

  }
  infile.close();

  std::sort(jolts.begin(), jolts.end());

  jolts.insert(jolts.begin(), 0);
  jolts.push_back( jolts[jolts.size()-1]+3 );


  return (problNumber == 1) ? adventDay10problem1(jolts)
                            : adventDay10problem2(jolts,0);
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