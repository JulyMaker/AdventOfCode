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

const std::regex SWAP{ R"(swap (\S+)\S+ (\S+) with \S+ (\S+))", std::regex::optimize },
                 ROTI{ R"(rotate (\w+) (\d+) steps?)", std::regex::optimize },
                 ROTL{ R"(rotate based on position of letter (\w))", std::regex::optimize },
                 MOVP{ R"(move position (\d+) to position (\d+))", std::regex::optimize },
                 REVP{ R"(reverse positions (\d+) through (\d+))", std::regex::optimize };


long long adventDay21problem12016(std::vector<std::string>& input)
{    
  std::string pass= "abcdefgh";
  std::smatch m;

  auto to_char = [&m](int i) { return m[i].str()[0]; };
  auto to_int = [&m](int i) { return std::stoi(m[i].str()); };

  for (const auto& line : input) 
  {
    if (std::regex_match(line, m, SWAP)) 
    { // reversible
      auto rev = [&](int i) { return (to_char(1) == 'l') ? pass.find(to_char(i)) : to_int(i); };
      std::swap(pass[rev(2)], pass[rev(3)]);
    }
    else if (std::regex_match(line, m, ROTI)) 
    {
      int steps = to_int(2);
      int dir(to_char(1));

      std::rotate(pass.begin(), (dir == 'l') ? pass.begin() + steps : pass.end() - steps, pass.end());
    }
    else if (std::regex_match(line, m, ROTL)) 
    {
      int i(pass.find(to_char(1)));
      int rot = (i + 1 + (i >= 4 ? 1 : 0)) % int(pass.size());

      std::rotate(pass.begin(), pass.end() - rot, pass.end());
    }
    else if (std::regex_match(line, m, MOVP)) 
    {
      int p0 = to_int(1); 
      int p1= to_int(2);

      std::swap(p0, p0);
      char letter= pass[p0];

      pass.erase(p0, 1), pass.insert(p1, 1, letter);
    }
    else if (std::regex_match(line, m, REVP)) 
    { // reversible
      std::reverse(pass.begin() + to_int(1), pass.begin() + to_int(2) + 1);
    }
  }
  
  std::cout << "Result: " << pass << std::endl;

  return 0;
}

template <typename T>
class reverser_impl 
{
  typename T::reverse_iterator b, e;

public:
  reverser_impl(T& data)
    : b{ data.rbegin() }
    , e{ data.rend() }
  {
  }

  typename T::reverse_iterator
    begin()
  {
    return b;
  }
  typename T::reverse_iterator
    begin() const
  {
    return b;
  }
  typename T::reverse_iterator
    end()
  {
    return e;
  }
  typename T::reverse_iterator
    end() const
  {
    return e;
  }
};

template <typename T> 
reverser_impl<T> reverser(T& data)
{
  return { data };
}

long long adventDay21problem22016(std::vector<std::string>& input)
{
  std::string pass = "fbgdceah";
  std::smatch m;

  auto to_char = [&m](int i) { return m[i].str()[0]; };
  auto to_int = [&m](int i) { return std::stoi(m[i].str()); };

  for (const auto& line : reverser(input)) 
  {
    if (std::regex_match(line, m, SWAP)) 
    { // reversible
      auto rev = [&](int i) { return (to_char(1) == 'l') ? pass.find(to_char(i)) : to_int(i); };
      std::swap(pass[rev(2)], pass[rev(3)]);
    }
    else if (std::regex_match(line, m, ROTI)) 
    {
      int steps = to_int(2); 
      int dir= (to_char(1) ^ ('l' ^ 'r'));

      std::rotate(pass.begin(), (dir == 'l') ? pass.begin() + steps : pass.end() - steps, pass.end());
    }
    else if (std::regex_match(line, m, ROTL)) 
    {
      int i= pass.find(to_char(1));
      int rot= (i / 2 + (i % 2 || !i ? 1 : 5)) % int(pass.size());

      std::rotate(pass.begin(), pass.begin() + rot, pass.end());
    }
    else if (std::regex_match(line, m, MOVP)) 
    {
      int p0 = to_int(1);
      int p1 = to_int(2);

      std::swap(p0, p1);
      char letter= pass[p0];

      pass.erase(p0, 1), pass.insert(p1, 1, letter);
    }
    else if (std::regex_match(line, m, REVP)) 
    { // reversible
      std::reverse(pass.begin() + to_int(1), pass.begin() + to_int(2) + 1);
    }
  }

  std::cout << "Result: " << pass << std::endl;

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

  result = (problNumber == 1) ? adventDay21problem12016(input)
                              : adventDay21problem22016(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  const int N = 0;
 if (argc < 3 - N)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2 - N]) < 1) || (std::stoi(argv[2 - N]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2-N]))
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