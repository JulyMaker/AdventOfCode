#include <dijkstra.h>

void Actor::addopen(std::vector<Point>& open, uint8_t x, uint8_t y, const Battle& battle)
{
  // FIXME?: all these finds would be faster if open was sorted...
  for (int xoffs = -1; xoffs <= 1; xoffs += 2)
  {
    Point p(x + xoffs, y);
    if (battle.getTile(p.x, p.y) == '.')
    {
      if (find(open.begin(), open.end(), p) == open.end())
        open.push_back(p);
    }
  }

  for (int yoffs = -1; yoffs <= 1; yoffs += 2)
  {
    Point p(x, y + yoffs);
    if (battle.getTile(p.x, p.y) == '.')
    {
      if (find(open.begin(), open.end(), p) == open.end())
        open.push_back(p);
    }
  }
}

bool Actor::trypathfind(const Point& dest, const Battle& battle, Path& outpath) const
{
  Dijkstra dijkstra(battle, pos, dest);
  return dijkstra.go(outpath);
}


bool Actor::canAttack(const Battle& battle) const
{
  if (hp <= 0)
    return false;

  char enemyrace = (race == 'E') ? 'G' : 'E';
  if ((battle.getTile(pos.up()) == enemyrace) ||
      (battle.getTile(pos.left()) == enemyrace) ||
      (battle.getTile(pos.right()) == enemyrace) ||
      (battle.getTile(pos.down()) == enemyrace))
    return true;

  return false;
}

void Actor::move(Battle& battle)
{
  // step 1: find all non-wall spaces within one space of the enemy
  std::vector<Point> inrange;
  inrange.reserve(battle.actors.size() * 4);
  bool enemies = false;
  for (auto& them : battle.actors)
  {
    if (them.race == race)
      continue;
    if (!them.isAlive())
      continue;

    enemies = true;
    addopen(inrange, them.pos.x, them.pos.y, battle);
  }

  if (!enemies)
    throw theyre_all_dead_sir();

  sort(inrange.begin(), inrange.end());

  // step 2: pathfind to each
  std::vector<Path> paths;
  for (auto& dest : inrange)
  {
    Path path;
    if (trypathfind(dest, battle, path))
    {
      paths.push_back(path);
    }
  }

  // if we have nowhere to go, just stop here
  if (paths.empty())
    return;

  // step 3: discard all but the shortest path(s)
  auto itshortest = min_element(paths.begin(), paths.end(), [](const Path& a, const Path& b)->bool {
    return a.steps.size() < b.steps.size();
    });
  paths.erase(remove_if(paths.begin(), paths.end(), [&](const Path& p)->bool {
    return p.steps.size() > itshortest->steps.size();
    }), paths.end());

  // step 4: choose the remaining destination first in reading order
  auto itchoice = min_element(paths.begin(), paths.end(), [](const Path& a, const Path& b)->bool {
    return a.to < b.to;
    });

  // step 5: MOVE!
  battle.clearTile(pos);
  pos = itchoice->steps.front();
  battle.setTile(pos, race);
}


void Actor::attack(Battle& battle)
{
  // step 1: find all living enemies within range
  std::vector<Actor*> attackable;
  bool enemies = false;
  for (auto& other : battle.actors)
  {
    if (other.race == race)
      continue;
    if (other.hp <= 0)
      continue;

    enemies = true;

    if (other.pos.x == pos.x)
    {
      if (pos.y - 1 == other.pos.y || pos.y + 1 == other.pos.y)
        attackable.push_back(&other);
    }
    else if (other.pos.y == pos.y)
    {
      if (pos.x - 1 == other.pos.x || pos.x + 1 == other.pos.x)
        attackable.push_back(&other);
    }
  }

  if (!enemies)
    throw theyre_all_dead_sir();
  if (attackable.empty())
    return;

  // step 2: choose one with lowest hp
  auto itdeadest = min_element(attackable.begin(), attackable.end(), [](const Actor* a, const Actor* b)->bool {
    return a->hp < b->hp;
    });
  attackable.erase(remove_if(attackable.begin(), attackable.end(), [&](const Actor* a)->bool {
    return a->hp > (*itdeadest)->hp;
    }), attackable.end());

  // step 3: break any stalemate using reading order
  sort(attackable.begin(), attackable.end(), [](const Actor* a, const Actor* b)->bool {
    return *a < *b;
    });

  Actor* ptarget = attackable.front();
  _ASSERT(ptarget->hp > 0);
  _ASSERT(ptarget->race != race);
  ptarget->hp -= ap;
  if (!ptarget->isAlive())
  {
    battle.clearTile(ptarget->pos);

    if (this != &battle.actors.back() && battle.gameOver())
      throw theyre_all_dead_sir();
  }
}