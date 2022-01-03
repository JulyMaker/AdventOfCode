#include <utils.h>

struct CompareByatan2 
{
  bool operator()(std::pair<int, int> s1, std::pair<int, int> s2) const 
  {
    return atan2(s1.first, s1.second) > atan2(s2.first, s2.second);
  }
};

uint64_t adventDay10problem12019(std::ifstream& input)
{
  std::string line;
  std::vector<std::pair<int, int>> asteroids;
  for (int row = 0; getline(input, line); ++row)
    for (int col = 0; col < line.size(); ++col)
      if (line[col] == '#')
        asteroids.emplace_back(col, row);

  std::map<std::pair<int, int>, std::vector<int>, CompareByatan2>  gcdsBySlopeForBestAsteroid;
  
  int bestX = 0, bestY = 0;
  auto result = 0;
  for (auto [ax, ay] : asteroids) 
  {
    std::map<std::pair<int, int>, std::vector<int>, CompareByatan2> gcdsBySlope;
    for (auto [bx, by] : asteroids) 
    {
      if (bx == ax && by == ay)
        continue;
      auto dx = bx - ax;
      auto dy = by - ay;
      auto g = std::abs(std::gcd(dx, dy));
      gcdsBySlope[{dx / g, dy / g}].push_back(g);
    }

    if (gcdsBySlope.size() > result) 
    {
      result = gcdsBySlope.size();
      bestX = ax;
      bestY = ay;
      gcdsBySlopeForBestAsteroid = gcdsBySlope;
    }
  }

	return result;
}

uint64_t adventDay10problem22019(std::ifstream& input)
{
  std::string line;
  std::vector<std::pair<int, int>> asteroids;
  for (int row = 0; getline(input, line); ++row)
    for (int col = 0; col < line.size(); ++col)
      if (line[col] == '#')
        asteroids.emplace_back(col, row);

  std::map<std::pair<int, int>, std::vector<int>, CompareByatan2>  gcdsBySlopeForBestAsteroid;

  int bestX = 0, bestY = 0;
  auto result = 0;
  for (auto [ax, ay] : asteroids)
  {
    std::map<std::pair<int, int>, std::vector<int>, CompareByatan2> gcdsBySlope;
    for (auto [bx, by] : asteroids)
    {
      if (bx == ax && by == ay)
        continue;
      auto dx = bx - ax;
      auto dy = by - ay;
      auto g = std::abs(std::gcd(dx, dy));
      gcdsBySlope[{dx / g, dy / g}].push_back(g);
    }

    if (gcdsBySlope.size() > result)
    {
      result = gcdsBySlope.size();
      bestX = ax;
      bestY = ay;
      gcdsBySlopeForBestAsteroid = gcdsBySlope;
    }
  }

  for (auto& [pos, qOfGs] : gcdsBySlopeForBestAsteroid)
    std::sort(qOfGs.begin(), qOfGs.end(), std::greater<>());

  std::vector<int> destructionOrder;
  while (destructionOrder.size() < 200) 
  {
    for (auto& [pos, qOfGs] : gcdsBySlopeForBestAsteroid) 
    {
      if (qOfGs.empty())
        continue;
      auto [dx, dy] = pos;
      auto g = qOfGs.back();
      qOfGs.pop_back();
      destructionOrder.emplace_back((bestX + g * dx) * 100 + bestY + g * dy);
    }
  }

  return destructionOrder.at(199);
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "10";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay10problem12019(inputFile); break;
    case 2: result = adventDay10problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}