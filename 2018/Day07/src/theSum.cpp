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
#include <optional>
#include <queue>

using queue = std::priority_queue< char, std::vector< char >, std::greater< char > >;
using charSet = std::unordered_set< char >;
using charMap = std::unordered_map< char, charSet >;

using req = std::unordered_map<char, std::vector<char>>;
using doneMap = std::unordered_map<char, bool>;

auto parse_steps(const std::vector<std::string>& input)
{
  const std::regex pat{ R"(^Step\s(\w).*(\w)\scan\sbegin\.$)" };
  charMap charGroups = {};

  for (auto& line : input)
  {
    std::smatch match;
    std::regex_search(line, match, pat);

    char parent = match[1].str()[0];
    char child = match[2].str()[0];

    if (charGroups.find(child) == charGroups.end()) charGroups[child] = {};
    if (charGroups.find(parent) == charGroups.end()) charGroups[parent] = {};
    charGroups[child].insert(parent);
  }
  
  return charGroups;
}

auto parse_steps2(const std::vector<std::string>& input, charSet& nodes)
{
  const std::regex pat{ R"(^Step\s(\w).*(\w)\scan\sbegin\.$)" };
  req requirements = {};

  for (auto& line : input)
  {
    std::smatch match;
    std::regex_search(line, match, pat);

    char parent = match[1].str()[0];
    char child = match[2].str()[0];

    requirements[child].push_back(parent);
    nodes.insert(parent);
    nodes.insert(child);
  }

  return requirements;
}

long long adventDay07problem120182(std::vector<std::string>& input)
{ 
  auto charGroups = parse_steps(input);
  std::string order = {};

  charSet charGroup = {};
  queue priority = {};

  // only push children with no parents onto the queue for BFS
  for (const auto& s : charGroups)
    if (s.second.empty() && charGroup.insert(s.first).second)
      priority.push(s.first);

  while (!priority.empty())
  {
    order.push_back(priority.top());
    priority.pop();
    for (const auto& s : charGroups)
    {
      charGroups[s.first].erase(order.back());
      if (charGroups[s.first].empty() && charGroup.insert(s.first).second)
        priority.push(s.first);
    }
  }

  std::cout << "Part 1: " << order << std::endl;

  return 0;
}

long long adventDay07problem12018(std::vector<std::string>& input)
{
  charSet nodes;
  req requirements = parse_steps2(input, nodes);

  std::string order = {};
  doneMap done;

  while (nodes.size() != 0) 
  {
    std::vector<char> next;
    bool allCompleted = false;

    for (char node : nodes) 
    {
      allCompleted = true;
      for (char r : requirements[node]) 
      {
        if (!done[r]) 
        { 
          allCompleted = false; 
          break; 
        }
      }
      if (allCompleted) next.push_back(node);
    }

    std::sort(next.begin(), next.end());

    done[next[0]] = true;
    order.push_back(next[0]);

    nodes.erase(next[0]);
  }

  std::cout << "Part 1: " << order << std::endl;

  return 0;
}

long long adventDay07problem22018(std::vector<std::string>& input)
{ 
  const int NUMWORKERS = 5;
  const int STEPTIME = 60;

  charSet nodes;
  req requirements = parse_steps2(input, nodes);

  long long time = 0;
  doneMap done;

  std::unordered_set<char> currJobs; // Jobs currently being performed
  std::vector<char> workers(NUMWORKERS);
  std::vector<int> counters(NUMWORKERS);

  fill(counters.begin(), counters.end(), -1);

  while (true)
  {
    std::vector<char> next;
    bool allCompleted = false;

    for (char node : nodes) 
    {
      allCompleted = true;
      for (char r : requirements[node]) 
      {
        if (!done[r]) 
        { 
          allCompleted = false; 
          break; 
        }
      }
      if (allCompleted && !currJobs.count(node)) next.push_back(node);
    }

    std::sort(next.begin(), next.end());

    // Assign workers jobs
    for (char n : next) 
    {
      for (int i = 0; i < NUMWORKERS; i++) 
      {
        if (counters[i] == -1) 
        {
          workers[i] = n;
          counters[i] = n - 'A' + STEPTIME + 1;
          currJobs.insert(n);
          break;
        }
      }
    }

    if (currJobs.empty()) break; // No worker is working on anything exit loop

    // Decrease counters
    int minTime = INT_MAX;
    for (int currTime : counters) 
      if (currTime != -1 && currTime < minTime) 
        minTime = currTime;

    for (int i = 0; i < NUMWORKERS; i++) 
    {
      if (counters[i] > -1) 
      {
        counters[i] -= minTime;
        if (counters[i] == 0) 
        { // Work finished
          done[workers[i]] = true;
          counters[i] = -1;
          currJobs.erase(workers[i]);
          nodes.erase(workers[i]);
        }
      }
    }

    time += minTime;
  }

  return time;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::vector<std::string> input;
  long long result = 0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    input.push_back(line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay07problem12018(input)
                              : adventDay07problem22018(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day07/input07.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
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
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
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