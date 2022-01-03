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
#include <deque>
#include <stack>
#include <queue>
#include <optional>

std::vector<std::string> parseInput(std::ifstream& input, const char c)
{
  std::vector<std::string> output;
  std::string line;

  while (!input.eof())
  {
    std::getline(input, line, c);
    if (line != "")
    {
      output.push_back(line);
    }
  }
  input.close();

  return output;
}

std::vector<int> parseInputInt(std::ifstream& input, const char c)
{
  std::vector<int> output;
  std::string line;

  while (!input.eof())
  {
    std::getline(input, line, c);
    if (line != "")
    {
      output.push_back(stoi(line));
    }
  }
  input.close();

  return output;
}

std::vector<int64_t> parseInputInt64(std::ifstream& input, const char c)
{
  std::vector<int64_t> output;
  std::string line;

  while (!input.eof())
  {
    std::getline(input, line, c);
    if (line != "")
    {
      output.push_back(stoi(line));
    }
  }
  input.close();

  return output;
}

template<class T>
std::vector<T> parseInput(std::ifstream& is)
{
  std::vector<T> data(std::istream_iterator<T>(is), {});

  return data;
}

std::vector<std::string> parseInputReg(std::ifstream& infile, std::string rex)
{
  //std::regex pattern = std::regex{ "^pos=<([-]?\\d+),([-]?\\d+),([-]?\\d+)>, r=(\\d+)$" };
  std::regex pattern = std::regex{ rex };
  std::vector<std::string> output;

  for (std::string line; getline(infile, line); )
  {
    std::smatch m;
    regex_match(line, m, pattern);
    for (auto& i : m)
      output.push_back(i);
  }

  return output;
}

std::vector<int> splitI(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(std::stoi(text.substr(start, end - start)));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(std::stoi(text.substr(start)));

  return tokens;
}

std::vector<std::string> splitS(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));

  return tokens;
}

bool mainControl(int argc, char* argv[], int& problem, std::string& fileName)
{
  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return false;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return false;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return false;
  }

  return true;
}