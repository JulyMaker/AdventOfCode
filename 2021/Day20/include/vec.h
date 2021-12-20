
// Two-dimensional vector. Can represent the difference between Points, and can
// be added to a Point to yield another point.
struct Vec 
{
  int64_t dx = 0;
  int64_t dy = 0;

  bool operator==(const Vec& other) const 
  {
    return dx == other.dx && dy == other.dy;
  }

  bool operator!=(const Vec& other) const 
  {
    return dx != other.dx || dy != other.dy;
  }

  Vec operator-() const { return Vec{ .dx = -dx, .dy = -dy }; }

  Vec& operator+=(const Vec& other) 
  {
    dx += other.dx;
    dy += other.dy;
    return *this;
  }

  Vec operator+(const Vec& other) const 
  {
    Vec result(*this);
    result += other;
    return result;
  }

  Vec& operator-=(const Vec& other) 
  {
    dx -= other.dx;
    dy -= other.dy;
    return *this;
  }

  Vec operator-(const Vec& other) const 
  {
    Vec result(*this);
    result -= other;
    return result;
  }

  // Scaling
  Vec& operator*=(const int64_t factor) 
  {
    dx *= factor;
    dy *= factor;
    return *this;
  }

  Vec operator*(const int64_t factor) const 
  {
    Vec result(*this);
    result *= factor;
    return result;
  }

  Vec Rotate90(int turns) const 
  {
    Vec rotated(*this);
    turns %= 4;
    for (int t = 0; t < turns; ++t) {
      const int64_t tmp = dx;
      rotated.dx = dy;
      rotated.dy = -tmp;
    }
    return rotated;
  }

  std::array<Vec, 4> AllRotations90() const 
  {
    return { Rotate90(0), Rotate90(1), Rotate90(2), Rotate90(3) };
  }

  int64_t ManhattanDistance() const { return std::abs(dx) + std::abs(dy); }

  double Magnitude() const { return std::sqrt(dx * dx + dy * dy); }

  bool Horizontal() const { return dy == 0; }

  bool Vertical() const { return dx == 0; }

  bool Diag45() const { return std::abs(dx) == std::abs(dy); }

  template <typename H>
  friend H AbslHashValue(H h, const Vec& vec) {
    return H::combine(std::move(h), vec.dx, vec.dy);
  }
};