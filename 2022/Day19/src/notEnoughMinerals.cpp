#include <utils.h>

struct Blueprint
{
  int id;

  int costOre;
  int costClay;
  std::pair<int, int> costObsidian;
  std::pair<int, int> costGeode;
};

using State = std::tuple<int, int, int, int, int, int, int, int, int>;

int qualityLevel(Blueprint bp, int time)
{
  int best = 0;
  // State (ore, clay, obsidian, geodes, rateOre, rateClay, rateObsidian, rateGeode, time)
  State start = { 0, 0, 0, 0, 1, 0, 0, 0, time };
  std::queue<State> stack;

  stack.push(start);
  std::set<State> setStates;

  while (!stack.empty())
  {
    State state = stack.front(); stack.pop();

    auto [ore, clay, obsidian, geode, rateOre, rateClay, rateObsidian, rateGeode, time] = state;
    best = std::max(best, geode);

    if (time == 0) continue;

    int maxElem = std::max(bp.costOre, std::max(bp.costClay, std::max(bp.costObsidian.first, bp.costGeode.first)));


    rateOre = std::min(rateOre, maxElem);
    rateClay = std::min(rateClay, bp.costObsidian.second);
    rateObsidian = std::min(rateObsidian, bp.costGeode.second);
    ore = std::min(ore, time * maxElem - rateOre * (time - 1));
    clay = std::min(clay, time * bp.costObsidian.second - rateClay * (time - 1));
    obsidian = std::min(obsidian, time * bp.costGeode.second - rateObsidian * (time - 1));

    state = { ore, clay, obsidian, geode, rateOre, rateClay, rateObsidian, rateGeode, time };
    if (setStates.find(state) != setStates.end()) continue;

    setStates.insert(state);

    // Doing nothing
    stack.push({ ore + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian, rateGeode, time - 1 } );

    if (ore >= bp.costOre) 
      stack.push({ ore - bp.costOre + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre + 1, rateClay, rateObsidian, rateGeode, time - 1 });

    if (ore >= bp.costClay)
      stack.push({ ore - bp.costClay + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay + 1, rateObsidian, rateGeode, time - 1 });

    if (ore >= bp.costObsidian.first && clay >= bp.costObsidian.second)
      stack.push({ ore - bp.costObsidian.first + rateOre, clay - bp.costObsidian.second + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian + 1, rateGeode, time - 1 } );

    if (ore >= bp.costGeode.first && obsidian >= bp.costGeode.second)
      stack.push({ ore - bp.costGeode.first + rateOre, clay + rateClay, obsidian - bp.costGeode.second + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian, rateGeode + 1, time - 1 });
  }

  return best;
}

uint64_t adventDay19problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const int TIME = 24;
  std::vector <Blueprint> blueprints;

  std::vector<std::string> in =parseInputReg(input,"Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.");
  for (int i=0; i < in.size() - 7; i+= 8)
  {
    Blueprint blue;

    blue.id = stoi(in[i + 1]);

    blue.costOre = stoi(in[i + 2]);
    blue.costClay = stoi(in[i + 3]);
    blue.costObsidian = { stoi(in[i + 4]), stoi(in[i + 5]) };
    blue.costGeode = { stoi(in[i + 6]), stoi(in[i + 7]) };

    blueprints.push_back(blue);
  }

  for(auto& bp : blueprints)
  {
    score += bp.id * qualityLevel(bp, TIME);
  }

  return score;
}


uint64_t adventDay19problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  const int TIME = 32;
  std::vector <Blueprint> blueprints;

  std::vector<std::string> in = parseInputReg(input, "Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.");
  for (int i = 0; i < in.size() - 7; i += 8)
  {
    Blueprint blue;

    blue.id = stoi(in[i + 1]);

    blue.costOre = stoi(in[i + 2]);
    blue.costClay = stoi(in[i + 3]);
    blue.costObsidian = { stoi(in[i + 4]), stoi(in[i + 5]) };
    blue.costGeode = { stoi(in[i + 6]), stoi(in[i + 7]) };

    blueprints.push_back(blue);
  }

  score = 1;

  for (int i =0; i < 3; i++)
  {
    score *= qualityLevel(blueprints[i], TIME);
  }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "19";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay19problem12022(inputFile); break;
    case 2: result = adventDay19problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}