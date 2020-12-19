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

#define parenthesesopen '('
#define parenthesesclose ')'

enum class OPERATION {SUM, MUL};

struct term
{
  long long number;
  OPERATION op;
};

void oper(long long& num1, long long num2, OPERATION op)
{
  if (op == OPERATION::SUM)
    num1 += num2;
  else
    num1 *= num2;
}

long long adventDay18problem1(std::string& line)
{
  std::vector<term> operations;
  term t{ 0, OPERATION::SUM };

  operations.push_back(t);

  for(int i=0; i<line.size(); ++i)
  {
    char c = line[i];

    if (c == ' ') continue;
    int last = operations.size() - 1;

    if(isdigit(c))
    {
      long long num = c - '0';
      oper(operations[last].number, num, operations[last].op);
    }
    else if(c == parenthesesopen)
    {
      term t{ 0, OPERATION::SUM };
      operations.push_back(t);
    }
    else if(c == parenthesesclose)
    {
      oper(operations[last-1].number, operations[last].number, operations[last-1].op);
      operations.erase(operations.begin() + last);
    }
    else
    {
      if (c == '+')
        operations[last].op = OPERATION::SUM;
      else
        operations[last].op = OPERATION::MUL;
    }
  }

  return operations[0].number;
}

void processParentheses(std::vector<term>& parenth)
{
  int size = parenth.size();
  int pos = 1;

  for (int i=1; i< size; ++i) // SUM
  {
    if (parenth[pos - 1].op == OPERATION::SUM)
    {
      oper(parenth[pos-1].number, parenth[pos].number, OPERATION::SUM);
      parenth[pos - 1].op = parenth[pos].op;
      parenth.erase(parenth.begin()+pos);
    }
    else
    {
      pos++;
    }
  }

  size= parenth.size();
  if (size == 1) return;

  pos = 1;
  for (int i = 1; i < size; ++i) // MUL
  {
    oper(parenth[pos-1].number, parenth[pos].number, OPERATION::MUL);
    parenth[pos-1].op = parenth[pos].op;
    parenth.erase(parenth.begin() + pos);
  }
}

long long adventDay18problem2(std::string& line)
{
  std::vector<std::vector<term>> operations;
  term t0{ 0, OPERATION::SUM };
  std::vector<term > aux{t0};

  operations.push_back(aux);

  int last = operations.size() - 1;

  for (int i = 0; i < line.size(); ++i)
  {
    char c = line[i];

    if (c == ' ') continue;

    if (isdigit(c))
    {
      long long num = c - '0';
      term t{ num, OPERATION::SUM };
      operations[last].push_back(t);
    }
    else if (c == parenthesesopen)
    {
      term t{ 0, OPERATION::SUM };
      aux[0]= t;
      operations.push_back(aux);

      last++;
    }
    else if (c == parenthesesclose)
    {
      processParentheses(operations[last]);
      operations[last-1].push_back(operations[last][0]);
      operations.erase(operations.begin()+last);
      last--;
    }
    else
    {
      if (c == '+')
        operations[last][operations[last].size() - 1].op = OPERATION::SUM;
      else
        operations[last][operations[last].size() - 1].op = OPERATION::MUL;
    }
  }

  processParentheses(operations[0]);

  return operations[0][0].number;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result=0;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    if (line == "") continue;

    result+= (problNumber == 1) ? adventDay18problem1(line)
                                : adventDay18problem2(line);
    
  }
  infile.close();

  return result;
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