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

static std::regex const NUM{ R"(\d+)", std::regex::optimize };

template <typename T, typename HashFn = std::hash<T>>
struct disjoint_set 
{
  struct set {
    T id;
    int size;
  };

  T find(T t) 
  {
    return find_impl(t).id;
  }

  void join(T t1, T t2) 
  {
    auto & p1 = find_impl(t1);
    auto & p2 = find_impl(t2);
    if (&p1 == &p2)
      return;
    --distinct;
    p1.id = p2.id;
    p2.size += p1.size;
  }

  int size_of(T t) 
  {
    return find_impl(t).size;
  }

  int size() const 
  {
    return total_size;
  }

  int sets() const 
  {
    return distinct;
  }

private:

  set& find_impl(T t) 
  {
    set& s = table[t];
    if (s.size == 0) {
      ++distinct;
      ++total_size;
      return s = { t, 1 };
    }
    if (s.id == t)
      return s;
    set& s1 = find_impl(s.id);
    s.id = s1.id;
    return s1;
  }

  std::unordered_map<T, set, HashFn> table;
  int distinct= 0;
  int total_size= 0;
};

long long adventDay12problem12017(std::vector<std::string>& input)
{
  disjoint_set<int> set;

  for (std::string line : input ) 
  {
    auto nums = std::sregex_iterator(std::begin(line), std::end(line), NUM);
    int prog{ std::stoi(nums->str()) };
    while (++nums != std::sregex_iterator()) {
      set.join(prog, std::stoi(nums->str()));
    }
  }

  return set.size_of(0);
}


long long adventDay12problem22017(std::vector<std::string>& input)
{
  disjoint_set<int> set;

  for (std::string line : input)
  {
    auto nums = std::sregex_iterator(std::begin(line), std::end(line), NUM);
    int prog{ std::stoi(nums->str()) };
    while (++nums != std::sregex_iterator()) {
      set.join(prog, std::stoi(nums->str()));
    }
  }

  return set.sets();
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

  result = (problNumber == 1) ? adventDay12problem12017(input)
                              : adventDay12problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day12/input12.txt";
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