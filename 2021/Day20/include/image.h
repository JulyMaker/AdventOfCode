#include <vector>
#include <string>
#include <unordered_set>
#include <point.h>

class Image 
{
public:
  Image() = default;

  explicit Image(const std::vector<std::string>& rep) 
  {
    for (int64_t y = 0; y < rep.size(); ++y) 
    {
      for (int64_t x = 0; x < rep[y].size(); ++x) 
      {
        switch (rep[y][x]) 
        {
          case '#':
            bright_pixels_.emplace(Point{ x, y });
            break;
          case '.':
            break;
        }
      }
    }
  }

  Image applyProgram(const std::vector<bool>& program) const 
  {
    Image result;
    if (!inverted_ && program.front()) 
    {
      result.inverted_ = true;
    }
    else if (inverted_ && !program.back()) 
    {
      result.inverted_ = false;
    }

    Point min = MinDimensions(bright_pixels_) - Vec{ .dx = 1, .dy = 1 };
    Point max = MaxDimensions(bright_pixels_) + Vec{ .dx = 1, .dy = 1 };

    for (int64_t y = min.y; y <= max.y; ++y) 
    {
      for (int64_t x = min.x; x <= max.x; ++x) 
      {
        const bool bright = program[valueForPixel(Point{ x, y })];
        if (bright ^ result.inverted_) 
        {
          result.bright_pixels_.emplace(Point{ x, y });
        }
      }
    }
    return result;
  }

  int64_t pixelsLit() const 
  {
    return bright_pixels_.size();
  }

private:
  int valueForPixel(Point p) const 
  {
    int value = 0;
    for (int64_t y : {-1, 0, 1}) 
    {
      for (int64_t x : {-1, 0, 1}) 
      {
        value = (value << 1) | bright_pixels_.contains(p + Vec{ x, y });
      }
    }

    if (inverted_) 
      value = ~value & 511;

    return value;
  }

  std::unordered_set<Point, pointHash> bright_pixels_;
  bool inverted_ = false;
};