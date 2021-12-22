#include <initializer_list>
#include<vector>

class Dice 
{
public:
  Dice() = default;

  int roll() 
  {
    ++rolled_;
    const int roll = nextRoll_;
    if (++nextRoll_ > 100) 
      nextRoll_ = 1;

    return roll;
  }

  int timesRolled() const { return rolled_; }

private:
  int nextRoll_ = 1;
  int rolled_ = 0;
};

struct PlayerState 
{
  int position = 0;
  int score = 0;
};

class GameState 
{
public:
  explicit GameState(std::initializer_list<int> playerStartingPositions) 
  {
    for (int pos : playerStartingPositions)
    {
      players_.emplace_back(PlayerState{ pos, 0 });
    }
  }

  int playUntilWin() 
  {
    while(true)
    {
      for (int playerIdx = 0; playerIdx < 2; ++playerIdx)
      {
        if (takeTurn(players_[playerIdx]))
        {
          return players_[playerIdx == 0 ? 1 : 0].score * dice_.timesRolled();
        }
      }
    }
  }

private:
  bool takeTurn(PlayerState& player) 
  {
    int nextPosition = (dice_.roll() + dice_.roll() + dice_.roll() + player.position) % 10;
    player.position = nextPosition;
    player.score += nextPosition + 1;

    return player.score >= 1000;
  }

  std::vector<PlayerState> players_;
  Dice dice_;
};
