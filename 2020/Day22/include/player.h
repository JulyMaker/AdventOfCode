#include <queue>

class Player
{

public:
  Player::Player(std::string name);
  Player::Player(Player p, int num);
  
  std::string getName();
  void includeCard(int card);
  
  int getCard();
  std::queue<int> getDecks();
  int deckSize();

  long long win();
  bool lose();

private:
  std::string name;
  std::queue<int> decks;
};