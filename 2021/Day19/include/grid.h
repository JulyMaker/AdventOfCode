#ifndef UTIL_DIMENSION_GRID_H_
#define UTIL_DIMENSION_GRID_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));

  return tokens;
}

template <size_t dim>
class DimensionGrid 
{
public:
  DimensionGrid() = delete;

  struct Vec;
  struct Rotation;
  struct MultiRotation;

  struct Point {
    std::array<int64_t, dim> coords = {};

    static Point parseCommaSeparated(const std::string rep) 
    {
      std::vector<std::string> coord_strings = split(rep, ",");
      Point parsed;
      for (size_t d = 0; d < dim; ++d)
      {
        parsed.coords[d]= std::stoi(coord_strings[d]);
      }
      return parsed;
    }

    bool operator==(const Point& other) const { return coords == other.coords; }

    bool operator!=(const Point& other) const { return coords != other.coords; }

    Point& operator+=(const Vec& vec) 
    {
      for (size_t d = 0; d < dim; ++d) 
      {
        this->coords[d] += vec.deltas[d];
      }
      return *this;
    }

    Point operator+(const Vec& vec) const
    {
      Point result(*this);
      result += vec;
      return result;
    }

    Point& operator-=(const Vec& vec) 
    {
      *this += (-vec);
      return *this;
    }

    Point operator-(const Vec& vec) const 
    {
      Point result(*this);
      result -= vec;
      return result;
    }

    friend Vec operator-(const typename DimensionGrid<dim>::Point& a,
      const typename DimensionGrid<dim>::Point& b) {
      typename DimensionGrid<dim>::Vec diff;
      for (size_t d = 0; d < dim; ++d) 
      {
        diff.deltas[d] = a.coords[d] - b.coords[d];
      }
      return diff;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) 
    {
      os << "(";
      for (size_t d = 0; d < dim; ++d) {
        os << p.coords[d];
        if (d != dim - 1) os << ", ";
      }
      os << ")";
      return os;
    }

    std::vector<Point> adjacentCardinal() const 
    {
      return *this + DimensionGrid<dim>::Vecs::Cardinal();
    }

    std::vector<Point> adjacentWithDiagonal() const 
    {
      return *this + DimensionGrid<dim>::Vecs::CardinalAndDiagonal();
    }

    template <typename H>
    friend H hashValue(H h, const Point& point) 
    {
      return H::combine(std::move(h), point.coords);
    }
  };

  class Points 
  {
  public:
    Points() = delete;

    inline static constexpr Point kOrigin{};
  };

  struct Vec 
  {
    std::array<int64_t, dim> deltas = {};

    bool operator==(const Vec& other) const { return deltas == other.deltas; }

    bool operator!=(const Vec& other) const { return deltas != other.deltas; }
    
    Vec operator-() const 
    {
      Vec negated(*this);
      for (int64_t& delta : negated.deltas) 
      {
        delta = -delta;
      }
      return negated;
    }

    Vec& operator+=(const Vec& other) 
    {
      for (size_t d = 0; d < dim; ++d) 
      {
        deltas[d] += other.deltas[d];
      }
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
      *this += (-other);
      return *this;
    }

    Vec operator-(const Vec& other) const 
    {
      Vec result(*this);
      result -= other;
      return result;
    }

    Vec& operator*=(const Rotation& rot) 
    {
      *this = Rotate90(rot.about_axis, rot.turns_90);
      return *this;
    }

    Vec operator*(const Rotation& rot) const 
    {
      return Rotate90(rot.about_axis, rot.turns_90);
    }

    Vec& operator*=(const MultiRotation& multi_rot) 
    {
      for (const Rotation& rot : multi_rot.rotations) 
      {
        *this = Rotate90(rot.about_axis, rot.turns_90);
      }
      return *this;
    }

    Vec operator*(const MultiRotation& multi_rot) const 
    {
      Vec result(*this);
      result *= multi_rot;
      return result;
    }

    // Scaling.
    Vec& operator*=(const int64_t factor) 
    {
      for (int64_t d : deltas) 
      {
        d *= factor;
      }
      return *this;
    }

    Vec operator*(const int64_t factor) const 
    {
      Vec result(*this);
      result *= factor;
      return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec& v) 
    {
      os << "Vec{";
      for (size_t d = 0; d < dim; ++d) {
        os << v.deltas[d];
        if (d != dim - 1) os << ", ";
      }
      os << "}";
      return os;
    }

    Vec Rotate90(size_t about_axis, int turns) const 
    {
      // Only implemented in 3D for now.
      Vec rotated(*this);
      turns %= 4;
      int64_t& first_dim = rotated.deltas[about_axis == 0 ? 1 : 0];
      int64_t& second_dim = rotated.deltas[about_axis == 2 ? 1 : 2];

      for (int t = 0; t < turns; ++t) 
      {
        const int64_t tmp = first_dim;
        first_dim = second_dim;
        second_dim = -tmp;
      }
      return rotated;
    }

    int64_t ManhattanDistance() const 
    {
      return std::accumulate(deltas.begin(), deltas.end(), int64_t{ 0 },
        [](int64_t sum, int64_t val) { return sum + std::abs(val); });
    }

    double Magnitude() const 
    {
      double sum_of_squares = 0.0;
      for (const int64_t d : deltas) 
      {
        sum_of_squares += d * d;
      }
      return std::sqrt(sum_of_squares);
    }

    bool Cardinal() const 
    {
      return std::count_if(deltas.begin(), deltas.end(),
        [](int64_t d) { return d != 0; }) == 1;
    }

    bool CardinalOrDiagonal() const 
    {
      auto iter = std::find_if(deltas.begin(), deltas.end(),
        [](int64_t d) { return d != 0; });
      if (iter == deltas.end()) return false;
      const int64_t mag = std::abs(*iter);
      return std::all_of(deltas.begin(), deltas.end(), [mag](int64_t d) {
        return d == 0 || std::abs(d) == mag;
        });
    }

    Vec UnitStep() const 
    {
      Vec step;
      for (size_t d = 0; d < dim; ++d) {
        if (deltas[d] < 0) {
          step.deltas[d] = -1;
        }
        else if (deltas[d] == 0) {
          step.deltas[d] = 0;
        }
        else {
          step.deltas[d] = 1;
        }
      }
      return step;
    }

    template <typename H>
    friend H hashValue(H h, const Vec& vec) 
    {
      return H::combine(std::move(h), vec.deltas);
    }
  };

  // Scaling Vec with scale factor first.
  friend Vec operator*(const int64_t factor, Vec& vec) { return vec * factor; }

  class Vecs 
  {
  public:
    Vecs() = delete;

    static std::vector<Vec> Cardinal() 
    {
      std::vector<Vec> cardinal;
      for (size_t d = 0; d < dim; ++d) 
      {
        Vec minus, plus;
        minus.deltas[d] = -1;
        plus.deltas[d] = 1;
        cardinal.emplace_back(std::move(minus));
        cardinal.emplace_back(std::move(plus));
      }
      return cardinal;
    }

    static std::vector<Vec> CardinalAndDiagonal() 
    {
      std::vector<Vec> result(1);
      for (size_t d = 0; d < dim; ++d) 
      {
        std::vector<Vec> expanded_result;
        for (const Vec& v : result) 
        {
          Vec minus(v);
          minus.deltas[d] = -1;
          expanded_result.emplace_back(std::move(minus));

          Vec plus(v);
          plus.deltas[d] = 1;
          expanded_result.emplace_back(std::move(plus));

          if (d == dim - 1 && v.ManhattanDistance() == 0) continue;
          expanded_result.emplace_back(v);
        }
        result = std::move(expanded_result);
      }
      return result;
    }
  };

  struct Rotation 
  {
    size_t about_axis = 0;
    int turns_90 = 0;
  };

  struct MultiRotation 
  {
    std::vector<Rotation> rotations;
  };

  class Rotations 
  {
  public:
    Rotations() = delete;

    static std::vector<MultiRotation> AllOrientations() 
    {
      // Only 3D is currently supported.
      std::vector<MultiRotation> orientations;
      for (int z_turns = 0; z_turns < 4; ++z_turns) 
      {
        Rotation z_rot{ .about_axis = 2, .turns_90 = z_turns };
        for (int x_turns = 0; x_turns < 4; ++x_turns) 
        {
          orientations.emplace_back(MultiRotation{ { z_rot, Rotation{.about_axis = 0, .turns_90 = x_turns}} });
        }
      }

      for (int y_turns : {1, 3}) 
      {
        Rotation y_rot{ .about_axis = 1, .turns_90 = y_turns };
        for (int x_turns = 0; x_turns < 4; ++x_turns) 
        {
          orientations.emplace_back(MultiRotation{ { y_rot, Rotation{.about_axis = 0, .turns_90 = x_turns}} });
        }
      }

      return orientations;
    }
  };

  // Arithmetic between Points and Vecs.
  template <typename VecContainer>
  std::enable_if_t<std::is_same_v<Vec, typename VecContainer::value_type>,
    std::vector<Point>> friend
    operator+(const Point& p, const VecContainer& vecs)
  {
    std::vector<Point> result;
    for (const Vec& v : vecs) 
    {
      result.emplace_back(p + v);
    }
    return result;
  }

  // Arithmetic between Vecs and Rotations.
  template <typename VecContainer>
  friend std::enable_if_t<
    std::is_same_v<Vec, typename VecContainer::value_type>, std::vector<Vec>>
    operator*(const VecContainer& vecs, const Rotation& rot) 
  {
    std::vector<Vec> result;
    for (const Vec& v : vecs) 
    {
      result.emplace_back(v * rot);
    }
    return result;
  }

  template <typename VecContainer>
  friend std::enable_if_t<
    std::is_same_v<Vec, typename VecContainer::value_type>, std::vector<Vec>>
    operator*(const VecContainer& vecs, const MultiRotation& multi_rot) 
  {
    std::vector<Vec> result;
    for (const Vec& v : vecs) 
    {
      result.emplace_back(v * multi_rot);
    }
    return result;
  }

  // Arithmetic between Points and Hyperplanes.

  // Returns the shortest vector from `h` to `p`, which is also guaranteed to be
  // normal to `h`.
  template <typename PointContainer>
  static Point MinDimensions(const PointContainer& container) 
  {
    Point min;
    std::fill(min.coords.begin(), min.coords.end(), std::numeric_limits<int64_t>::max());
    for (const Point& point : container) 
    {
      for (size_t d = 0; d < dim; ++d) 
      {
        min.coords[d] = std::min(min.coords[d], point.coords[d]);
      }
    }
    return min;
  }

  template <typename PointContainer>
  static Point MaxDimensions(const PointContainer& container) 
  {
    Point max;
    std::fill(max.coords.begin(), max.coords.end(), std::numeric_limits<int64_t>::min());
    for (const Point& point : container) 
    {
      for (size_t d = 0; d < dim; ++d) {
        max.coords[d] = std::max(max.coords[d], point.coords[d]);
      }
    }
    return max;
  }
};

#endif  // UTIL_DIMENSION_GRID_H_