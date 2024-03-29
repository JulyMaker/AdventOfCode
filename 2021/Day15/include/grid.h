#include <iterator>

// A dense two - dimensional grid of 'T' values.Cells are addressable as points.
template <typename T = int>
class Grid 
{
public:
  // Iterator implementation.
  template <typename ValueType, typename OuterIt, typename InnerIt>
  class IteratorImpl 
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = ValueType;
    using pointer = ValueType*;
    using reference = ValueType&;

    IteratorImpl() = default;

    reference operator*() const { return *inner_; }
    pointer operator->() const { return &*inner_; }

    IteratorImpl& operator++() 
    {
      if (++inner_ == outer_->end()) 
      {
        if (++outer_ == outer_end_) 
        {
          inner_ = InnerIt();
        }
        else {
          inner_ = outer_->begin();
        }
      }
      return *this;
    }

    IteratorImpl operator++(int) const 
    {
      IteratorImpl tmp = *this;
      ++tmp;
      return tmp;
    }

    bool operator==(const IteratorImpl& other) const 
    {
      return outer_ == other.outer_ && inner_ == other.inner_;
    }

    bool operator!=(const IteratorImpl& other) const 
    {
      return !(*this == other);
    }

  protected:
    OuterIt outer_;
    OuterIt outer_end_;
    InnerIt inner_;

  private:
    friend class Grid<T>;

    explicit IteratorImpl(OuterIt outer, OuterIt outer_end, InnerIt inner)
      : outer_(std::move(outer)),
      outer_end_(std::move(outer_end)),
      inner_(std::move(inner)) {}
  };


  // Iterator over the values held in cells.
  using iterator =
    IteratorImpl<T, typename std::vector<std::vector<T>>::iterator,
    typename std::vector<T>::iterator>;

  // Const-iterator over the values held in cells.
  class const_iterator
    : public IteratorImpl<
    const T, typename std::vector<std::vector<T>>::const_iterator,
    typename std::vector<T>::const_iterator> 
  {
  public:
    const_iterator(const iterator& it) 
    {
      this->outer_ = it.outer_;
      this->outer_end_ = it.outer_end_;
      this->inner_ = it.inner_;
    }
  };

  // Iterator over Point coordinates in the grid.
  class PointIterator 
  {
  public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Point;
    using pointer = const Point*;
    using reference = const Point&;

    PointIterator() = default;

    reference operator*() const { return current_; }
    pointer operator->() const { return &current_; }

    PointIterator& operator++() 
    {
      if (++current_.y == grid_->XSize()) 
      {
        ++current_.x;
        current_.y = 0;
      }
      return *this;
    }

    PointIterator operator++(int) const 
    {
      PointIterator tmp = *this;
      ++tmp;
      return tmp;
    }

    bool operator==(const PointIterator& other) const 
    {
      return current_ == other.current_ && grid_ == other.grid_;
    }

    bool operator!=(const PointIterator& other) const 
    {
      return !(*this == other);
    }

  private:
    friend class Grid;

    explicit PointIterator(Point current, const Grid* grid)
      : current_(current), grid_(grid) {}

    Point current_;
    const Grid* grid_ = nullptr;
  };

  // A view over the Points in range of the Grid.
  class PointView 
  {
  public:
    using iterator = PointIterator;
    using const_iterator = PointIterator;

    const_iterator cbegin() const { return grid_->point_begin(); }

    const_iterator cend() const { return grid_->point_end(); }

    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }

  private:
    friend class Grid;

    explicit PointView(const Grid* grid) : grid_(grid) {}

    const Grid* grid_ = nullptr;
  };

  explicit Grid(const size_t x_dim, const size_t y_dim)
    : values_(x_dim, std::vector<T>(y_dim)) {}

  // Parses a grid from a representation where each cell is an ASCII digit.
  // Technically X and Y are reversed from their intuitive direction in the
  // input, but thus far that hasn't been a problem.
  static Grid readFromDigits(const std::vector<std::string>& input) 
  {
    Grid grid;
    for (const std::string& line : input) 
    {
      grid.values_.emplace_back();
      for (const char c : line) 
      {
        const T value = c - '0';
        grid.values_.back().emplace_back(value);
      }
    }
    return grid;
  }

  // Returns the grid's size in the X dimension.
  size_t XSize() const { return values_.size(); }

  // Returns the grid's size in the Y dimension.
  size_t YSize(size_t x = 0) const 
  {
    return values_[x].size();
  }

  // Returns true iff `point` is within the range covered by the Grid.
  bool inRange(const Point& point) const 
  {
    return point.x >= 0 && point.x < values_.size() && point.y >= 0 &&
      point.y < values_[point.x].size();
  }

  template <typename PointContainer>
  std::vector<Point> filterInRange(const PointContainer& points) const 
  {
    std::vector<Point> filtered;
    for (const Point& point : points) 
    {
      if (inRange(point)) filtered.emplace_back(point);
    }
    return filtered;
  }

  // Accesses the value held in the cell at `point`.
  T& operator[](const Point& point) 
  {
    return values_[point.x][point.y];
  }

  // Accesses the value held in the cell at `point`.
  const T& operator[](const Point& point) const 
  {
    return values_[point.x][point.y];
  }

  // Returns a view of all the points in the Grid. Can be useful for iterating
  // over all grid points.
  PointView Points() const { return PointView(this); }

  // Iterators over values held in cells.
  iterator begin() {
    return iterator(values_.begin(), values_.end(), values_.front().begin());
  }

  iterator end() {
    return iterator(values_.end(), values_.end(),
      typename std::vector<T>::iterator());
  }

  const_iterator cbegin() const {
    return const_iterator(const_cast<Grid*>(this)->begin());
  }

  const_iterator cend() const {
    return const_iterator(const_cast<Grid*>(this)->end());
  }

  const_iterator begin() const { return cbegin(); }

  const_iterator end() const { return cend(); }

  // Iterators over points on grid.
  PointIterator point_begin() const {
    return PointIterator(Point(0, 0), this);
  }

  PointIterator point_end() const {
    return PointIterator({ static_cast<int64_t>(XSize()), 0 }, this);
  }

 private:
   Grid() = default;

   std::vector<std::vector<T>> values_;
};