#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <map>

#define RSHIFT >>
#define LSHIFT <<
#define AND &
#define OR |
#define NOT ~

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void process (std::map<std::string, std::string>& circuito, std::string& line)
{
  std::smatch sm;
  std::regex regExp("(.*) -> (\\w+)");

  if (regex_search(line, sm, regExp))
  {
    circuito[sm[2].str()] = sm[1].str();
  }
}

unsigned short adventDay7problem12015(std::map<std::string, std::string>& circuito, std::string incog)
{
  std::smatch sm;
  std::regex regExp1("NOT (\\w+)");
  std::regex regExp2("(\\w+) (AND|OR|LSHIFT|RSHIFT) (\\w+)");
  //std::regex regExp3("(\\d+)");

  if (is_number(incog))
  {
    return (unsigned short) std::stoi(incog);
  }else
  {
    std::cout << circuito[incog] << std::endl;
  }

  if (regex_search(circuito[incog], sm, regExp1))
  {
    unsigned short num = adventDay7problem12015(circuito, sm[1].str());
    circuito[sm[1].str()] = std::to_string(num);
    return NOT num;
    //return NOT adventDay7problem12015(circuito, sm[1].str());
  }
  else if (regex_search(circuito[incog], sm, regExp2))
  {
    unsigned short num1 = adventDay7problem12015(circuito, sm[1].str());
    circuito[sm[1].str()] = std::to_string(num1);
    unsigned short num2 = adventDay7problem12015(circuito, sm[3].str());
    circuito[sm[3].str()] = std::to_string(num2);

    if (sm[2].str() == "AND")
    {
      return num1 AND num2;
    }
    else if(sm[2].str() == "OR")
    {
      return num1 OR num2;
    }
    else if (sm[2].str() == "RSHIFT")
    {
      return num1 RSHIFT num2;
    }
    else if (sm[2].str() == "LSHIFT")
    {
      return num1 LSHIFT num2;
    }  
  }
  else 
  {   
    return adventDay7problem12015(circuito, circuito[incog]);
  }

  return 0;
}

int adventDay7problem22015(std::map<std::string, std::string>& circuito, std::string incog)
{
  std::map<std::string, std::string> circuitoCopia = circuito;
  unsigned short aValue = adventDay7problem12015(circuito, "a");

  circuitoCopia["b"] = std::to_string(aValue);

  return adventDay7problem12015(circuitoCopia, "a");;
}

unsigned short readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::map<std::string, std::string> circuito;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;
    process(circuito,line);
  }
  infile.close();

  return (problNumber == 1) ? adventDay7problem12015(circuito, "a")
                            : adventDay7problem22015(circuito, "b");
  
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