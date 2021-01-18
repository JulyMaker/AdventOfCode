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
#include <queue>

enum State { Default, Garbage, Ignore };

long long adventDay09problem12017(std::vector<std::string>& input)
{
  State s= Default;
  int nest= 0, score= 0;

  for (auto& line : input)
  {
    for (char c : line)
    {
      switch (s)
      {
        case Default: switch (c)
                      {
                        case '<': s = Garbage;     continue;
                        case '{': ++nest;          continue;
                        case '}': score += nest--; continue;
                      }
        case Garbage: switch (c)
                      {
                        case '!': s = Ignore;  continue;
                        case '>': s = Default; continue;
                        default:               continue;
                      }
        case Ignore:
          s = Garbage;
      }
    }
  }

  return score;
}

void next(std::string& input, int& pos)
{
  pos++;
  while (pos <= input.size() && input[pos] == '!')
    pos += 2;
}

int readGarbage(std::string& input, int& pos)
{
  int score = 0;

  next(input, pos);
  while(input[pos] != '>')
  {
    score++;
    next(input, pos);
  }
  next(input, pos);

  return score;
}


long long adventDay09problem22017(std::string& input, int& pos)
{
  State s = Default;
  int gc = 0;
  bool inGarbage = false;

  next(input, pos); // skip '{'
  int score = 0;

  while( input[pos] != '}')
  {
    if (input[pos] == '<')
    {
      score += readGarbage(input, pos);
    }
    else if (input[pos] == '{')
    {
      score += adventDay09problem22017(input, pos);
    }
      
    if (input[pos] == ',')
    {
      next(input, pos);
    }
  }
     
  next(input, pos);

  return score;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> input;
  int pos = 0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    input.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay09problem12017(input)
                              : adventDay09problem22017(input[0], pos);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day09/input09.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
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
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
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