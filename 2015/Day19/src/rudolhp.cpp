#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <valarray>
#include <functional>
#include <numeric>
#include <array>

void process (std::unordered_multimap <std::string, std::string>& rules, std::string& mol, std::string& line)
{
  const static std::regex PARSE{ R"((\w+) => (\w+))" };
  std::smatch m;

  if (std::regex_match(line, m, PARSE))
    rules.emplace(m[1].str(), m[2].str());
  else
    mol = line;
}

void process2(std::unordered_multimap <std::string, std::string>& rules, std::string& mol, std::string& line)
{
  const static std::regex PARSE{ R"((\w+) => (\w+))" };
  std::smatch m;

  if (std::regex_match(line, m, PARSE))
    rules.emplace(m[2].str(), m[1].str());
  else
    mol = line;
}

long long adventDay19problem12015(std::unordered_multimap <std::string, std::string>& rules, std::string& mol)
{
  std::set <std::string> set;
  int result = 0;

  for (auto && r : rules)
    for (int pos = mol.find(r.first, 0); pos != std::string::npos; pos = mol.find(r.first, pos + 1))
      result += set.insert(std::string{ mol }.replace(pos, r.first.length(), r.second)).second;

  return result;
}

long long adventDay19problem22015(std::unordered_multimap <std::string, std::string>& rules, std::string& mol)
{
  int result = 0;
  int pos = 0;

  while (mol != "e")
    for (auto && r : rules)
      if (pos = mol.find(r.first, 0), pos != std::string::npos)
        mol.replace(pos, r.first.length(), r.second), ++result;

  return result;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::string mol;
  std::unordered_multimap <std::string, std::string> rules;

  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    (problNumber == 1) ? process(rules, mol, line)
                       : process2(rules, mol, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay19problem12015(rules, mol)
                              : adventDay19problem22015(rules, mol);

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