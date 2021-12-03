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
#include <unordered_map>
#include <array>
#include <mutex>
#include <numeric>
#include <intrin.h>
#include <tuple>
#include <iomanip>
#include <cctype> 
#include <random>
#include <valarray>
#include <thread>
#include <unordered_set>

int binaryToDecimal(std::string n)
{
  int dec_value = 0;

  // Initializing base value to 1, i.e 2^0
  int base = 1;

  for(int i = n.size() - 1; i >= 0; --i)
  {
    dec_value += int(n[i]-'0') * base;
    base = base * 2;
  }

  return dec_value;
}

long long adventDay03problem12021(std::ifstream& is)
{
  std::vector<std::string> binaryNumbers(std::istream_iterator<std::string>(is), {});

  std::string gammaStr = "";

  for (int i = 0; i < binaryNumbers[0].size(); ++i)
  {
    unsigned int unos = 0;
    unsigned int ceros = 0;

    for (int j = 0; j < binaryNumbers.size(); ++j)
    {
      (binaryNumbers[j][i] == '0') ? ceros++ : unos++;
    }

    gammaStr += (ceros >= unos) ? "0" : "1";
  }

  std::string epsilonStr = "";
  for (auto& num : gammaStr)
    epsilonStr+= (num == '0')? "1" : "0";

  long long gamma = binaryToDecimal(gammaStr);
  long long epsilon = binaryToDecimal(epsilonStr);

  return gamma * epsilon;
}

void removeNumbers(std::vector<std::string>& numbers, unsigned int pos, char filter)
{
  int numbersSize = numbers.size() -1;

  for (int i = numbersSize; i >= 0; i--)
  {
    if (numbers[i][pos] == filter) numbers.erase(std::next(numbers.begin(), i));
  }
}

long long adventDay03problem22021(std::ifstream& is)
{
  std::vector<std::string> oxygenGenerator(std::istream_iterator<std::string>(is), {});
  std::vector<std::string> CO2scrubber = oxygenGenerator;

  int i = 0;
  while ( oxygenGenerator.size() > 1 && i < oxygenGenerator[0].size() )
  {
    unsigned int unos = 0;
    unsigned int ceros = 0;

    for (int j = 0; j < oxygenGenerator.size(); ++j)
    {
      (oxygenGenerator[j][i] == '0') ? ceros++ : unos++;
    }

    removeNumbers(oxygenGenerator, i, (ceros > unos)? '1': '0' );

    ++i;
  }

  int k = 0;
  while (CO2scrubber.size() > 1 && k < CO2scrubber[0].size())
  {
    unsigned int unos = 0;
    unsigned int ceros = 0;

    for (int j = 0; j < CO2scrubber.size(); ++j)
    {
      (CO2scrubber[j][k] == '0') ? ceros++ : unos++;
    }

    removeNumbers(CO2scrubber, k, (ceros <= unos) ? '1' : '0');

    ++k;
  }
  
  long long oxygen = binaryToDecimal(oxygenGenerator[0]);
  long long CO2 = binaryToDecimal(CO2scrubber[0]);

  return oxygen * CO2;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay03problem12021(infile)
                                        : adventDay03problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day03/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return -1;
  }


  long long int result = 0;
  switch (problem)
  {
  case 1:
    result = readFile(fileName, problem);
    break;
  case 2:
    result = readFile(fileName, problem);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}