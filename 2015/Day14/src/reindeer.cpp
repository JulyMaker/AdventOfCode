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

const int TIME = 2503;

#define COMPARE_BY(X) [] (const auto & d1, const auto & d2) { return d1.X < d2.X; }

struct Reindeer 
{
  int speed = 0;
  int go = 0;
  int rest = 0;
  int distance = 0; 
  int points =0;

  explicit Reindeer() {}
  Reindeer(int _s, int _g, int _r) : speed{ _s }, go{ _g }, rest{ _r } { }

  void tick(int t) {
    if (t % (go + rest) < go) distance += speed;
  }
};

void process(std::vector<Reindeer>& sled, std::string& line)
{
  const static std::regex PARSE{ R"(\w+ can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.)" };
  std::smatch m;

  if (regex_search(line, m, PARSE))
  {
    sled.emplace_back(std::stoi(m[1].str()), std::stoi(m[2].str()), std::stoi(m[3].str()));
  } 
}

long long adventDay14problem12015(std::vector<Reindeer>& sled)
{ 
  for (int t= 0; t < TIME; ++t) 
  {
    for (auto && reind : sled)
      reind.tick(t);
  }
 
  return std::max_element(sled.cbegin(), sled.cend(), COMPARE_BY(distance))->distance;;
}

long long adventDay14problem22015(std::vector<Reindeer>& sled)
{
  for (int t=0; t < TIME; ++t) 
  {
    for (auto && reind : sled)
      reind.tick(t);

    std::vector<int> leadersTable;
    int lead= 0;

    for (auto && reind : sled) 
    {
      if (reind.distance > lead)
      {
        leadersTable.clear();
        lead = reind.distance;
      }
        
      if (reind.distance == lead)
        leadersTable.push_back(&reind - &sled[0]);
    }

    for (auto && name : leadersTable)
      ++sled[name].points;
  }

  return std::max_element(sled.cbegin(), sled.cend(), COMPARE_BY(points))->points;
}

long long readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector <Reindeer> sled;
  
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    //infile >> line;
  
    if (line == "") continue;
   
    process(sled, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay14problem12015(sled)
                              : adventDay14problem22015(sled);

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