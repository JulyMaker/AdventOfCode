#include <utils.h>

struct Ingredient 
{
  int64_t amountRequired;
  std::string ingredientName;
};

struct Reaction 
{
  int64_t makes;
  std::vector<Ingredient> ingredients;
};

void topoHelper(const std::string& name, const std::map<std::string, Reaction>& reactions, std::set<std::string>& visited, std::deque<std::string>& order)
{
  if (name == "ORE")
    return;

  visited.insert(name);
  const auto& [howmuch, ingredients] = reactions.at(name);

  for (const auto& [used, ingredientName] : ingredients)
    if (!visited.count(ingredientName))
      topoHelper(ingredientName, reactions, visited, order);

  order.push_front(name);
}

std::deque<std::string> topoSort(const std::string& name, const std::map<std::string, Reaction>& reactions) 
{
  std::set<std::string> visited;
  std::deque<std::string> order;
  topoHelper(name, reactions, visited, order);

  return order;
}

std::map<std::string, Reaction> readReactionInput(std::istream& ifile) 
{
  std::map<std::string, Reaction> reactions;
  std::string line;
  while (getline(ifile, line)) 
  {
    Ingredient i{ 0, "" };
    std::vector<Ingredient> ingredients;
    std::istringstream iline(line);
    bool done = false;

    while (!done) 
    {
      iline >> i.amountRequired >> i.ingredientName;
      if (i.ingredientName.back() == ',')
        i.ingredientName.pop_back();
      else
        done = true;

      ingredients.push_back(i);
    }
    std::string arrow;
    iline >> arrow >> i.amountRequired >> i.ingredientName; // "=>" num reagent
    reactions[i.ingredientName] = { i.amountRequired, ingredients };
  }
  return reactions;
}


uint64_t adventDay14problem12019(std::ifstream& input)
{
  std::map<std::string, Reaction> reactions = readReactionInput(input);

  auto intDivRoundUp = [](int64_t num, int64_t den) 
  {
    return (num + den - 1) / den;
  };

  std::deque<std::string> chemicalsInOrder = topoSort("FUEL", reactions);

  auto oreNeededForFuel = [&](int64_t fuel) 
  {
    std::map<std::string, int64_t> amountNeeded{ {"FUEL", fuel} };

    for (const auto& chemical : chemicalsInOrder) 
    {
      const auto& [amountReactionMakes, ingredients] = reactions[chemical];
      for (const auto& [reactionRequires, name] : ingredients) 
      {
        auto timesToRunReaction = intDivRoundUp(amountNeeded[chemical], amountReactionMakes);
        amountNeeded[name] += reactionRequires * timesToRunReaction;
      }
    }
    return amountNeeded["ORE"];
  };

	return oreNeededForFuel(1);
}

uint64_t adventDay14problem22019(std::ifstream& input)
{
  std::map<std::string, Reaction> reactions = readReactionInput(input);

  auto intDivRoundUp = [](int64_t num, int64_t den)
  {
    return (num + den - 1) / den;
  };

  std::deque<std::string> chemicalsInOrder = topoSort("FUEL", reactions);

  auto oreNeededForFuel = [&](int64_t fuel)
  {
    std::map<std::string, int64_t> amountNeeded{ {"FUEL", fuel} };

    for (const auto& chemical : chemicalsInOrder)
    {
      const auto& [amountReactionMakes, ingredients] = reactions[chemical];
      for (const auto& [reactionRequires, name] : ingredients)
      {
        auto timesToRunReaction = intDivRoundUp(amountNeeded[chemical], amountReactionMakes);
        amountNeeded[name] += reactionRequires * timesToRunReaction;
      }
    }
    return amountNeeded["ORE"];
  };

  auto lower = 0ull;
  auto upper = 1000000000000ull;
  while (lower != upper) 
  {
    int64_t mid = lower + (upper - lower) / 2;
    if (oreNeededForFuel(mid) <= 1000000000000ull)
      lower = mid + 1;
    else
      upper = mid;
  }

  return lower - 1;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "14";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay14problem12019(inputFile); break;
    case 2: result = adventDay14problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}