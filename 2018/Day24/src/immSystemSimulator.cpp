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
#include <deque>
#include <queue>
#include <ctype.h>

enum class Team
{
  immune,
  infection
};

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));

  return tokens;
}

std::vector<std::string>parseWeakImmune(const std::vector<std::string>& elements, const std::string& name)
{
  std::vector<std::string> result;
  auto element(std::find(elements.begin(), elements.end(), name));
  if (element != elements.end())
  {
    std::advance(element, 2);
    while (element->back() == ',')
    {
      result.push_back(element->substr(0, element->size() - 1));
      ++element;
    }
    result.push_back(*element);
  }
  return result;
}

struct Unit
{
  int64_t num_units, hp, attack_damage, initiative;
  std::string attack_type;
  std::vector<std::string> immune, weak;
  Team team;
  Unit(const std::string& line, const Team& TEAM) : team(TEAM)
  {
    std::vector<std::string> elements;
    elements = split(line, " ();"); //boost::split(elements, line, boost::is_any_of(" ();"));
    num_units = std::stoi(elements.at(0));
    hp = std::stoi(elements.at(4));

    auto element(std::find(elements.begin(), elements.end(), "does"));
    ++element;
    attack_damage = std::stoi(*element);
    ++element;
    attack_type = *element;

    element = std::find(elements.begin(), elements.end(), "initiative");
    ++element;
    initiative = std::stoi(*element);

    weak = parseWeakImmune(elements, "weak");
    immune = parseWeakImmune(elements, "immune");
  }

  int64_t power() const { return num_units * attack_damage; }

  bool operator<(const Unit& unit) const
  {
    return power() < unit.power()
      ? true
      : (power() == unit.power() ? (initiative < unit.initiative)
        : false);
  }

  bool operator>(const Unit& unit) const { return unit < *this; }
};

std::vector<Unit> parseInput(std::ifstream& infile)
{
  std::string line;
  std::vector<Unit> units;

  std::getline(infile, line);
  std::getline(infile, line);
  while (!line.empty())
  {
    units.emplace_back(line, Team::immune);
    std::getline(infile, line);
  }

  std::getline(infile, line);
  std::getline(infile, line);
  while (!line.empty())
  {
    units.emplace_back(line, Team::infection);
    std::getline(infile, line);
  }

  return units;
}

std::ostream& operator<<(std::ostream& os, const Unit& unit)
{
  if (unit.team == Team::immune)
  {
    os << "Immune: ";
  }
  else
  {
    os << "Infection: ";
  }

  os << unit.num_units << " " << unit.hp << " attack " << unit.attack_damage
    << " " << unit.attack_type << " initiative " << unit.initiative;
  if (!unit.weak.empty())
  {
    os << " weak";
    for (auto& weak : unit.weak)
    {
      os << " " << weak;
    }
  }
  if (!unit.immune.empty())
  {
    os << " immune";
    for (auto& immune : unit.immune)
    {
      os << " " << immune;
    }
  }
  return os;
}

bool fightFinished(const std::vector<Unit>& units)
{
  return std::find_if(units.begin(), units.end(),
    [](const Unit& unit) { return unit.team == Team::immune; })
    == units.end() || std::find_if(units.begin(), units.end(), [](const Unit& unit) {
    return unit.team == Team::infection;
      }) == units.end();
}

std::vector<Unit> fightWithHelp(const std::vector<Unit>& units_orig, const int64_t& help)
{
  std::vector<Unit> units(units_orig);
  for (auto& unit : units)
  {
    if (unit.team == Team::immune)
      unit.attack_damage += help;
  }

  size_t round(0);
  while (!fightFinished(units))
  {
    std::sort(units.begin(), units.end(), std::greater<Unit>());

    std::vector<std::pair<std::vector<Unit>::iterator, int64_t>> attacks;
    for (auto& unit : units)
    {
      auto attacked(units.end());
      int64_t attack_multiplier(0);
      for (auto defender(units.begin()); defender != units.end(); ++defender)
      {
        if (defender->team != unit.team && std::find(defender->immune.begin(), defender->immune.end(), unit.attack_type)
            == defender->immune.end() && std::find_if(attacks.begin(), attacks.end(), [&](const std::pair<std::vector<Unit>::iterator, int64_t>
              & attack) { return attack.first == defender; }) == attacks.end())
        {
          int64_t this_unit_multiplier(1);
          if (std::find(defender->weak.begin(), defender->weak.end(), unit.attack_type) != defender->weak.end())
          {
            this_unit_multiplier = 2;
          }

          if (attacked == units.end() || (this_unit_multiplier > attack_multiplier) || (this_unit_multiplier == attack_multiplier && *defender > * attacked))
          {
            attacked = defender;
            attack_multiplier = this_unit_multiplier;
          }
        }
      }
      attacks.emplace_back(attacked, attack_multiplier);
    }

    std::vector<size_t> attack_order(attacks.size());
    std::iota(attack_order.begin(), attack_order.end(), 0);
    std::sort(attack_order.begin(), attack_order.end(),
      [&](const size_t& index0, const size_t& index1) {
        return units[index0].initiative > units[index1].initiative;
      });

    bool any_units_killed(false);
    for (auto& index : attack_order)
    {
      if (attacks[index].first != units.end())
      {
        int64_t total_damage(units[index].power() * attacks[index].second);
        int64_t units_killed(total_damage / (attacks[index].first->hp));
        attacks[index].first->num_units -= units_killed;

        if (attacks[index].first->num_units < 0)
          attacks[index].first->num_units = 0;

        any_units_killed = any_units_killed || (units_killed > 0);

        if (round == 5000)
        {
          std::cout << units[index] << "\n\t"
            << *(attacks[index].first) << "\n\t"
            << attacks[index].second << " " << units_killed
            << " "
            << "\n";
        }
      }
    }

    if (!any_units_killed)
      break;

    std::vector<Unit> new_units;
    for (auto& unit : units)
    {
      if (unit.num_units > 0)
        new_units.push_back(unit);
    }
    std::swap(units, new_units);
    ++round;
  }
  return units;
}

int64_t adventDay24problem12018(std::ifstream& input)
{
  std::vector<Unit> units = parseInput(input);

  int64_t sum(0);
  for (auto& unit : fightWithHelp(units, 0))
    sum += unit.num_units;

  return sum;
}

int64_t adventDay24problem22018(std::ifstream& input)
{
  std::vector<Unit> units = parseInput(input);

  int64_t sum=0;
  for (size_t help = 1; help < 10000; ++help)
  {
    auto fight_result(fightWithHelp(units, help));
    if (std::find_if(fight_result.begin(), fight_result.end(), [](const Unit& unit) { return unit.team == Team::infection; }) == fight_result.end())
    {
      sum = 0;
      for (auto& unit : fight_result)
        sum += unit.num_units;

      break;
    }
  }

  return sum;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay24problem12018(infile)
                                        : adventDay24problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day24/input24.txt";
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