#include <dijkstra.h>

void Dijkstra::visit(const Point& p)
{
  auto tcost = getTcost(p);

  visitNeighbour(p.up(), tcost);
  visitNeighbour(p.left(), tcost);
  visitNeighbour(p.right(), tcost);
  visitNeighbour(p.down(), tcost);

  // mark as visited
  cost[p.x + p.y * width] &= 0x7fff;
}

void Dijkstra::buildpath(Path& outpath) const
{
  outpath.to = to;

  // follow path of least tcost back from 'to' to 'from'. <-- lol
  auto nsteps = getTcost(to);
  auto& steps = outpath.steps;
  steps.reserve(nsteps);

  Point curr = to;
  while (curr != from)
  {
    steps.push_back(curr);

    auto next = curr.up();
    auto mintcost = getTcost(next);
    // ugh there must be a better way to express this :/
    if (getTcost(curr.left()) < mintcost)
    {
      next = curr.left();
      mintcost = getTcost(curr.left());
    }

    if (getTcost(curr.right()) < mintcost)
    {
      next = curr.right();
      mintcost = getTcost(curr.right());
    }

    if (getTcost(curr.down()) < mintcost)
    {
      next = curr.down();
      mintcost = getTcost(curr.down());
    }

    curr = next;
  }

  reverse(steps.begin(), steps.end());
}

bool Dijkstra::go(Path& outpath)
{
  // THINKS: open could be sorted list<> of Point,tcost pairs?
  Point curr = from;
  open.push_back(curr);
  while (!open.empty())
  {
    // find open space with minimum tentative cost
    curr = open.front();
    auto mintcost = getTcost(curr);
    for (auto it = open.begin() + 1; it != open.end(); ++it)
    {
      auto tcost = getTcost(*it);
      if (tcost < mintcost)
      {
        curr = *it;
        mintcost = tcost;
      }
    }

    // if it's our destination, then we're done marking costs
    if (curr == to)
    {
      buildpath(outpath);
      return true;
    }

    // visit it!
    visit(curr);
    open.erase(find(open.begin(), open.end(), curr));
  }

  return false;
}
