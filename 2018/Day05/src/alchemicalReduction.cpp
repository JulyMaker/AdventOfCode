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


bool are_opposite(char a, char b)
{
  if (isupper(a) && tolower(a) == b)
    return true;
  else if (islower(a) && toupper(a) == b)
    return true;
  else
    return false;
}

int react_polymer(std::string s)
{
  auto it = std::begin(s);
  auto sentry = std::end(s);

  while (it != sentry) {
    auto nit = it + 1;
    if (nit != sentry && are_opposite(it[0], nit[0]))
    {
      it = s.erase(it, nit + 1);
      sentry = std::end(s);

      if (it != std::begin(s))
        --it;
    }
    else {
      ++it;
    }
  }

  return s.size();
}

long long adventDay05problem12018(std::string& input)
{ 
  return react_polymer(input);
}


std::string remove_all_of_char(std::string s, char c)
{
  auto it = std::begin(s);
  auto sentry = std::end(s);
  while (it != sentry) 
  {
    if (it[0] == c || it[0] == toupper(c)) {
      it = s.erase(it);
      sentry = std::end(s);
    }
    else {
      ++it;
    }
  }
  return s;
}

int reduce_react(std::string s, char c)
{
  s = remove_all_of_char(s, c);       // reduce
  return react_polymer(s);            // react
}

template <typename F, typename C, typename D, typename T>
void task_scheduler(F f, const C& src, D& dest, size_t offset, size_t split,
  const T& t)
{
  auto dit = std::begin(dest);
  auto sit = std::begin(src);
  std::advance(dit, offset);
  std::advance(sit, offset);

  auto sentry = std::begin(src);
  std::advance(sentry, std::min(offset + split, src.size()));

  while (sit != sentry) 
  {
    *dit = f(t, *sit);
    ++dit;
    ++sit;
  }
}

template <typename F, typename C, typename D, typename T>
void split_task(F task, const C& src, D& dest, const T& t)
{
  static constexpr size_t MIN_THREADS = 2;

  if (dest.size() < src.size())   // ensure destination is at least same size
    dest.resize(src.size());

  auto num_threads = std::thread::hardware_concurrency();
  auto split = src.size() / num_threads;
  if (split < MIN_THREADS) 
  {
    split = MIN_THREADS;
    num_threads = src.size() / MIN_THREADS;
  }

  auto sched = task_scheduler<F, C, D, T>;
  std::vector<std::thread> vt(num_threads);
  for (size_t i = 0; i < vt.size(); ++i) 
  {
    size_t offset = i * split;
    if (i == vt.size() - 1) split = dest.size() - offset; // ensure splits will cover size
    vt[i] = std::thread{ sched, task, std::cref(src), std::ref(dest),
                        offset, split, std::cref(t) };
  }

  for (auto& t : vt)
    t.join();
}

long long adventDay05problem22018(std::string& input)
{ 
  std::vector<char> alphabet;
  for (char c = 'a'; c <= 'z'; ++c)
    alphabet.push_back(c);

  std::vector<int> lengths(alphabet.size());
  split_task(reduce_react, alphabet, lengths, input);

  auto it_min = std::min_element(lengths.begin(), lengths.end());
  return *it_min;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  
  std::string input;
  long long result = 0;
  
  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;
  
    input = line;
  }
  infile.close();

  result = (problNumber == 1) ? adventDay05problem12018(input)
                              : adventDay05problem22018(input);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day05/input05.txt";
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