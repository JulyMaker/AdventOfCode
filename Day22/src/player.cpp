#include "player.h"

Player::Player(std::string playerName)
{
  name = playerName;
}

Player::Player(Player p, int num)
{
  name = p.getName();
  for (int i = 0; i < num; ++i)
    decks.push(p.getCard());
}

std::string Player::getName()
{
  return name;
}

void Player::includeCard(int card) 
{
  decks.push(card);
}

int Player::getCard()
{
  int card = decks.front();
  decks.pop();

  return card;
}

std::queue<int> Player::getDecks()
{
  return decks;
}

int Player::deckSize()
{
  return decks.size();
}

long long Player::win()
{
  long long result=0;
  int pos = decks.size();

  while (!decks.empty())
  {
    result += decks.front() * pos;
    decks.pop();
    pos--;
  }

  return result;
}

bool Player::lose()
{
  return decks.empty();
}