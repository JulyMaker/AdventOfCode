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
#include <optional>

auto & count(std::string const &s) 
{
  static std::array<int, 26> m;
  m.fill(0);
  for (auto const c : s) 
  {
    ++m[c - 'a'];
  }

  static std::unordered_map<int, int> counts;
  counts.clear();
  for (auto const c : m) 
  {
    ++counts[c];
  }
  return counts;
}

std::optional<std::string> check(std::string const &a, std::string const &b) 
{
  int diff = std::inner_product(std::begin(a), std::end(a), std::begin(b), 0, std::plus<>{}, std::not_equal_to<>{});
  if (diff == 1) 
  {
    std::string s(a);
    auto[diffS, _] = std::mismatch(std::begin(s), std::end(s), std::begin(b));
    s.erase(diffS);
    return s;
  }
  return std::nullopt;
}


long long adventDay02problem12018(std::ifstream& is)
{
  std::vector<std::string> data(std::istream_iterator<std::string>(is), {});
  
  int twos= 0, threes= 0;
  for (std::string const &s : data) 
  {
    auto const &counts = count(s);
    twos += counts.count(2);
    threes += counts.count(3);
  }
  
  return (twos * threes);
}

template <typename Container, typename Fn>
auto combinations(Container const& c, size_t k, Fn&& f) {
  using T = std::add_const_t<typename Container::value_type>;
  using R = decltype(f(std::declval<std::vector<std::reference_wrapper<T>>>()));
  std::vector<std::reference_wrapper<T>> res(std::begin(c), std::begin(c) + k);
  std::vector<bool> v(k, true);
  v.resize(std::size(c));
  do {
    for (size_t i= 0, j= 0; i < v.size(); ++i) 
    {
      if (v[i]) {
        res[j++] = c[i];
      }
    }
    if (auto val = f(res); val) {
      return val;
    }
  } while (std::prev_permutation(std::begin(v), std::end(v)));
  return R{};
}


long long adventDay02problem22018(std::ifstream& is)
{
  std::vector<std::string> data(std::istream_iterator<std::string>(is), {});

  auto result = combinations(data, 2, [](auto const & l) {
    return check(l[0], l[1]);
  });

  std::cout << "Result: " << *result  <<std::endl;
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

  result = (problNumber == 1) ? adventDay02problem12018(infile)
                              : adventDay02problem22018(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day02/input02.txt";
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