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

struct csv : std::ctype<char> 
{
  csv() : std::ctype<char>(get_table()) {}
  static mask const* get_table() 
  {
    static mask rc[table_size];
    rc[static_cast<int>(',')] = std::ctype_base::space;
    rc[static_cast<int>('\n')] = std::ctype_base::space;
    return rc;
  }
};


long long adventDay10problem12017(std::string& input)
{
  std::vector<int> lengths;
  std::istringstream is(input);

  is.imbue(std::locale{ is.getloc(), new csv });
  lengths.insert(lengths.end(), std::istream_iterator<int>{is}, {});
  is.imbue(std::locale{ is.getloc(), new std::ctype<char> });

  int iters = 1;
  std::array<unsigned char, 256> list;
  std::iota(std::begin(list), std::end(list), 0);
  unsigned char skip= 0, pos= 0;

  while (iters--)
  {
    for (unsigned char length : lengths) 
    {
      std::reverse(std::begin(list), std::begin(list) + length);
      unsigned char delta = length + skip++;
      std::rotate(std::begin(list), std::begin(list) + delta, std::end(list));
      pos += delta;
    }
  }
    
  std::rotate(std::begin(list), std::end(list) - pos, std::end(list));

  return list[0] * list[1];
}


long long adventDay10problem22017(std::string& input)
{
  std::vector<int> lengths;
  std::istringstream is(input);

  lengths.insert(lengths.end(), std::istream_iterator<char>{is}, {});
  lengths.insert(lengths.end(), { 17, 31, 73, 47, 23 });

  int iters = 64;
  std::array<unsigned char, 256> list;
  std::iota(std::begin(list), std::end(list), 0);
  unsigned char skip= 0, pos= 0;

  while (iters--)
  {
    for (unsigned char length : lengths)
    {
      std::reverse(std::begin(list), std::begin(list) + length);
      unsigned char delta = length + skip++;
      std::rotate(std::begin(list), std::begin(list) + delta, std::end(list));
      pos += delta;
    }
  }
   
  std::rotate(std::begin(list), std::end(list) - pos, std::end(list));

  std::ostream& os = std::cout;
  auto const flags = os.flags(std::ios::hex);
  auto const fill = os.fill('0');
  
  for (auto b = std::begin(list); b != std::end(list); std::advance(b, 16))
    os << std::setw(2) << std::accumulate(b, std::next(b, 16), 0, std::bit_xor<void>());

  os.flags(flags), os.fill(fill);

  os << '\n';

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::string input;
  int pos = 0;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    input = line;
  }
  infile.close();

  result = (problNumber == 1) ? adventDay10problem12017(input)
                              : adventDay10problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day10/input10.txt";
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