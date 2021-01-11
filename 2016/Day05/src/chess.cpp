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
#include <thread>
#include "md5.h"

int htoi(char c)
{
  return c - '0' + (c >= 'a') * (10 + '0' - 'a');
}

char itoh(int v)
{
  char const digit[] = "0123456789abcdef";
  return digit[v];
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

template <typename T>
auto is_value(T val)
{
  return [val](T other) { return other == val; };
}

long long adventDay05problem12016(std::string& line)
{
  const int SIZE= 8;
  int numDone = 0;

  std::string password(SIZE, '_');
  std::string in = line;
  
  parallel_do([&](int groupIdx, int groupSize, std::string input) 
  {
    int id= groupIdx;
    
    for (; numDone != SIZE; id += groupSize) 
    {
      std::string buf = input+std::to_string(id);
      buf = md5(buf);
      if (!std::all_of(buf.cbegin(), buf.cbegin() + 5, is_value('0')))
        continue;

      int num= htoi(buf[5]);

      password[numDone] = itoh(num);
      ++numDone;  
    }
  }, in);

  std::cout << "Result: " << password << std::endl;
  return 0;
}

long long adventDay05problem22016(std::string& line)
{
  const int SIZE = 8;
  int numDone = 0;

  std::string password(SIZE, '_');
  std::string in = line;

  parallel_do([&](int groupIdx, int groupSize, std::string input)
  {
    int id = groupIdx;

    for (; numDone != SIZE; id += groupSize)
    {
      std::string buf = input + std::to_string(id);
      buf = md5(buf);
      if (!std::all_of(buf.cbegin(), buf.cbegin() + 5, is_value('0')))
        continue;

      int num = htoi(buf[6]);
      int pos = htoi(buf[5]);

      if ((pos >= SIZE || password[pos] != '_'))
        continue;

      password[pos] = itoh(num);
      ++numDone;
    }
  }, in);

  std::cout << "Result: " << password << std::endl;
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  std::string line = "ffykfhsq"; //"abc"; //

  //std::vector<std::string> values;
  ////int result=0;
  //
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  values.push_back(line);
  //}
  //infile.close();

  return (problNumber == 1)? adventDay05problem12016(line)
                           : adventDay05problem22016(line);

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