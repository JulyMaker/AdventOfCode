#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <array>
#include <mutex>
#include <numeric>
#include <intrin.h>
#include <tuple>
#include <iomanip>
#include <cctype> 
#include <random>
#include <valarray>
#include <thread>
#include <unordered_set>
#include <optional>
#include <deque>
#include <queue>
#include <pixie.h>

int screenw = 1200;
int screenh = 800;

Pixie::Window window;

struct Span
{
  uint32_t minx, maxx;    // ranges are inclusive
  uint32_t miny, maxy;

  Span() = default;
  Span(uint32_t minx, uint32_t maxx, uint32_t miny, uint32_t maxy)
    : minx(minx), maxx(maxx), miny(miny), maxy(maxy)
  {/**/
  }

  Span(const std::string& line)
  {
    // y=7, x=495..501
    std::istringstream is(line);
    char dummy;
    if (line[0] == 'x')
    {
      is.ignore(1000, '=');
      is >> maxx;
      minx = maxx;

      is.ignore(1000, '=');
      is >> miny >> dummy >> dummy >> maxy;
    }
    else
    {
      is.ignore(1000, '=');
      is >> maxy;
      miny = maxy;

      is.ignore(1000, '=');
      is >> minx >> dummy >> dummy >> maxx;
    }
  }
};

inline void fill(char* map, uint32_t xoff, uint32_t yoff, uint32_t width, const Span& clay)
{
  Span local = clay;
  local.minx -= xoff;
  local.maxx -= xoff;
  local.miny -= yoff;
  local.maxy -= yoff;

  for (uint32_t y = local.miny; y <= local.maxy; ++y)
  {
    char* prow = map + y * width;
    memset(prow + local.minx, '#', 1 + local.maxx - local.minx);
  }
}

std::vector<std::string> parseLines(std::ifstream& input)
{
  std::vector<std::string> lines;

  for (std::string line; getline(input, line);)
  {
    if (line != "")
      lines.push_back(line);
  }

  return lines;
}

int64_t adventDay17problem12018(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseLines(input);
  // load the data
  std::vector<Span> clays;
  clays.reserve(inputLines.size());
  Span space(~0u, 0, ~0u, 0);
  for (auto& line : inputLines)
  {
    clays.emplace_back(line);

    auto& s = clays.back();
    space.minx = min(space.minx, s.minx);
    space.maxx = max(space.maxx, s.maxx);
    space.miny = min(space.miny, s.miny);
    space.maxy = max(space.maxy, s.maxy);
  }

  // embiggen our space to catch edge drips
  space.minx--;
  space.maxx++;

  // set up our space
  uint32_t width = 1 + space.maxx - space.minx;
  uint32_t height = 1 + space.maxy - space.miny;
  char* map = new char[width * height];
  memset(map, '.', width * height);

  screenw = width;
  screenh = height;
  if (!window.Open(L"day17 guest appearance in a window!", screenw, screenh, false))
    exit(1);

  uint32_t xoff = space.minx;
  uint32_t yoff = space.miny;

  // fill in the clay
  for (auto& clay : clays)
  {
    fill(map, xoff, yoff, width, clay);
  }

  // wet the sand beneath the spring
  map[500 - xoff] = '|';
  bool wetted;
  int nwetted = 1;
  bool printed = false;
  do {
    wetted = false;

    // go from the bottom up, omitting the top line
    // FIXME: would be a lot quicker if we just remembered the 3-4 lines that could possibly need updating...
    for (uint32_t ly = height - 1; ly > 0; --ly)
    {
      // propagate each spot of moisture in the previous row
      auto abovebegin = map + ((ly - 1) * width);
      auto aboveend = abovebegin + width;
      for (auto prev = abovebegin; prev != aboveend; ++prev)
      {
        char prevc = *prev;
        if (prevc == '|')
        {
          // propagate l&r as long as there's clay or water below
          if (ly != height - 1)
          {
            auto currbegin = aboveend;
            auto currend = currbegin + width;

            // wind to the left
            int nwound = 0;
            auto curr = prev + width;
            while (curr != currbegin)
            {
              auto below = curr + width;
              if ((*below == '#' || *below == '~') &&
                (*(curr - 1) != '#'))
              {
                --curr;
                nwound++;
              }
              else
              {
                break;
              }
            }

            // fill to the right as long as we can
            while (curr != currend)
            {
              if (*curr == '.')
              {
                *curr = '|';
                wetted = true;
                ++nwetted;
              }

              auto below = curr + width;
              if ((nwound <= 0) &&       // deal with flows off to the left
                ((*below != '#' && *below != '~') ||
                  (*(curr + 1) == '#')))
              {
                break;
              }
              else
              {
                ++curr;
                --nwound;
              }
            }
          }
          else
          {
            auto pcurr = prev + width;
            if (*pcurr != '|')
            {
              *pcurr = '|';
              wetted = true;
              ++nwetted;
            }
          }
        }
      }
    }

    // now the water's got everywhere by flowing, find where it's settled

    // go from the bottom up, omitting the top & bottom lines
    // FIXME: again, this only needs to happen on rows we just added water to
    for (uint32_t ly = height - 2; ly > 0; --ly)
    {
      auto currbegin = map + (ly * width);
      auto currend = currbegin + width;

      auto curr = currbegin;
      while (curr != currend)
      {
        // skip to the next clay
        curr = std::find(curr, currend, '#');
        if (curr == currend || (curr + 1 == currend))
          break;

        ++curr;

        if (*curr == '|')
        {
          // find the span of contained water
          auto start = curr;
          bool contained = true;
          while (*curr == '|')
          {
            auto below = curr + width;
            if (*below != '#' && *below != '~')
            {
              contained = false;
              break;
            }
            ++curr;
          }
          if (*curr == '#' && contained)
          {
            std::fill(start, curr, '~');
          }
        }
      }
    }

    // render
    uint32_t* pixbuf = window.GetPixels();
    char* curr = map;
    while (curr != map + (width * height))
    {
      char c = *curr;
      if (c == '.')
        *pixbuf = 0xbb8844;
      else if (c == '|')
        *pixbuf = 0xbbddff;
      else if (c == '~')
        *pixbuf = 0x5588ff;
      else
        *pixbuf = 0x886600;

      ++curr;
      ++pixbuf;
    }

    if (!window.Update())
      break;

    if (!wetted && !printed)
    {
      std::cout << " Result: " << nwetted << " " << std::endl;
      std::cout << "\n\n Aquifers = " << std::count(map, map + width * height, '~') << std::endl;

      std::ofstream ofs("../../Day17/output.txt");
      for (uint32_t y = 0; y < height; ++y)
      {
        ofs.write(map + y * width, width);
        ofs << '\n';
      }

      printed = true;
    }

  } while (!window.IsKeyDown(Pixie::Key::Key_Escape));

  delete[] map;
  return nwetted;
}

int64_t adventDay17problem22018(std::ifstream& input)
{
  std::vector<std::string> inputLines = parseLines(input);
  // load the data
  std::vector<Span> clays;
  clays.reserve(inputLines.size());
  Span space(~0u, 0, ~0u, 0);
  for (auto& line : inputLines)
  {
    clays.emplace_back(line);

    auto& s = clays.back();
    space.minx = min(space.minx, s.minx);
    space.maxx = max(space.maxx, s.maxx);
    space.miny = min(space.miny, s.miny);
    space.maxy = max(space.maxy, s.maxy);
  }

  // embiggen our space to catch edge drips
  space.minx--;
  space.maxx++;

  // set up our space
  uint32_t width = 1 + space.maxx - space.minx;
  uint32_t height = 1 + space.maxy - space.miny;
  char* map = new char[width * height];
  memset(map, '.', width * height);

  screenw = width;
  screenh = height;
  if (!window.Open(L"day17 guest appearance in a window!", screenw, screenh, false))
    exit(1);

  uint32_t xoff = space.minx;
  uint32_t yoff = space.miny;

  // fill in the clay
  for (auto& clay : clays)
  {
    fill(map, xoff, yoff, width, clay);
  }

  // wet the sand beneath the spring
  map[500 - xoff] = '|';
  bool wetted;
  int nwetted = 1;
  bool printed = false;
  do {
    wetted = false;

    // go from the bottom up, omitting the top line
    // FIXME: would be a lot quicker if we just remembered the 3-4 lines that could possibly need updating...
    for (uint32_t ly = height - 1; ly > 0; --ly)
    {
      // propagate each spot of moisture in the previous row
      auto abovebegin = map + ((ly - 1) * width);
      auto aboveend = abovebegin + width;
      for (auto prev = abovebegin; prev != aboveend; ++prev)
      {
        char prevc = *prev;
        if (prevc == '|')
        {
          // propagate l&r as long as there's clay or water below
          if (ly != height - 1)
          {
            auto currbegin = aboveend;
            auto currend = currbegin + width;

            // wind to the left
            int nwound = 0;
            auto curr = prev + width;
            while (curr != currbegin)
            {
              auto below = curr + width;
              if ((*below == '#' || *below == '~') &&
                (*(curr - 1) != '#'))
              {
                --curr;
                nwound++;
              }
              else
              {
                break;
              }
            }

            // fill to the right as long as we can
            while (curr != currend)
            {
              if (*curr == '.')
              {
                *curr = '|';
                wetted = true;
                ++nwetted;
              }

              auto below = curr + width;
              if ((nwound <= 0) &&       // deal with flows off to the left
                ((*below != '#' && *below != '~') ||
                  (*(curr + 1) == '#')))
              {
                break;
              }
              else
              {
                ++curr;
                --nwound;
              }
            }
          }
          else
          {
            auto pcurr = prev + width;
            if (*pcurr != '|')
            {
              *pcurr = '|';
              wetted = true;
              ++nwetted;
            }
          }
        }
      }
    }

    // now the water's got everywhere by flowing, find where it's settled

    // go from the bottom up, omitting the top & bottom lines
    // FIXME: again, this only needs to happen on rows we just added water to
    for (uint32_t ly = height - 2; ly > 0; --ly)
    {
      auto currbegin = map + (ly * width);
      auto currend = currbegin + width;

      auto curr = currbegin;
      while (curr != currend)
      {
        // skip to the next clay
        curr = std::find(curr, currend, '#');
        if (curr == currend || (curr + 1 == currend))
          break;

        ++curr;

        if (*curr == '|')
        {
          // find the span of contained water
          auto start = curr;
          bool contained = true;
          while (*curr == '|')
          {
            auto below = curr + width;
            if (*below != '#' && *below != '~')
            {
              contained = false;
              break;
            }
            ++curr;
          }
          if (*curr == '#' && contained)
          {
            std::fill(start, curr, '~');
          }
        }
      }
    }

    // render
    uint32_t* pixbuf = window.GetPixels();
    char* curr = map;
    while (curr != map + (width * height))
    {
      char c = *curr;
      if (c == '.')
        *pixbuf = 0xbb8844;
      else if (c == '|')
        *pixbuf = 0xbbddff;
      else if (c == '~')
        *pixbuf = 0x5588ff;
      else
        *pixbuf = 0x886600;

      ++curr;
      ++pixbuf;
    }

    if (!window.Update())
      break;

    if (!wetted && !printed)
    {
      std::cout << " Result: " << nwetted << " " << std::endl;
      std::cout << "\n\n Aquifers = " << std::count(map, map + width * height, '~') << std::endl;

      std::ofstream ofs("../../Day17/output.txt");
      for (uint32_t y = 0; y < height; ++y)
      {
        ofs.write(map + y * width, width);
        ofs << '\n';
      }

      printed = true;
    }

  } while (!window.IsKeyDown(Pixie::Key::Key_Escape));

  delete[] map;

  return std::count(map, map + width * height, '~');
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay17problem12018(infile)
                                        : adventDay17problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day17/input17.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return -1;
  }


  long long int result = 0;
  switch (problem)
  {
  case 1:
    result = readFile(fileName, problem);
    break;
  case 2:
    result = readFile(fileName, problem);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}