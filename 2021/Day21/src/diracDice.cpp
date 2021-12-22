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
#include <game.h>
#include <game2.h>

std::vector<int> parseInput(std::ifstream& input)
{
  std::string player1;
  std::string player2;
  std::vector<int> output;

  std::getline(input, player1);
  std::getline(input, player2);
  input.close();

  const std::regex pat{ "Player \\d+ starting position: (\\d+)" };
  std::smatch match;

  std::regex_search(player1, match, pat);
  output.push_back(std::stoi(match[1].str()) -1);
  std::regex_search(player2, match, pat);
  output.push_back(std::stoi(match[1].str()) -1);

  return output;
}


uint64_t adventDay21problem12021(std::ifstream& input)
{
  std::vector<int> inputInt = parseInput(input);

  GameState game({ inputInt[0], inputInt[1] });

  return  game.playUntilWin();
}

uint64_t adventDay21problem22021(std::ifstream& input)
{
  std::vector<int> inputInt = parseInput(input);

  GameState2 game;
  game.player1.position = inputInt[0];
  game.player2.position = inputInt[1];

  std::unordered_map<GameState2, int64_t, gameHash> gameToUniverses{ {game, 1} };
  std::unordered_set<GameState2, gameHash> enqueued{ game };

  std::priority_queue<GameState2, std::vector<GameState2>, GreaterTotalScore> toProcess;
  toProcess.emplace(game);
  while (!toProcess.empty())
  {
    GameState2 current = toProcess.top();
    toProcess.pop();
    int64_t universesIn = gameToUniverses.at(current);
    for (auto [nextState, expansionFactor] : current.expandUniverses()) 
    {
      if (!nextState.Win() && enqueued.emplace(nextState).second)
      {
        toProcess.emplace(nextState);
      }
      gameToUniverses[nextState] += universesIn * expansionFactor;
    }
  }

  int64_t player1_wins = 0;
  int64_t player2_wins = 0;
  for (const auto& [game, universes] : gameToUniverses)
  {
    if (game.player1.win()) 
      player1_wins += universes;
    if (game.player2.win()) 
      player2_wins += universes;
  }

  return  std::max(player1_wins, player2_wins);
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay21problem12021(infile)
                                       : adventDay21problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day21/input01.txt";
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