#include <point.h>

class Battle;

class Actor
{
  Point pos;
  char race;
  int hp;
  int ap;

  static void addopen(std::vector<Point>& open, uint8_t x, uint8_t y, const Battle& battle);

  bool trypathfind(const Point& dest, const Battle& battle, Path& outpath) const;

public:
  Actor() = default;
  Actor(uint8_t x, uint8_t y, char race, int ap) : pos(x, y), race(race), ap(ap)
  {
    hp = 200;
  }

  bool operator<(const Actor& o) const
  {
    return pos < o.pos;
  }

  bool isElf() const { return race == 'E'; }
  bool isAlive() const { return hp > 0; }
  const Point& getPos() const { return pos; }
  int gethp() const { return hp; }

  bool canAttack(const Battle& battle) const;
  void move(Battle& battle);
  void attack(Battle& battle);

  friend std::ostream& operator<<(std::ostream& os, const Battle& battle);
};