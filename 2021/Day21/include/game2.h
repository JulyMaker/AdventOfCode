#include <unordered_map>

struct PlayerState2 
{
  int position = 0;
  int score = 0;

  bool operator==(const PlayerState2& other) const 
  {
    return position == other.position && score == other.score;
  }

  bool win() const { return score >= 21; }

  PlayerState2 move(int spaces) const 
  {
    PlayerState2 next;
    next.position = (position + spaces) % 10;
    next.score = score + next.position + 1;

    return next;
  }

  template <typename H>
  friend H hashValue(H h, const PlayerState2& p)
  {
    return H::combine(std::move(h), p.position, p.score);
  }
};

struct gameHash;

struct GameState2 
{
  PlayerState2 player1;
  PlayerState2 player2;
  bool player2Next = false;

  int totalScore() const { return player1.score + player2.score; }

  bool Win() const { return player1.win() || player2.win(); }

  std::unordered_map<GameState2, int64_t, gameHash> expandUniverses() const;
  
  bool operator==(const GameState2& other) const 
  {
    return player1 == other.player1 && player2 == other.player2 &&
      player2Next == other.player2Next;
  }

  template <typename H>
  friend H hashValue(H h, const GameState2& g) 
  {
    return H::combine(std::move(h), g.player1, g.player2, g.player2_next);
  }
};

struct gameHash
{
  size_t operator()(const const GameState2& g) const
  {
    return std::hash<int>()(((g.player1.position * 39) ^ g.player1.score) + ((g.player2.position * 39) ^ g.player2.score) + g.player2Next);
  }
};

struct GreaterTotalScore 
{
  bool operator()(const GameState2& a, const GameState2& b) const 
  {
    return a.totalScore() > b.totalScore();
  }
};

std::unordered_map<GameState2, int64_t, gameHash> GameState2::expandUniverses() const
{
  std::unordered_map<GameState2, int64_t, gameHash> expanded;
  for (std::pair<int, int> move_universes : { std::make_pair(3, 1), std::make_pair(4, 3), std::make_pair(5, 6), std::make_pair(6, 7),
                                              std::make_pair(7, 6), std::make_pair(8, 3), std::make_pair(9, 1) })
  {
    GameState2 next(*this);
    if (player2Next)
    {
      next.player2 = player2.move(move_universes.first);
      next.player2Next = false;
      expanded.emplace(next, move_universes.second);
    }
    else
    {
      next.player1 = player1.move(move_universes.first);
      next.player2Next = true;
      expanded.emplace(next, move_universes.second);
    }
  }
  return expanded;
}