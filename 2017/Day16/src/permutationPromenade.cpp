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



long long adventDay16problem12017(std::vector<std::string>& input)
{
  std::string p(16, ' ');
  std::iota(std::begin(p), std::end(p), 'a');
  std::vector<std::function<void()>> cmds;

  std::stringstream stream(input[0]);

  for (std::string line; getline(stream, line, ','); )
  {
    if (int i; std::sscanf(line.c_str(), "s%d", &i))
      cmds.emplace_back([&p, i] {
      std::rotate(std::begin(p), std::prev(std::end(p), i), std::end(p));
    });
    else if (int j; std::sscanf(line.c_str(), "x%d/%d", &i, &j))
      cmds.emplace_back([&p, i, j] {
      std::iter_swap(std::begin(p) + i, std::begin(p) + j);
    });
    else if (char a, b; std::sscanf(line.c_str(), "p%c/%c", &a, &b))
      cmds.emplace_back([&p, a, b] {
      std::iter_swap(std::find(std::begin(p), std::end(p), a), std::find(std::begin(p), std::end(p), b));
    });
  }
    
  auto dance = [&] 
  {
    for (auto & cmd : cmds)
      cmd();
  };

  dance();
  std::cout << p << std::endl;

  return 0;
}

long long adventDay16problem22017(std::vector<std::string>& input)
{
  std::string p(16, ' ');
  std::iota(std::begin(p), std::end(p), 'a');
  std::vector<std::function<void()>> cmds;

  std::stringstream stream(input[0]);

  for (std::string line; getline(stream, line, ','); )
  {
    if (int i; std::sscanf(line.c_str(), "s%d", &i))
      cmds.emplace_back([&p, i] {
      std::rotate(std::begin(p), std::prev(std::end(p), i), std::end(p));
    });
    else if (int j; std::sscanf(line.c_str(), "x%d/%d", &i, &j))
      cmds.emplace_back([&p, i, j] {
      std::iter_swap(std::begin(p) + i, std::begin(p) + j);
    });
    else if (char a, b; std::sscanf(line.c_str(), "p%c/%c", &a, &b))
      cmds.emplace_back([&p, a, b] {
      std::iter_swap(std::find(std::begin(p), std::end(p), a), std::find(std::begin(p), std::end(p), b));
    });
  }

  auto dance = [&]
  {
    for (auto & cmd : cmds)
      cmd();
  };

  std::map<std::string, int> lookup;
  for (int rep{ 0 }; lookup.emplace(p, rep++).second; )
    dance();

  int rem(1000000000 % lookup.size());
  for (auto const &[s, i] : lookup) {
    if (i == rem) {
      std::cout << s << std::endl;
      return 0;
    }
  }

  return 0;
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

  result = (problNumber == 1) ? adventDay16problem12017(input)
                              : adventDay16problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day16/input16.txt";
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