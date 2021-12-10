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
#include <deque>
#include <stack>


long long adventDay10problem12021(std::ifstream& is)
{
  std::vector<std::string> sintax(std::istream_iterator<std::string>(is), {});
  long long total = 0;

  for (auto& line : sintax)
  {
    std::stack<char> parens;

    for (auto& c : line)
    {
      switch (c)
      {
        case '(':
        case '[':
        case '{':
        case '<':
          parens.push(c);
          break;
        case ')':
          if (parens.empty() || parens.top() != '(')
            total += 3;

          parens.pop();
          break;
        case ']':
          if (parens.empty() || parens.top() != '[') 
            total += 57;

          parens.pop();
          break;
        case '}':
          if (parens.empty() || parens.top() != '{')
            total += 1197;

          parens.pop();
          break;
        case '>':
          if (parens.empty() || parens.top() != '<')
            total += 25137;

          parens.pop();
          break;
        default:
          break;
      }
    }
  }

  return total;
}

long long computeScore(std::stack<char>& parens)
{
  long long total_score = 0;

  while (!parens.empty()) 
  {
    total_score *= 5;
    switch (parens.top()) 
    {
      case '(':
        total_score += 1;
        break;
      case '[':
        total_score += 2;
        break;
      case '{':
        total_score += 3;
        break;
      case '<':
        total_score += 4;
        break;
      default:
        break;
    }
    parens.pop();
  }

  return total_score;
}

long long adventDay10problem22021(std::ifstream& is)
{
  std::vector<std::string> sintax(std::istream_iterator<std::string>(is), {});
  std::vector<long long> scores;
  
  for (auto& line : sintax)
  {
    std::stack<char> parens;
    bool error = false;

    for (auto& c : line)
    {
      if (error) break;

      switch (c)
      {
        case '(':
        case '[':
        case '{':
        case '<':
          parens.push(c);
          break;
        case ')':
          if (parens.empty() || parens.top() != '(')
          {
            error = true;
            break;
          }
        
          parens.pop();
          break;
        case ']':
          if (parens.empty() || parens.top() != '[')
          {
            error = true;
            break;
          }
        
          parens.pop();
          break;
        case '}':
          if (parens.empty() || parens.top() != '{')
          {
            error =true;
            break;
          }
            
          parens.pop();
          break;
        case '>':
          if (parens.empty() || parens.top() != '<')
          {
            error = true;
            break;
          }
        
          parens.pop();
          break;
        default:
          break;
      }
    }

    if(!error) scores.push_back(computeScore(parens));
  }

  std::sort(scores.begin(), scores.end());
  
  return scores[scores.size() / 2];;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay10problem12021(infile)
                                        : adventDay10problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day10/input01.txt";
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