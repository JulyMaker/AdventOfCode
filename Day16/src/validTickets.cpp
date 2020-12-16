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

void process(std::vector<std::pair<int, int>>& intervals, std::vector<std::string>& tickets, std::string& line)
{
  //departure location : 49 - 258 or 268 - 960
  static bool ticks = false;
  std::smatch sm;
  std::regex regExp(".*: (\\d+)-(\\d+) or (\\d+)-(\\d+)");
  std::regex regExp2("nearby tickets:");

  if (regex_search(line, sm, regExp))
  {
    intervals.push_back(std::make_pair(std::stoi(sm[1].str()), std::stoi(sm[2].str())));
    intervals.push_back(std::make_pair(std::stoi(sm[3].str()), std::stoi(sm[4].str())));
  }

  if (ticks)
  {
    tickets.push_back(line);
  }

  if (regex_search(line, sm, regExp2))
  {
    ticks = true;
  }
}

int adventDay16problem1(std::vector<std::pair<int, int>>& intervals, std::vector<std::string>& tickets)
{
  int sum = 0;

  for (int i = 0; i < tickets.size(); ++i)
  {
    std::string value;
    std::stringstream input_string(tickets[i]);
    bool invalid = true;

    while (getline(input_string, value, ','))
    {
      invalid = true;
      int intValue = std::stoi(value);
      for(int j=0; j< intervals.size(); ++j)
      {
        if (intValue >= intervals[j].first && intValue <= intervals[j].second)
        {
          invalid = false;
          break;
        }
      }
 
      if (invalid) { sum += intValue; break; }
    }
  }

  return sum;
}

void process(std::vector<std::vector<std::pair<int, int>>>& intervals, std::vector<std::vector<int>>& tickets, std::vector<int>& myTicket, std::string& line)
{
  //departure location : 49 - 258 or 268 - 960
  static bool ticks = false;
  static bool myTick = false;
  std::smatch sm;
  std::regex regExp(".*: (\\d+)-(\\d+) or (\\d+)-(\\d+)");
  std::regex regExp2("nearby tickets:");
  std::regex regExp3("your ticket:");

  if (regex_search(line, sm, regExp))
  {
    std::vector<std::pair<int, int>> aux;
    aux.push_back(std::make_pair(std::stoi(sm[1].str()), std::stoi(sm[2].str())));
    aux.push_back(std::make_pair(std::stoi(sm[3].str()), std::stoi(sm[4].str())));

    intervals.push_back(aux);
  }

  if (ticks)
  {
    std::vector<int> aux;

    bool invalid = true;
    std::string value;
    std::stringstream input_string(line);
    while (getline(input_string, value, ','))
    {
      invalid = true;
      int intValue = std::stoi(value);
      for (int j = 0; j < intervals.size(); ++j)
      {
        if ((intValue >= intervals[j][0].first && intValue <= intervals[j][0].second)
          || (intValue >= intervals[j][1].first && intValue <= intervals[j][1].second))
        {
          invalid = false;
          aux.push_back(intValue);
          break;
        }
      }

      if (invalid) break;
    }

    if(!invalid) tickets.push_back(aux);
  }

  if (myTick)
  {
    std::string value;
    std::stringstream input_string(line);
    while (getline(input_string, value, ','))
    {
      myTicket.push_back(std::stoi(value));
    }
    myTick = false;
  }

  if (regex_search(line, sm, regExp2))
  {
    ticks = true;
  }

  if (regex_search(line, sm, regExp3))
  {
    myTick = true;
  }
}

bool isValid(int value, std::vector < std::pair<int, int>>& rule)
{
  if ((value >= rule[0].first && value <= rule[0].second)
    || (value >= rule[1].first && value <= rule[1].second))
    return true;

  return false;
}

long long adventDay16problem2(std::vector<std::vector<std::pair<int, int>>>& intervals, std::vector<std::vector<int>>& tickets, std::vector<int>& myTicket)
{
  long long mul = 1;
  std::vector<std::pair<int, std::vector<int>>> validRules;

  for (int numPos = 0; numPos < tickets[0].size(); ++numPos)
  {
    std::vector<int> rules;
    for (int j = 0; j < intervals.size(); ++j)
    {
      bool valid = true;
      for (int i = 0; i < tickets.size(); ++i)
      {
        int value = tickets[i][numPos];

        if (!isValid(value, intervals[j]))
        {
          valid = false;
          break;
        }
      }

      if (valid) rules.push_back(j);
    }

    validRules.push_back(std::make_pair(numPos, rules));
    rules.clear();
  }
  
  std::sort(validRules.begin(), validRules.end(), [](std::pair<int, std::vector<int>>& a, std::pair<int, std::vector<int>>& b) 
  {return a.second.size() < b.second.size(); });

  std::map<int, bool> used;
  for(auto& rules : validRules)
  {
    for (auto& r : rules.second)
    {
      std::map<int, bool>::iterator it = used.find(r);
      if (it == used.end())
      {
        if(r < 6) mul *= myTicket[rules.first]; // departure cases
        used[r] = true;
      }
    }   
  }

  return mul;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result = 0;
  std::vector<std::pair<int, int>> intervals;
  std::vector<std::string> tickets;
  std::vector<std::vector<std::pair<int, int>>> intervals2;
  std::vector<std::vector<int>> tickets2;
  std::vector<int> myTicket;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    (problNumber == 1) ? process(intervals, tickets, line)
                       : process(intervals2, tickets2, myTicket, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay16problem1(intervals, tickets)
                              : adventDay16problem2(intervals2, tickets2, myTicket);

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