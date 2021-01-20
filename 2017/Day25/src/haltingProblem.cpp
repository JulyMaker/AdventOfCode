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

struct state {
  struct action {
    int write;
    char dir;
    char next;
  };
  action act[2];
};

template <typename T, typename Str>
T read(std::istream& is, Str && str) 
{
  T data;
  std::string line;
  std::getline(is, line);
  std::sscanf(line.c_str(), std::forward<Str>(str), &data);
  return data;
}

long long adventDay25problem12017(std::ifstream& is)
{
  auto start = read<char>(is, "Begin in state %c.");
  auto steps = read<int>(is, "Perform a diagnostic checksum after %d steps.");

  std::unordered_map<char, state> states;
  for (std::string line; std::getline(is, line), is; ) {
    auto curr = read<char>(is, "In state %c:");
    state s;
    for (int i = 0; i < 2; ++i) {
      auto val = read<int>(is, "  If the current value is %d:");
      s.act[val] = state::action{
        read<int>(is, "    - Write the value %d."),
        read<char>(is, "    - Move one slot to the %c"),
        read<char>(is, "    - Continue with state %c.")
      };
    }
    states.emplace(curr, s);
  }

  std::unordered_map<int, int> tape;
  for (int cursor{ 0 }; steps >= 0; --steps) 
  {
    auto const & curr = states[start].act[tape[cursor]];
    tape[cursor] = curr.write;
    cursor += (curr.dir == 'l') ? -1 : 1;
    start = curr.next;
  }

  int checksum= 0;
  for (auto[k, v] : tape)
    checksum += v;
  
  return checksum;
}

long long adventDay25problem22017(std::ifstream& is)
{
  std::cout << "Happy Advent of Code 2017!" << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  //std::string line;
  //
  //std::vector<std::string> input;
  long long result = 0;
  //
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay25problem12017(infile)
                              : adventDay25problem22017(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day25/input25.txt";
  int problem = 1;

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