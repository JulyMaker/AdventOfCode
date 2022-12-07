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
#include <bitset>

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

std::vector<std::vector<char>> parseInputChars(std::ifstream& input)
{
  std::string line;
  std::vector<std::vector<char>> map;
  std::vector<char> aux;

  while (std::getline(input, line))
  {
    for (int i = 0; i < line.size(); i++)
    {
      aux.push_back(line[i]);
    }
    map.push_back(aux);
    aux.clear();
  }

  return map;
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

std::string parseLine(std::ifstream& input)
{
  std::string line;

  std::getline(input, line);
  input.close();

  return line;
}

std::vector<int> parseCharToChar(std::ifstream& input)
{
  std::string number;
  std::vector<int> sequence;

  input >> number;
  for (int i = 0; i < number.size(); i++)
  {
    sequence.push_back(number[i] - '0');
  }

  return sequence;
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
      output.push_back(stoll(line));
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

int64_t vectorToInt(std::vector<int>& vector, int offset1 = 0, int offset2 = 0)
{
  if (offset2 == 0) offset2 = vector.size();

  auto result = std::accumulate(vector.begin() + offset1, vector.begin() + offset2, 0, [](int l, int r) {
    return l * 10 + r;
    });

  return result;
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

void readInput05(std::ifstream& infile, std::vector<std::stack<char>>& crane, std::vector<std::vector<int>>& moves)
{
  std::vector<std::vector<char>> stackAux;
  //std::regex pattern1 = std::regex{ "[\\[(\\w))\\]\\s|\\s\\s\\s\\s]+\\[(\\w)\\]|\\s\\s\\s" };
  std::regex pattern1 = std::regex{ "\\[(\\w)\\]" };
  std::regex pattern2 = std::regex{ "move (\\d+) from (\\d+) to (\\d+)" };
  std::smatch m;
  bool firstTime = true;

  for (std::string line; getline(infile, line); )
  {
    if (line == "") break;

    int j = 0;
    do {
      if (firstTime)
      {
        std::stack<char> nstack = std::stack<char>();
        crane.push_back(nstack);
        std::vector<char> nvector = std::vector<char>();
        stackAux.push_back(nvector);
      }

      std::string subStr = line.substr(j, 3);
      if (regex_match(subStr, m, pattern1))
        stackAux[j / 4].push_back(m[1].str()[0]);
      else
        stackAux[j / 4].push_back(' ');

      j += 4;
    } while (j <= line.size() - 3);  

    firstTime = false;
  }

  // Fill stack
  for(int pos=0; pos < stackAux.size(); pos++)
    for(int v= stackAux[pos].size()-2; v >= 0; v--)
    {
      if(stackAux[pos][v] != ' ')
        crane[pos].push(stackAux[pos][v]);
    }

  // Fill moves
  for (std::string line; getline(infile, line); )
  {
    regex_match(line, m, pattern2);
    std::vector<int> nvector = std::vector<int>();
    moves.push_back(nvector);

    for (int i = 1; i < m.size(); i++)
    {
      moves[moves.size() - 1].push_back(std::stoi(m[i]));
    }
  }
}