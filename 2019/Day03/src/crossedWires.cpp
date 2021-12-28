#include <utils.h>

struct Point 
{ 
  int x = 0; int y = 0; 

  bool operator==(const Point& p2) { return x == p2.x && y == p2.y; }
  bool operator!=(const Point& p2) { return !(*this == p2); }
};

// Segments are horizontal or vertical segments between two points.
// To ease intersection checks, ordered intervals of x and y coordinates are precomputed.
struct Segment 
{
  Segment(const Point& a, const Point& b) 
  {
    p1 = a;
    p2 = b;
    xMin = std::min(p1.x, p2.x);
    xMax = std::max(p1.x, p2.x);
    yMin = std::min(p1.y, p2.y);
    yMax = std::max(p1.y, p2.y);
  }

  Point p1;
  Point p2;
  int xMin; int xMax; int yMin; int yMax;
};

int manhattanDist(const Point& a, const Point& b)
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// Check if two segments intersect. Returns true if segments intersect. If they
// do, intersection will be modified with the intersection if non-null.
bool intersects(const Segment& s1, const Segment& s2, Point* intersection) 
{
  if ((s1.xMin >= s2.xMin && s1.xMin <= s2.xMax) && (s2.yMin >= s1.yMin && s2.yMin <= s1.yMax)) 
  {
    if (intersection) 
    {
      intersection->x = s1.xMin;
      intersection->y = s2.yMin;
    }
    return true;
  }
  else if ((s2.xMin >= s1.xMin && s2.xMin <= s1.xMax) && (s1.yMin >= s2.yMin && s1.yMin <= s2.yMax)) 
  {
    if (intersection) 
    {
      intersection->x = s2.xMin;
      intersection->y = s1.yMin;
    }
    return true;
  }
  return false;
};

using Segments = std::vector<Segment>;

std::vector<Segments> parseWires(std::ifstream& input)
{
  std::vector<Segments> segs;
  Segments seg;

  for (std::string line; std::getline(input, line);)
  {
    Point p{ 0, 0 };
    Point prev = p;
    std::vector<std::string> wires = splitS(line, ",");

    for (auto& w : wires)
    {
      char direction = w[0];
      int n = std::stoi(w.substr(1));

      switch (direction)
      {
        case 'L': p.x -= n; break;
        case 'R': p.x += n; break;
        case 'U': p.y += n; break;
        case 'D': p.y -= n; break;
      }

      seg.emplace_back(prev, p);
      prev = p;
    }

    segs.push_back(seg);
    seg.clear();
  }
 
  return segs;
}

uint64_t adventDay03problem12019(std::ifstream& input)
{
  std::vector<Segments> wires = parseWires(input);
  std::vector<Segment> wireOne = wires[0];
  std::vector<Segment> wireTwo = wires[1];

  const Point ORIGIN{ 0, 0 };

  int minDist = std::numeric_limits<int>::max();
  Point intersection;

  for (const auto& i : wireOne) 
    for (const auto& j : wireTwo) 
      if (intersects(i, j, &intersection) && intersection != ORIGIN) 
        minDist = std::min(minDist, manhattanDist(intersection, ORIGIN));
  
  return minDist;
}

uint64_t adventDay03problem22019(std::ifstream& input)
{
  std::vector<Segments> wires = parseWires(input);
  std::vector<Segment> wireOne = wires[0];
  std::vector<Segment> wireTwo = wires[1];

  const Point ORIGIN{ 0, 0 };
  int minDelay = std::numeric_limits<int>::max();

  Point intersection;

  int oneDist = 0;
  for (const auto& i : wireOne) 
  {
    int twoDist = 0;
    for (const auto& j : wireTwo) 
    {
      if (intersects(i, j, &intersection) && intersection != ORIGIN) 
      {
        minDelay = std::min(minDelay, (oneDist + twoDist + manhattanDist(intersection, i.p1) + manhattanDist(intersection, j.p1)));
      }
      twoDist += manhattanDist(j.p1, j.p2);
    }
    oneDist += manhattanDist(i.p1, i.p2);
  }

  return minDelay;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "03";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay03problem12019(inputFile); break;
    case 2: result = adventDay03problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}