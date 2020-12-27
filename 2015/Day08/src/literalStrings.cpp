#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <map>


void adventDay8problem12015(std::string& line, int& literal, int& inMemory)
{
  char doubleQuote = '"';
  char backslash = '\\';

  inMemory += line.length()-2;
  literal += 2;

  for(int i =1; i<line.size()-1; ++i)
  {
    literal++;
    if (line[i] == backslash)
    {
      if (line[i+1] == backslash || line[i+1] == doubleQuote)
      {
        literal++;
        inMemory--;
        ++i;
      }else if(line[i + 1] == 'x')
      {
        literal += 3;
        inMemory -= 3;
        i += 3;
      }
    }
  }
}

void adventDay8problem22015(std::string& line, int& literal)
{
  char doubleQuote = '"';
  char backslash = '\\';
  char doubleQuoteSl = '\"';

  literal += 6;

  for (int i = 1; i < line.size()-1; ++i)
  {
    literal++;
    if (line[i] == backslash || line[i] == doubleQuoteSl)
    {
      literal++;
    }
  }
}

unsigned short readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int literal = 0;
  int inMemory = 0;
  int literalAux = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;

    if (line == "") continue;
    adventDay8problem12015(line, literal, inMemory);

    if(problNumber==2) adventDay8problem22015(line, literalAux);
  }
  infile.close();

  if (problNumber == 2) { inMemory = literal; literal = literalAux; }

  return literal - inMemory;
  
}

unsigned short main(int argc, char *argv[])
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

  int result = 0;
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