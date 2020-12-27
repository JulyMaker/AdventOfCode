#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int adventDay1problem12015(std::vector<std::string>& parenthesis)
{
  unsigned int count = 0;

  for (int i = 0; i < parenthesis.size(); ++i)
  {
    for (int j = 0; j < parenthesis[i].size(); ++j)
    {
      count = (parenthesis[i][j] == '(') ? count+1 : count - 1;
    }
  }

  return count;
}

int adventDay1problem22015(std::vector<std::string>& parenthesis)
{
  unsigned int count = 0;
  unsigned int pos = 1;

  for (int i = 0; i < parenthesis.size(); ++i)
  {
    for (int j = 0; j < parenthesis[i].size(); ++j)
    {
      count = (parenthesis[i][j] == '(') ? count + 1 : count - 1;

      if (count == -1) return pos;

      pos++;
    }
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> parenthesis;

  while (!infile.eof()) 
  {
    std::getline(infile, line);
    if(line != "") parenthesis.push_back(line);
  }
  infile.close();

  return (problNumber == 1) ? adventDay1problem12015(parenthesis)
                            : adventDay1problem22015(parenthesis);
}

int main(int argc, char *argv[])
{
  // argv contain inputParenthesis.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputParenthesis.txt path or problem number missing" << std::endl;
    return -1;
  }else if((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2) )
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