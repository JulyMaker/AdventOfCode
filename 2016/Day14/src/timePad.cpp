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
#include "md5.h"

struct LSet {
  std::set<int> v;
  std::mutex    m;
  
  void put(int val)
  {
    std::lock_guard<std::mutex> g{ m };
    v.emplace(val);
  }
};

int htoi(char c)
{
  return c - '0' + (c >= 'a') * (10 + '0' - 'a');
}

char itoh(int v)
{
  char const digit[] = "0123456789abcdef";
  return digit[v];
}

int fast_itoa(int i, char* b)
{
  char const digit[] = "0123456789";
  char*      p = b;
  int        shifter = i;

  do
    ++p;
  while (shifter /= 10);

  *p = '\0';
  int dist(p - b);
  do
    *--p = digit[i % 10];
  while (i /= 10);

  return dist;
}

template <int N = -1, typename Fn, typename... Args>
void parallel_do(Fn&& f, Args&&... args)
{
  std::vector<std::thread> threads;
  const int groupSize((N == -1) ? std::thread::hardware_concurrency() : N);

  for (int idx= 0; idx < groupSize; ++idx)
    threads.emplace_back(f, idx, groupSize, std::forward<Args>(args)...);

  for (auto& t : threads)
    t.join();
}

void key(const char* input, size_t len, std::string& digest)
{
  digest = md5(input);
}

void key2(const char* input, size_t len, std::string& digest)
{
  digest = md5(input);
  for (int i = 0; i < 2016; ++i)
    digest = md5(digest);
}

template <int N, int Limit, typename Itr, typename Fn>
void findSeq(Itr begin, Itr end, Fn&& f)
{
  int count= 0;
  Itr curr;

  while (std::distance(begin, end) >= N) 
  {
    for (curr = begin + 1; curr != end; ++curr)
      if (*curr != *begin)
        break;

    if (std::distance(begin, curr) >= N) 
    {
      f(*begin);
      if (++count == Limit)
        return;
    }
    begin = curr;
  }
}

const int GOAL = 64;
const int WINDOW = 1000;
const int LIMIT = 25600;


long long adventDay14problem12016(std::string instrucc)
{    
  std::array<LSet, 16> l3, l5;
  std::vector<int> ind;

  parallel_do([&](unsigned int tid, unsigned int N) 
  {
    std::string input{ instrucc };
    std::string buf;
    uint32_t    length(input.size());
    input.reserve(length + 10);

    for (unsigned int val= tid; val < LIMIT; val += N) 
    {
      key(input.data(), length + fast_itoa(val, &input[length]), buf);
      findSeq<5, 32>(buf.cbegin(), buf.cend(), [&](char c) { l5[htoi(c)].put(val); });
      findSeq<3, 1>(buf.cbegin(), buf.cend(), [&](char c) { l3[htoi(c)].put(val); });
    }
  });

  for (int i = 0; i < 16; ++i)
  {
    for (auto i3 : l3[i].v)
    {
      for (auto i5 : l5[i].v)
      {
        if (i3 < i5 && i5 - i3 < WINDOW)
        {
          ind.emplace_back(i3);
          break;
        }
      }
    }
  }    
        
  std::sort(ind.begin(), ind.end());
  return ind[GOAL - 1];
}

long long adventDay14problem22016(std::string instrucc)
{
  std::array<LSet, 16> l3, l5;
  std::vector<int> ind;

  parallel_do([&](unsigned int tid, unsigned int N)
  {
    std::string input{ instrucc };
    std::string buf;
    uint32_t    length(input.size());
    input.reserve(length + 10);

    for (unsigned int val = tid; val < LIMIT; val += N)
    {
      key2(input.data(), length + fast_itoa(val, &input[length]), buf);
      findSeq<5, 32>(buf.cbegin(), buf.cend(), [&](char c) { l5[htoi(c)].put(val); });
      findSeq<3, 1>(buf.cbegin(), buf.cend(), [&](char c) { l3[htoi(c)].put(val); });
    }
  });

  for (int i = 0; i < 16; ++i)
  {
    for (auto i3 : l3[i].v)
    {
      for (auto i5 : l5[i].v)
      {
        if (i3 < i5 && i5 - i3 < WINDOW)
        {
          ind.emplace_back(i3);
          break;
        }
      }
    }
  }

  std::sort(ind.begin(), ind.end());
  return ind[GOAL - 1];
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  std::string instrucc = "cuanljph";
  long long result = 0;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  instrucc.push_back(line);
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay14problem12016(instrucc)
                              : adventDay14problem22016(instrucc);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 2)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[1]))
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