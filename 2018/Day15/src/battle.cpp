#include <battle.h>

Battle::Battle(const std::vector<std::string>& input, int elfpower) : ndeadelves(0)
{
  height = (uint32_t)input.size();
  width = 0;
  for (auto& line : input)
    width = std::max(width, (uint32_t)line.length());

  map = new char[width * height];
  memset(map, ' ', width * height);

  int y = 0;
  for (auto& line : input)
  {
    char* mapc = map + y * width;
    for (uint32_t x = 0; x < line.length(); ++x, ++mapc)
    {
      char c = line[x];
      *mapc = c;

      if (c == 'G' || c == 'E')
        actors.emplace_back(x, y, c, (c == 'E') ? elfpower : 3);
    }
    ++y;
  }
}

// returns true if one side has won before this round completed
bool Battle::tick()
{
  try
  {
    sortActors();

    for (auto& actor : actors)
    {
      if (!actor.isAlive())
        continue;

      if (!actor.canAttack(*this))
        actor.move(*this);

      if (actor.canAttack(*this))
        actor.attack(*this);
    }

    clean_up_the_dead();
  }
  catch (theyre_all_dead_sir&)
  {
    clean_up_the_dead();
    return true;
  }

  return false;
}

void Battle::sortActors()
{
  sort(actors.begin(), actors.end());
}

void Battle::clean_up_the_dead()
{
  for (const Actor& a : actors)
  {
    if (!a.isAlive() && a.isElf())
      ++ndeadelves;
  }

  actors.erase(remove_if(actors.begin(), actors.end(), [](const Actor& a)->bool {
    return !a.isAlive();
    }), actors.end());
}


bool Battle::gameOver() const
{
  size_t nelves = 0;
  size_t nglobs = 0;
  for (auto& actor : actors)
  {
    if (actor.isAlive())
    {
      if (actor.isElf())
        ++nelves;
      else
        ++nglobs;
    }
  }

  return (nelves == 0) || (nglobs == 0);
}
