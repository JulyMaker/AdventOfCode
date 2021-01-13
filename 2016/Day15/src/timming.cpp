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

int inv(int a, int m)
{
  int u1= 1, u2= 0, u3= a, v1= 0, v2= 0, v3= m;

  while (v3 != 0) {
    int q{ u3 / v3 };
    std::tie(v1, v2, v3, u1, u2, u3) = std::make_tuple((u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3);
  }
  return (m + u1) % m;
}

int crt(const std::vector<int>& num, const std::vector<int>& rem)
{
  int prod{ std::accumulate(num.begin(), num.end(), 1, std::multiplies<int>{}) };
  int result= 0;

  for (unsigned int i= 0; i < num.size(); ++i) 
  {
    int p= prod / num[i];
    result += rem[i] * inv(p, num[i]) * p;
  }
  return result % prod;
}

void process(std::vector<int>& nums, std::vector<int>& rems, int& N, std::string line)
{
  int num, rem;
  sscanf(line.c_str(), "Disc #%*d has %d positions; at time=0, it is at position %d.", &num, &rem);
  nums.push_back(num);
  rems.push_back(num - (rem + N + 1) % num);
}

long long adventDay15problem12016(std::vector<int>& nums, std::vector<int>& rems)
{    
  return crt(nums, rems);
}

long long adventDay15problem22016(std::vector<int>& nums, std::vector<int>& rems, int& N)
{
  nums.push_back(11); 
  rems.push_back(10 - N);

  return crt(nums, rems);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int N = 0;
  std::vector<int> nums, rems;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    process(nums, rems, N, line);
    ++N;
  }
  infile.close();

  result = (problNumber == 1) ? adventDay15problem12016(nums, rems)
                              : adventDay15problem22016(nums, rems, N);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 3)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[2]))
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