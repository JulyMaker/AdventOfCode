#include <iostream>
#include <string>
#include <fstream>
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

const int FEATURES = 4;
const int TOTAL_TABLESPOONS = 100;

struct Ingredient 
{
  std::valarray <int> data; 
  int calories;

  explicit Ingredient() : data(FEATURES), calories{ 0 } { }
  Ingredient(const std::valarray <int> & d, int c) : data{ d }, calories{ c } { }
};

void process(std::vector<Ingredient>& ingredients,int &count,  std::string& line)
{
  const static std::regex PARSE{ R"(\w+: \w+ (-?\d+), \w+ (-?\d+), \w+ (-?\d+), \w+ (-?\d+), \w+ (-?\d+))" };
  std::smatch m;
  
  if (regex_search(line, m, PARSE))
  {
    ingredients.emplace_back(std::valarray <int> { std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4]) }, std::stoi(m[5]));
    ++count;
  }
}

void combine(int count, int ttablespoons, int* dest, std::function<void()> doNext)
{
  if (count == 1)
  {
    *dest = ttablespoons;
    doNext();
  }
  else
    for (int i = 0; i <= ttablespoons; ++i)
    {
      *dest = i;
      combine(count - 1, ttablespoons - i, dest + 1, doNext);
    }
      
}

void for_all(int count, int ttablespoons, std::function <void(int*)> f) 
{
  int dest[FEATURES];

  combine(count, ttablespoons, dest, [&] {
    f(dest);
  });
}

long long adventDay15problem12015(std::vector<Ingredient>& ingredients, int &count)
{ 
  int max = 0;

  for_all(count, TOTAL_TABLESPOONS, [&](int* counts) 
  {
    Ingredient ingred;
    for (int i{ 0 }; i < count; ++i)
    {
      ingred.data += counts[i] * ingredients[i].data;
      ingred.calories += counts[i] * ingredients[i].calories;
    }
      
      max = std::max(max, std::accumulate(std::begin(ingred.data), std::end(ingred.data), 1, [](int p, int v) { return p * std::max(v, 0); }));
  });

  return max;
}

long long adventDay15problem22015(std::vector<Ingredient>& ingredients, int &count)
{
  int max = 0;

  for_all(count, TOTAL_TABLESPOONS, [&](int* counts)
  {
    Ingredient ingred;
    for (int i{ 0 }; i < count; ++i)
    {
      ingred.data += counts[i] * ingredients[i].data;
      ingred.calories += counts[i] * ingredients[i].calories;
    }

    if (ingred.calories == 500)
      max = std::max(max, std::accumulate(std::begin(ingred.data), std::end(ingred.data), 1, [](int p, int v) { return p * std::max(v, 0); }));
  });

  return max;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<Ingredient> ingredients;
  int count=0;
  
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(ingredients, count, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay15problem12015(ingredients, count)
                              : adventDay15problem22015(ingredients, count);

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