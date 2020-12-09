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

bool adventDay9problem1(std::vector<long long>& numbers)
{
  long long number = numbers[numbers.size() - 1];

  for(int i=0; i< numbers.size()-1; ++i)
  {
    for (int j = 0; j < numbers.size() - 1; ++j)
    {
      if (numbers[i] + numbers[j] == number) return true;
    }
  }

  return false;
}


int adventDay9problem2(std::vector<long long>& numbers, long long number)
{
  bool encontrado = false;
  long long sum = 0;
  long long max = 0;
  long long min = 0;

  for (int i = 0; i < numbers.size(); ++i)
  {
    if (encontrado) break;
    sum = 0;
    max = 0;
    min = number;

    int j = i;
    while ( sum < number)
    {
      sum += numbers[j];

      if (sum == number)
      {
        encontrado = true;
        break;
      }

      if (numbers[j] < min) min = numbers[j];
      if (numbers[j] > max) max = numbers[j];

      j++;
    }
  }
  
  return min + max;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<long long int> numbers;
  bool encontrado =false;
  long long int readAux;

  while (!infile.eof())
  {
    //std::getline(infile, line);
    infile >> readAux;

    //if (readAux == "") continue;
    numbers.push_back(readAux);

    if (numbers.size() < 26) continue;

    encontrado = adventDay9problem1(numbers);

    if (!encontrado) break;
  }
  infile.close();

  return (problNumber==1)? numbers[numbers.size() - 1] : adventDay9problem2(numbers, numbers[numbers.size() - 1]);
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