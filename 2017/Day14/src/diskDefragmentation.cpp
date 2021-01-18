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

using Pair = std::pair<int, int>;

struct PairHash 
{
  std::size_t
    operator()(Pair const& p) const {
    return *reinterpret_cast<std::size_t const*>(&p.first);
  }
};

template <typename T, typename HashFn = std::hash<T>>
struct disjoint_set {
  struct set {
    T id;
    int size;
  };

  T find(T t) {
    return find_impl(t).id;
  }

  void join(T t1, T t2) {
    auto & p1 = find_impl(t1);
    auto & p2 = find_impl(t2);
    if (&p1 == &p2)
      return;
    --distinct;
    p1.id = p2.id;
    p2.size += p1.size;
  }

  int size_of(T t) {
    return find_impl(t).size;
  }

  int size() const {
    return total_size;
  }

  int sets() const {
    return distinct;
  }

private:

  set& find_impl(T t) {
    set& s = table[t];
    if (s.size == 0) {
      ++distinct;
      ++total_size;
      return s = { t, 1 };
    }
    if (s.id == t)
      return s;
    set& s1 = find_impl(s.id);
    s.id = s1.id;
    return s1;
  }

  std::unordered_map<T, set, HashFn> table;
  int distinct{ 0 };
  int total_size{ 0 };
};

std::string knot_hash(std::string const & str) 
{
  std::array<unsigned char, 256> list;
  std::iota(std::begin(list), std::end(list), 0);
  std::vector<unsigned char> lengths{ std::begin(str), std::end(str) };
  lengths.insert(lengths.end(), { 17, 31, 73, 47, 23 });
  unsigned char skip= 0, pos= 0;

  for (int _{ 0 }; _ < 64; ++_)
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
  std::ostringstream oss;
  oss.flags(std::ios::hex);
  oss.fill('0');

  for (auto b = std::begin(list); b != std::end(list); std::advance(b, 16))
    oss << std::setw(2) << std::accumulate(b, std::next(b, 16), 0, std::bit_xor<void>());
  return oss.str();
}

int htoi(char c)
{
  return c - '0' + (c >= 'a') * (10 + '0' - 'a');
}

std::array<bool, 128> hash2array(std::string const & hash) 
{
  std::array<bool, 128> arr;
  auto a = std::begin(arr);
  for (auto h : hash) 
  {
    auto const d = static_cast<unsigned char>(htoi(h));
    *a++ = (d >> 3) & 1;
    *a++ = (d >> 2) & 1;
    *a++ = (d >> 1) & 1;
    *a++ = d & 1;
  }
  return arr;
}


long long adventDay14problem12017(std::string& input)
{
  disjoint_set<Pair, PairHash> set;
  std::array<bool, 128> prev;
  std::fill(std::begin(prev), std::end(prev), false);

  for (int row = 0; row < 128; ++row) 
  {
    std::string str{ (std::ostringstream{} << input << "-" << std::to_string(row)).str() };
    auto hash = hash2array(knot_hash(str));
    for (int col = 0; col < 128; ++col) 
    {
      if (hash[col]) 
      {
        set.find({ row, col });
        if (prev[col])
          set.join({ row, col }, { row - 1, col });
        if (col > 0 && hash[col - 1])
          set.join({ row, col }, { row, col - 1 });
      }
    }
    prev = hash;
  }

  return set.size();
}

long long adventDay14problem22017(std::string& input)
{
  disjoint_set<Pair, PairHash> set;
  std::array<bool, 128> prev;
  std::fill(std::begin(prev), std::end(prev), false);

  for (int row = 0; row < 128; ++row) 
  {
    std::string str{ (std::ostringstream{} << input << "-" << std::to_string(row)).str() };
    auto hash = hash2array(knot_hash(str));
    for (int col = 0; col < 128; ++col) 
    {
      if (hash[col]) 
      {
        set.find({ row, col });
        if (prev[col])
          set.join({ row, col }, { row - 1, col });
        if (col > 0 && hash[col - 1])
          set.join({ row, col }, { row, col - 1 });
      }
    }
    prev = hash;
  }
  
  return set.sets();
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string input = "stpzcrnm";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  input.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay14problem12017(input)
                              : adventDay14problem22017(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day14/input14.txt";
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