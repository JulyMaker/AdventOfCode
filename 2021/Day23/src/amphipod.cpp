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
#include <astar.h>
#include <astarN.h>

std::vector<std::string> parseInput(std::ifstream& input)
{
  std::vector<std::string> output;
  std::string line;

  while (!input.eof()) 
  {
    std::getline(input, line);
    if (line != "") 
    { 
      output.push_back(line);
    }
  }
  input.close();

  return output;
}


uint64_t adventDay23problem12021(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseInput(input);

  State initialState{.hallWay = {parseCell(inputLines[1][1]), parseCell(inputLines[1][2]),
                                 parseCell(inputLines[1][3]), parseCell(inputLines[1][4]),
                                 parseCell(inputLines[1][5]), parseCell(inputLines[1][6]),
                                 parseCell(inputLines[1][7]), parseCell(inputLines[1][8]),
                                 parseCell(inputLines[1][9]), parseCell(inputLines[1][10]), parseCell(inputLines[1][11])},
                     .roomA = {parseCell(inputLines[2][3]), parseCell(inputLines[3][3])},
                     .roomB = {parseCell(inputLines[2][5]), parseCell(inputLines[3][5])},
                     .roomC = {parseCell(inputLines[2][7]), parseCell(inputLines[3][7])},
                     .roomD = {parseCell(inputLines[2][9]), parseCell(inputLines[3][9])} };

  std::unordered_map<State, std::vector<State>, stateHash> successors;
  std::unordered_map<std::pair<State, State>, int64_t, statePairHash> edgeCosts;

  auto getAdjacent = [&successors, &edgeCosts](const State& start) -> std::vector<State> 
  {
    auto known_it = successors.find(start);
    if (known_it != successors.end()) 
    {
      return known_it->second;
    }

    std::vector<std::pair<State, int64_t>> stateAndCost = start.successorStates();

    std::vector<State> states;
    for (const auto& [state, _] : stateAndCost)
    {
      states.emplace_back(state);
    }

    successors.emplace(start, states);

    for (auto& [state, cost] : stateAndCost)
    {
      edgeCosts.emplace(std::make_pair(start, std::move(state)), cost);
    }

    return states;
  };

  auto getCost = [&edgeCosts](const State& start, const State& next) -> int64_t 
  {
      auto cost_it = edgeCosts.find({ start, next });
      return cost_it->second;
  };

  auto path = AStar(initialState, kGoalState, getAdjacent, getCost);

  return  path->cost;
}

uint64_t adventDay23problem22021(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseInput(input);
  
  StateN initialStateN{ .hallway = {},
                        .room_a = {ParseCell(inputLines[2][3]), CellN::kD, CellN::kD, ParseCell(inputLines[3][3])},
                        .room_b = {ParseCell(inputLines[2][5]), CellN::kC, CellN::kB, ParseCell(inputLines[3][5])},
                        .room_c = {ParseCell(inputLines[2][7]), CellN::kB, CellN::kA, ParseCell(inputLines[3][7])},
                        .room_d = {ParseCell(inputLines[2][9]), CellN::kA, CellN::kC, ParseCell(inputLines[3][9])} };
  
  std::unordered_map<StateN, std::vector<StateN>, stateNHash> successors;
  std::unordered_map<std::pair<StateN, StateN>, int64_t, stateNPairHash> edge_costs;
  
  auto get_adjacent = [&successors, &edge_costs](const StateN& start) -> std::vector<StateN> 
  {
    auto known_it = successors.find(start);
    if (known_it != successors.end()) 
    {
      return known_it->second;
    }
  
    std::vector<std::pair<StateN, int64_t>> state_and_cost = start.SuccessorStates();
  
    std::vector<StateN> states;
    for (const auto& [state, _] : state_and_cost) 
    {
      states.emplace_back(state);
    }
    successors.emplace(start, states);
  
    for (auto& [state, cost] : state_and_cost) 
    {
      edge_costs.emplace(std::make_pair(start, std::move(state)), cost);
    }
  
    return states;
  };
  
  auto get_cost = [&edge_costs](const StateN& start, const StateN& next) -> int64_t
  {
      auto cost_it = edge_costs.find({ start, next });
      return cost_it->second;
  };
  
  auto path = AStarN(initialStateN, kGoalStateN, get_adjacent, get_cost);
  
  return  path->cost;
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay23problem12021(infile)
                                       : adventDay23problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day23/input01.txt";
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