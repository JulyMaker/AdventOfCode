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
#include "player.h"

void process(std::vector<Player>& players, std::string& line)
{
  std::smatch sm;
  std::regex regExp("(.*):");

  if (regex_search(line, sm, regExp))
  {
    Player p(sm[1].str());
    players.push_back(p);
  }
  else
  {
    players[players.size() - 1].includeCard(std::stoi(line));
  }
}

void winTurn(Player& player, int c1, int c2)
{
  player.includeCard(c1);
  player.includeCard(c2);
}

long long adventDay22problem1(std::vector<Player>& players)
{
  bool win= false;

  while(!win)
  {
    int cardP1 = players[0].getCard();
    int cardP2 = players[1].getCard();

    (cardP1 > cardP2) ? winTurn(players[0], cardP1, cardP2) : winTurn(players[1], cardP2, cardP1);

    if(players[0].lose())
    {
      return players[1].win();
    }

    if (players[1].lose())
    {
      return players[0].win();
    }
  }

  return 0;
}

long long subGame(Player player1, Player player2)
{
  std::set<std::queue<int>> repeatP1;
  std::set<std::queue<int>> repeatP2;
  while (true)
  {
    repeatP1.insert(player1.getDecks());
    repeatP2.insert(player2.getDecks());

    int cardP1 = player1.getCard();
    int cardP2 = player2.getCard();

    if (cardP1 <= player1.deckSize() && cardP2 <= player2.deckSize())
    {
      Player p1(player1, cardP1);
      Player p2(player2, cardP2);
      int winner = subGame(p1, p2);

      (winner == 1) ? winTurn(player1, cardP1, cardP2) : winTurn(player2, cardP2, cardP1);
    }
    else
    {
      (cardP1 > cardP2) ? winTurn(player1, cardP1, cardP2) : winTurn(player2, cardP2, cardP1);
    }

    if (player1.lose())
      return 2;
    
    if (player2.lose())
      return 1;

    if (repeatP1.count(player1.getDecks()) > 0 || repeatP2.count(player2.getDecks()) > 0) return 1;
  }
}

long long adventDay22problem2(std::vector<Player>& players)
{
  while (true)
  {
    int cardP1 = players[0].getCard();
    int cardP2 = players[1].getCard();

    if (cardP1 <= players[0].deckSize() && cardP2 <= players[1].deckSize())
    {
      Player p1(players[0], cardP1);
      Player p2(players[1], cardP2);
      int winner = subGame(p1, p2);

      (winner == 1)? winTurn(players[0], cardP1, cardP2) : winTurn(players[1], cardP2, cardP1);
    }
    else
    {
      (cardP1 > cardP2) ? winTurn(players[0], cardP1, cardP2) : winTurn(players[1], cardP2, cardP1);
    }
    
    if (players[0].lose())
      return players[1].win();

    if (players[1].lose())
      return players[0].win();
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  long long result=0;
  std::vector<Player> players;

  while (!infile.eof())
  {
    std::getline(infile, line);
  
    if (line == "") continue;

    process(players, line);  
  }
  infile.close();

  result = (problNumber == 1) ? adventDay22problem1(players)
                               : adventDay22problem2(players);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
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

 long long int result = 0;
 switch (std::stoi(argv[2]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}