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

int lookup_id(const std::string & person) {
  static int shist = 0;
  static std::unordered_map <std::string, int> lookup;

  auto && loc = lookup.find(person);
  if (loc != lookup.end())
    return loc->second;
  return (lookup[person] = 1 << shist++);
}

void process(std::set <int>& people, std::unordered_map <int, int>& distance, std::string& line)
{
  static const std::regex PARSE{ R"((\w+) would (\w+) (\d+) happiness units by sitting next to (\w+).)" };
  std::smatch m;

  if (regex_search(line, m, PARSE))
  {
    int h1{ lookup_id(m[1].str()) }, h2{ lookup_id(m[4].str()) };
    int val = ((m[2].str() == "gain") ? 1 : -1) * std::stoi(m[3].str());
    people.insert(h1), people.insert(h2), distance[h1 ^ h2] += val;
  } 
}

long long adventDay13problem12015(std::set <int>& people, std::unordered_map <int, int>& distance)
{ 
  std::vector <int> tableOrder{ people.cbegin(), people.cend()};
  int result = std::numeric_limits <int>::min();

  do {
    int current = distance[tableOrder[0] | tableOrder.back()];

    for (auto && people = tableOrder.cbegin() + 1; people != tableOrder.cend(); ++people)
      current += distance[*people | *(people - 1)];

    result = std::max(result, current);
  } while (std::next_permutation(tableOrder.begin(), tableOrder.end()));

  return result;
}

long long adventDay13problem22015(std::set <int>& people, std::unordered_map <int, int>& distance)
{
  std::vector <int> tableOrder{ people.cbegin(), people.cend() };
  int result = std::numeric_limits <int>::min();

  do {
    int current = 0;

    for (auto && people = tableOrder.cbegin() + 1; people != tableOrder.cend(); ++people)
      current += distance[*people | *(people - 1)];

    result = std::max(result, current);
  } while (std::next_permutation(tableOrder.begin(), tableOrder.end()));

  return result;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::set <int> people;
  std::unordered_map <int, int> distance;
  
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(people, distance, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay13problem12015(people, distance)
                              : adventDay13problem22015(people, distance);

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