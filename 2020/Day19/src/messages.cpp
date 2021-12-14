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

void process(std::map<int, std::string>& rules, std::vector<std::string>& messages, std::string& line)
{
  std::smatch sm;
  //std::regex regExpRule1("(\\d+): (\\d+) (\\d+) \\| (\\d+) (\\d+)");
  //std::regex regExpRule2("(\\d+): (\\d+) (\\d+)");
  //std::regex regExpRule3("(\\d+): (\\d+)");
  std::regex regExpA("(\\d+): \"a\"");
  std::regex regExpB("(\\d+): \"b\"");
  std::regex regExp("(\\d+): (.*)");

  if (regex_search(line, sm, regExpA))
  {
    rules[std::stoi(sm[1].str())] = "a";
  }
  else if (regex_search(line, sm, regExpB))
  {
    rules[std::stoi(sm[1].str())] = "b";
  }
  else if (regex_search(line, sm, regExp))
  {
    rules[std::stoi(sm[1].str())] = sm[2].str();
  }else
  {
    messages.push_back(line);
  }
}

std::string processRules(std::map<int, std::string>& rules, int ruleN)
{
  std::string reg =  rules[ruleN];

  if (reg == "a" || reg == "b")
    return reg;

  std::smatch sm;
  std::regex regExpRule1("(\\d+) (\\d+) \\| (\\d+) (\\d+)");
  std::regex regExpRule2("(\\d+) \\| (\\d+)");
  std::regex regExpRule3("(\\d+) (\\d+) (\\d+)");
  std::regex regExpRule4("(\\d+) (\\d+)");
  std::regex regExpRule5("(\\d+)");

  if (regex_search(reg, sm, regExpRule1))
  {
    return "(" + processRules(rules, std::stoi(sm[1].str())) + processRules(rules, std::stoi(sm[2].str())) + "|"
      + processRules(rules, std::stoi(sm[3].str())) + processRules(rules, std::stoi(sm[4].str())) + ")";
  }
  if (regex_search(reg, sm, regExpRule2))
  {
    return "(" + processRules(rules, std::stoi(sm[1].str())) + "|" + processRules(rules, std::stoi(sm[2].str()))+")";
  }
  else if (regex_search(reg, sm, regExpRule3))
  {
    return processRules(rules, std::stoi(sm[1].str())) + processRules(rules, std::stoi(sm[2].str()))
      + processRules(rules, std::stoi(sm[3].str()));
  }
  else if (regex_search(reg, sm, regExpRule4))
  {
    return processRules(rules, std::stoi(sm[1].str())) + processRules(rules, std::stoi(sm[2].str()));
  }
  else if (regex_search(reg, sm, regExpRule5))
  {
    return processRules(rules, std::stoi(sm[1].str()));
  }
}

long long adventDay19problem1(std::map<int, std::string>& rules, std::vector<std::string>& messages)
{
  std::string regEx = processRules(rules, 0);

  std::smatch sm;
  std::regex regExpZero(regEx);

  long long result=0;
  for(int i=0; i< messages.size(); ++i)
  {
    if (regex_match(messages[i], sm, regExpZero))
      result++;
  }

  return result;
}


std::string processRules2(std::map<int, std::string>& rules, int ruleN)
{
  std::string reg = rules[ruleN];

  if (reg == "a" || reg == "b")
    return reg;

  std::smatch sm;
  std::regex regExpRule1("(\\d+) (\\d+) \\| (\\d+) (\\d+)");
  std::regex regExpRule2("(\\d+) \\| (\\d+)");
  std::regex regExpRule3("(\\d+) (\\d+) (\\d+)");
  std::regex regExpRule4("(\\d+) (\\d+)");
  std::regex regExpRule5("(\\d+)");

  std::regex regExpRuleEight("(\\d+) \\| (\\d+) (\\d+)");
  std::regex regExpRuleEleven("(\\d+) (\\d+) \\| (\\d+) (\\d+) (\\d+)");

  if (regex_match(reg, sm, regExpRule1))
  {
    return "(" + processRules2(rules, std::stoi(sm[1].str())) + processRules2(rules, std::stoi(sm[2].str())) + "|"
      + processRules2(rules, std::stoi(sm[3].str())) + processRules2(rules, std::stoi(sm[4].str())) + ")";
  }
  if (regex_match(reg, sm, regExpRule2))
  {
    return "(" + processRules2(rules, std::stoi(sm[1].str())) + "|" + processRules2(rules, std::stoi(sm[2].str())) + ")";
  }
  else if (regex_match(reg, sm, regExpRule3))
  {
    return processRules2(rules, std::stoi(sm[1].str())) + processRules2(rules, std::stoi(sm[2].str()))
      + processRules2(rules, std::stoi(sm[3].str()));
  }
  else if (regex_match(reg, sm, regExpRule4))
  {
    return processRules2(rules, std::stoi(sm[1].str())) + processRules2(rules, std::stoi(sm[2].str()));
  }
  else if (regex_match(reg, sm, regExpRule5))
  {
    return processRules2(rules, std::stoi(sm[1].str()));
  }else if (regex_match(reg, sm, regExpRuleEight))
  {
    return "(" + processRules2(rules, std::stoi(sm[1].str())) + "|" + processRules2(rules, std::stoi(sm[2].str()))
      + "("+processRules2(rules, std::stoi(sm[1].str()))+")+" +")";
  }
  else if(regex_match(reg, sm, regExpRuleEleven))
  {
    std::string a = processRules2(rules, std::stoi(sm[1].str()));
    std::string b = processRules2(rules, std::stoi(sm[2].str()));
    std::string res = "(" + a + b;

    int depth = 5;
    for (int i = 1; i < depth; ++i)
    {
      res += "|("+a;
      for (int j=0; j< i; ++j)res += a;
      for (int j=0; j< i; ++j)res += b;
      res += b+")";
    }
    res += ")";

    return res;
  }
}

long long adventDay19problem2(std::map<int, std::string>& rules, std::vector<std::string>& messages)
{
  std::string regEx = processRules2(rules, 0);

  std::smatch sm;
  std::regex regExpZero(regEx);

  long long result = 0;
  for (int i = 0; i < messages.size(); ++i)
  {
    if (regex_match(messages[i], sm, regExpZero))
    {    
      result++;
    }       
  }

  // 306 - 333 (312, 331)
  return result;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result=0;
  std::map<int, std::string> rules;
  std::vector<std::string> messages;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    if (line == "") continue;

    process(rules, messages, line);  
  }
  infile.close();

  result = (problNumber == 1) ? adventDay19problem1(rules, messages)
                               : adventDay19problem2(rules, messages);

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