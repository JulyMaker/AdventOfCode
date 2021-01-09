#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <valarray>
#include <functional>
#include <numeric>
#include <array>

class Combination {
  bool cont{ true };
  std::vector <bool> v;

public:
  Combination(size_t n, size_t r) : v(r, true) {
    v.resize(n, false);
  }

  bool next(std::vector <int> & res) {
    if (!cont) return false;
    for (size_t i= 0, j= 0; i < v.size(); ++i)
      if (v[i])
        res[j++] = i;
    cont = std::prev_permutation(std::begin(v), std::end(v));
    return true;
  }
};

long long check(const std::vector <int> & nums, int target) 
{
  int min= 1;

  while (std::accumulate(std::rbegin(nums), std::rbegin(nums) + min++, 0) <= target);

  std::vector <int> ind(min);
  for (size_t r= min; true; ind.resize(++r)) 
  {
    Combination comb( nums.size(), r );

    while (comb.next(ind)) 
    {
      int sum= 0; 
      uint64_t prod= 1;
      
      for (auto && index : ind)
        sum += nums[index], prod *= nums[index];
      if (sum == target)
        return prod;
    }
  }
  return 0;
}

long long adventDay24problem12015(std::vector<int>& nums)
{
  const int BUCKETS= 3;
  int sum = std::accumulate(std::cbegin(nums), std::cend(nums), 0);
 
  return check(nums, sum / BUCKETS);
}

long long adventDay24problem22015(std::vector<int>& nums)
{
  const int BUCKETS = 4;
  int sum = std::accumulate(std::cbegin(nums), std::cend(nums), 0);

  return check(nums, sum / BUCKETS);
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<int> nums;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;

    if (line == "") continue;

    nums.push_back(std::stoi(line));
  }
  infile.close();

  result = (problNumber == 1) ? adventDay24problem12015(nums)
                              : adventDay24problem22015(nums);

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