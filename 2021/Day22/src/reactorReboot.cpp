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
#include <deque>
#include <stack>
#include <queue>
#include <optional>
#include <grid.h>

struct Procedure
{
  DimensionGrid<3>::Orthotope box;
  bool on = false;

  std::optional<Procedure> Clamp() const
  {
    Procedure clamped;
    clamped.on = on;
    for (size_t d = 0; d < 3; ++d)
    {
      if (box.min_point.coords[d] > 50) return std::nullopt;
      if (box.max_point.coords[d] < -50) return std::nullopt;
      clamped.box.min_point.coords[d] = std::max(box.min_point.coords[d], int64_t{ -50 });
      clamped.box.max_point.coords[d] = std::min(box.max_point.coords[d], int64_t{ 50 });
    }

    return clamped;
  }
};

std::vector<Procedure> parseInput(std::ifstream& input)
{
  std::vector<Procedure> output;
  std::string line;

  const std::regex pat{ "(\\w+) x=(-?\\d+)\.\.(-?\\d+),y=(-?\\d+)\.\.(-?\\d+),z=(-?\\d+)\.\.(-?\\d+)" };
  std::smatch match;

  while (!input.eof()) 
  {
    std::getline(input, line);
    if (line != "") 
    {
      std::regex_search(line, match, pat);

      std::string on_or_off = match[1].str();
      Procedure parsed;  
      parsed.box.min_point.coords[0] = std::stoi(match[2].str());
      parsed.box.max_point.coords[0] = std::stoi(match[3].str());
      parsed.box.min_point.coords[1] = std::stoi(match[4].str());
      parsed.box.max_point.coords[1] = std::stoi(match[5].str());
      parsed.box.min_point.coords[2] = std::stoi(match[6].str());
      parsed.box.max_point.coords[2] = std::stoi(match[7].str());
  
      parsed.on = (on_or_off == "on") ? true : false;
      
      output.push_back(parsed);
    }
  }
  input.close();

  return output;
}

struct dimGridPointHash
{
  std::size_t operator() (const DimensionGrid<3>::Point& p) const
  {
    std::size_t seed = p.coords.size();
    for (auto& i : p.coords)
    {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

uint64_t adventDay22problem12021(std::ifstream& input)
{
  std::vector<Procedure> procedures = parseInput(input);
  std::unordered_set<DimensionGrid<3>::Point, dimGridPointHash> on;

  for (const Procedure& procedure : procedures) 
  {
    std::optional<Procedure> clamped = procedure.Clamp();
    if (!clamped) continue;

    if (clamped->on) 
    {
      on.insert(clamped->box.begin(), clamped->box.end());
    }
    else 
    {
      for (const DimensionGrid<3>::Point& p : clamped->box)
        on.erase(p);
    }
  }

  return  on.size();
}

uint64_t adventDay22problem22021(std::ifstream& input)
{
  std::vector<Procedure> procedures = parseInput(input);

  DimensionGrid<3>::MultiVolume on;
  for (const Procedure& procedure : procedures)
    on = (procedure.on) ? on + procedure.box : on - procedure.box;

  return  on.HyperVolumeInclusive();
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay22problem12021(infile)
                                       : adventDay22problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day22/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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