#include <point.h>
#include <actor.h>
#include <ostream>
#include <iterator>

class Battle
{
  uint32_t width, height;
  char* map;
  std::vector<Actor> actors;
  int ndeadelves;

  void sortActors();
  void clean_up_the_dead();

public:
  Battle(const std::vector<std::string>& input, int elfpower);
  ~Battle()
  {
    delete[] map;
  }

  bool tick();

  char getTile(const Point& p) const
  {
    return getTile(p.x, p.y);
  }

  char getTile(uint32_t x, uint32_t y) const
  {
    if (x >= width || y >= height)
      return '#';

    return map[x + y * width];
  }

  void setTile(const Point& p, char c)
  {
    setTile(p.x, p.y, c);
  }

  void setTile(uint32_t x, uint32_t y, char c)
  {
    if (x >= width || y >= height)
      return;

    map[x + y * width] = c;
  }

  void clearTile(const Point& p)
  {
    if (p.x >= width || p.y >= height)
      return;

    map[p.x + p.y * width] = '.';
  }

  int getScore() const
  {
    int score = 0;
    for (auto& actor : actors)
    {
      if (actor.isAlive())
        score += actor.gethp();
    }
    return score;
  }

  bool gameOver() const;
  bool deadElves() const { return ndeadelves > 0; }

  friend std::ostream& operator<<(std::ostream& os, const Battle& battle);
  friend class Actor;
  friend class Dijkstra;
};

class theyre_all_dead_sir : public std::exception
{

};

