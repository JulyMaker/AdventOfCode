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

void process(std::vector<std::pair<int64_t, int64_t>>& data, std::string line)
{
  uint64_t a, b;
  sscanf(line.c_str(), "%llu-%llu", &a, &b);
  data.emplace_back(a, b); 
}

long long adventDay20problem12016(std::vector<std::pair<int64_t, int64_t>>& data)
{    
  std::sort(data.begin(), data.end());
  
  int64_t MAX= 4294967295;
  int64_t total = 0;
  int64_t last = -1;
  int64_t first= -1;

  for (const auto& d : data) 
  {
    int64_t c= std::max(int64_t{0}, d.first - last - 1);
    if (first == -1 && c)
      first = last + 1;

    last = std::max(last, d.second);
  }
  total += std::max(int64_t{ 0 }, MAX - last);

  return first;
}

long long adventDay20problem22016(std::vector<std::pair<int64_t, int64_t>>& data)
{
  std::sort(data.begin(), data.end());

  int64_t MAX = 4294967295;
  int64_t total = 0;
  int64_t last = -1;
  int64_t first = -1;

  for (const auto& d : data)
  {
    int64_t c = std::max(int64_t{ 0 }, d.first - last - 1);
    total += c;

    last = std::max(last, d.second);
  }
  total += std::max(int64_t{ 0 }, MAX - last);

  return total;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
 
  std::vector<std::pair<int64_t, int64_t>> data;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(data, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay20problem12016(data)
                              : adventDay20problem22016(data);

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