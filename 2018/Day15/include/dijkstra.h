#include <battle.h>
#include <algorithm>

class Dijkstra
{
  const Battle& battle;
  uint32_t width;
  uint32_t height;
  Point from;
  Point to;

  // top bit = unvisited, bottom 15 = distance
  uint16_t* cost;

  std::vector<Point> open;

  void visit(const Point& p);

  bool isVisited(const Point& p) const
  {
    if (p.x >= width || p.y >= height)
      return true;

    return (cost[p.x + p.y * width] & 0x8000) == 0;
  }

  bool isTraversable(const Point& p) const
  {
    return battle.map[p.x + p.y * width] == '.';
  }

  uint32_t getTcost(const Point& p) const
  {
    if (p.x >= width || p.y >= height)
      return 0x7fff;

    return cost[p.x + p.y * width] & 0x7fff;
  }

  void setTcost(const Point& p, uint16_t newtcost)
  {
    if (p.x >= width || p.y >= height)
      return;

    auto tcost = cost[p.x + p.y * width];
    cost[p.x + p.y * width] = newtcost | (tcost & 0x8000);
  }

  void markTcost(const Point& p, uint16_t neighbortcost)
  {
    if (p.x >= width || p.y >= height)
      return;

    auto oldtcost = cost[p.x + p.y * width];
    auto tcost = std::min(oldtcost, (uint16_t)(neighbortcost + 1));
    cost[p.x + p.y * width] = tcost | (oldtcost & 0x8000);
  }

  void visitNeighbour(const Point& p, uint16_t tcost)
  {
    if (!isVisited(p) && isTraversable(p))
    {
      markTcost(p, tcost);

      if (find(open.begin(), open.end(), p) == open.end())
        open.push_back(p);
    }
  }

  void buildpath(Path& outpath) const;

public:

  Dijkstra(const Battle& battle, const Point& from, const Point& to)
    : battle(battle)
    , from(from)
    , to(to)
  {
    width = battle.width;
    height = battle.height;
    cost = new uint16_t[width * height];
    std::fill(cost, cost + width * height, 0xffff);
    cost[from.x + from.y * width] = 0;

    open.reserve(50);
  }
  ~Dijkstra()
  {
    delete[] cost;
  }

  bool go(Path& outpath);
};