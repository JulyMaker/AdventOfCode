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

void parse(std::ifstream& infile, int& players, int& points)
{
  std::string line;
  std::getline(infile, line);
  infile.close();
 
  const std::regex pat{ "(\\d+) players; last marble is worth (\\d+) points*" };

  std::smatch match;
  std::regex_search(line, match, pat);

  players = std::stoi(match[1].str());
  points = std::stoi(match[2].str());
}

long long adventDay09problem12018(std::ifstream& is, int times)
{
  int players = 0;
  int points = 0;
  parse(is, players, points);
  points *= times;

  std::list<long> marbles;

  std::vector<long long> scores(players, 0);
  int currentPlayer = 0;
  long long maxScore = INT_MIN;

  marbles.push_back(0);
  std::list<long>::iterator currentMarble = marbles.begin();

  for (int i = 1; i <= points; i++) 
  {
    if (i % 23 == 0) 
    {
      scores[currentPlayer] += i;
      for (int j = 0; j < 7; j++) {
        if (currentMarble == marbles.begin()) 
          currentMarble = marbles.end();
        currentMarble--;
      }
      scores[currentPlayer] += *currentMarble;
      currentMarble = marbles.erase(currentMarble);
      if (currentMarble == marbles.end()) 
        currentMarble = marbles.begin();

      if (scores[currentPlayer] > maxScore) 
        maxScore = scores[currentPlayer];
    }
    else {
      for (int j = 0; j < 2; j++) 
      {
        if (currentMarble == marbles.end()) 
          currentMarble = marbles.begin();
        currentMarble++;
      }
      currentMarble = marbles.insert(currentMarble, i);
    }
    currentPlayer = (currentPlayer + 1) % players;
  }

  return maxScore;
}


long long adventDay09problem22018(std::ifstream& is, int times)
{
  return adventDay09problem12018(is, times);
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay09problem12018(infile, 1)
                                        : adventDay09problem22018(infile, 100);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day09/input09.txt";
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