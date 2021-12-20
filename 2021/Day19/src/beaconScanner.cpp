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
#include <sensor.h>

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::string line;
  std::vector<std::string> output;

  while (!input.eof())
  {
    std::getline(input, line);
    //if (line != "")
    {
      output.push_back(line);
    }
  }
  input.close();

  return output;
}

std::vector<std::vector<std::string>> splitByEmptyStrings( std::vector<std::string> strs) 
{
  std::vector<std::vector<std::string>> splits;
  std::vector<std::string> current_split;

  for (std::string& str : strs) 
  {
    if (!str.empty()) 
    {
      current_split.emplace_back(std::move(str));
      continue;
    }

    if (current_split.empty()) continue;

    splits.emplace_back(std::move(current_split));
    current_split.clear();
  }
  if (!current_split.empty()) 
    splits.emplace_back(std::move(current_split));

  return splits;
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

uint64_t adventDay19problem12021(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseInput(input);
  std::vector<std::vector<std::string>> scannerLines = splitByEmptyStrings(std::move(inputLines));
  std::list<SensorData> sensorData;

  for (const std::vector<std::string>& scannerDesc : scannerLines)
  {
    std::vector<DimensionGrid<3>::Vec> beacon_signals;
    for (auto line_it = scannerDesc.begin() + 1; line_it != scannerDesc.end(); ++line_it)
    {
      beacon_signals.emplace_back(DimensionGrid<3>::Point::parseCommaSeparated(*line_it) -DimensionGrid<3>::Points::kOrigin);
    }
    sensorData.emplace_back(std::move(beacon_signals));
  }

  std::vector<SensorData> exhausted;
  std::deque<SensorData> resolved;

  resolved.emplace_back(std::move(sensorData.front()));
  sensorData.erase(sensorData.begin());
  resolved.front().SetPosition(DimensionGrid<3>::Points::kOrigin);

  while (!sensorData.empty())
  {
    std::cout << "Resolved " << (resolved.size() + exhausted.size()) << " sensors (" << exhausted.size() << " exhausted)\n";

    SensorData currentResolved = std::move(resolved.front());
    resolved.pop_front();
    std::vector<std::list<SensorData>::iterator> newlyResolved;

    for (auto unresolved_it = sensorData.begin(); unresolved_it != sensorData.end(); ++unresolved_it) 
    {
      if (unresolved_it->MatchToKnown(currentResolved))
      {
        resolved.emplace_back(std::move(*unresolved_it));
        newlyResolved.emplace_back(unresolved_it);
      }
    }
    exhausted.emplace_back(std::move(currentResolved));

    for (const auto to_remove : newlyResolved)
      sensorData.erase(to_remove);
  }

  std::cout << "Resolved " << (resolved.size() + exhausted.size()) << " sensors (" << exhausted.size() << " exhausted)\n";

  exhausted.insert(exhausted.end(), std::make_move_iterator(resolved.begin()), std::make_move_iterator(resolved.end()));

  std::unordered_set<DimensionGrid<3>::Point, dimGridPointHash> beacons;
  for (const SensorData& sensor : exhausted) 
  {
    auto beacons_from_sensor = sensor.AbsoluteBeaconPositions();
    beacons.insert(beacons_from_sensor.begin(), beacons_from_sensor.end());
  }

  return  beacons.size();
}

uint64_t adventDay19problem22021(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseInput(input);
  std::vector<std::vector<std::string>> scannerLines = splitByEmptyStrings(std::move(inputLines));
  std::list<SensorData> sensorData;

  for (const std::vector<std::string>& scannerDesc : scannerLines)
  {
    std::vector<DimensionGrid<3>::Vec> beacon_signals;
    for (auto line_it = scannerDesc.begin() + 1; line_it != scannerDesc.end(); ++line_it)
    {
      beacon_signals.emplace_back(DimensionGrid<3>::Point::parseCommaSeparated(*line_it) - DimensionGrid<3>::Points::kOrigin);
    }
    sensorData.emplace_back(std::move(beacon_signals));
  }

  std::vector<SensorData> exhausted;
  std::deque<SensorData> resolved;

  resolved.emplace_back(std::move(sensorData.front()));
  sensorData.erase(sensorData.begin());
  resolved.front().SetPosition(DimensionGrid<3>::Points::kOrigin);

  while (!sensorData.empty())
  {
    std::cout << "Resolved " << (resolved.size() + exhausted.size()) << " sensors (" << exhausted.size() << " exhausted)\n";

    if (resolved.empty())
    {
      sensorData.erase(sensorData.begin());
      if (sensorData.empty()) break;
      resolved.emplace_back(std::move(sensorData.front()));
      sensorData.erase(sensorData.begin());
      resolved.front().SetPosition(DimensionGrid<3>::Points::kOrigin);
    }

    SensorData currentResolved = std::move(resolved.front());
    resolved.pop_front();
    std::vector<std::list<SensorData>::iterator> newlyResolved;

    for (auto unresolved_it = sensorData.begin(); unresolved_it != sensorData.end(); ++unresolved_it)
    {
      if (unresolved_it->MatchToKnown(currentResolved))
      {
        resolved.emplace_back(std::move(*unresolved_it));
        newlyResolved.emplace_back(unresolved_it);
      }
    }
    exhausted.emplace_back(std::move(currentResolved));

    for (const auto to_remove : newlyResolved)
      sensorData.erase(to_remove);
  }

  std::cout << "Resolved " << (resolved.size() + exhausted.size()) << " sensors (" << exhausted.size() << " exhausted)\n";
  
  exhausted.insert(exhausted.end(), std::make_move_iterator(resolved.begin()), std::make_move_iterator(resolved.end()));
  
  std::int64_t max_manhattan = -1;
  for (const SensorData& outer : exhausted) 
  {
    for (const SensorData& inner : exhausted) 
    {
      max_manhattan = std::max(max_manhattan, (outer.position() - inner.position()).ManhattanDistance());
    }
  }
  
  return max_manhattan;
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay19problem12021(infile)
                                       : adventDay19problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day19/input01.txt";
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