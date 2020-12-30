#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>

long long adventDay12problem12015(std::string& line)
{ 
  long long sum = 0;
  std::string s="";

  for (char c : line)
  {
    if (c == '-' || isdigit(c))
    {
      s += c;
    }
    else if(s.size() > 0)
    {
      sum += std::stoi(s);
      s = "";
    }
  }

  return sum;
}

long long adventDay12problem22015(std::string& line)
{
  long long sum = 0;
  int value = 0;
  std::stack <long long> sumStack;

  bool minus = false;
  char c = ' ';

  for (int i= 0; i < line.size(); ++i) {
     c= line[i];

    switch (c) 
    {
      case '{':
        sumStack.push(sum); sum = 0; break;
      case '}':
        sum += sumStack.top(); sumStack.pop(); break;
      case ':':
        if (!line.compare(i + 2, 4, "red\""))
          for (sum = 0, value = 1; value > 0; ++i)
            value += ((line[i + 2] == '}') ? -1 : ((line[i + 2] == '{') ? 1 : 0));
        break;
      case '-':
        minus = true; break;
      default:
        if (c >= '0' && c <= '9') {
          for (value = (c - '0'); line[i + 1] >= '0' && line[i + 1] <= '9'; ++i)
            value = value * 10 + (line[i + 1] - '0');
          sum = (minus ? sum - value : sum + value);
        }
        minus = false;
    }
  }

  return sum;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    result += (problNumber == 1) ? adventDay12problem12015(line)
                                 : adventDay12problem22015(line);
  }
  infile.close();

  return result;
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

  long long result = 0;
  switch (std::stoi(argv[2]))
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