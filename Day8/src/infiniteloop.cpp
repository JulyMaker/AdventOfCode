#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>

#define ADD "acc"
#define JUMP "jmp"
#define NOP "nop"

int adventDay8problem1(std::vector<std::pair<std::string, int>>& instructions)
{
  int accumulator = 0;
  bool repeat = false;
  int inst = 0;
  std::map<int, bool> instDo;

  while(!repeat)
  {
    std::string instruction = instructions[inst].first;
    int instAux = inst;

    if(instruction == ADD)
    {
      accumulator += instructions[inst].second;
      inst++;
    }
    else if (instruction == JUMP)
    {
      inst += instructions[inst].second;
    }
    else
    {
      inst++;
    }

    if (instDo[inst] == true) repeat = true;

    instDo[instAux] = true;
  }

  return accumulator;
}


int adventDay8problem2(std::vector<std::pair<std::string, int>>& instructions)
{
  int accumulator = 0;
  bool repeat = false;
  int changeInst=0; 
  int lastInst = 0;

  std::map<int, bool> instDo;

  while (lastInst < instructions.size())
  {
    std::string instruction = instructions[lastInst].first;
    int instAux = lastInst;

    if ((lastInst == changeInst) && (instruction==JUMP || instruction == NOP))
    {
      instruction = (instruction == JUMP) ? NOP : JUMP;
    }

    if (instruction == ADD)
    {
      accumulator += instructions[lastInst].second;
      lastInst++;
    }
    else if (instruction == JUMP)
    {
      lastInst += instructions[lastInst].second;   
    }
    else
    {
      lastInst++;
    }

    if (instDo[lastInst] == true) repeat = true;

    instDo[instAux] = true;

    if (repeat)
    {
      changeInst++;
      lastInst = 0;
      accumulator = 0;
      repeat = false;
      instDo.clear();
    } 
  }

  return accumulator;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::pair<std::string,int>> instructions;
  std::string command;
  int number=0;

  while (!infile.eof())
  {
    //std::getline(infile, line);
    infile >> command >> number;

    if (command == "") continue;

    instructions.push_back(std::make_pair(command, number));

  }
  infile.close();

  return (problNumber == 1) ? adventDay8problem1(instructions)
                            : adventDay8problem2(instructions);
}

int main(int argc, char *argv[])
{
  // argv contain inputDeclarationForm.txt path
  if (argc < 3)
  {
    std::cout << "ERROR: inputDeclarationForm.txt path or problem number missing" << std::endl;
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