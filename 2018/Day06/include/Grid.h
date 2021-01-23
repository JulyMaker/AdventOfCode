#include <vector>

class Coords
{
public:
  Coords(char id, int x, int y) : _id{ id }, _x{ x }, _y{ y } { }
  char id() const { return _id; }
  int  x()  const { return _x; }
  int  y()  const { return _y; }
  bool is_infinite() const { return infinite; }
  void is_infinite(bool b) { infinite = b; }
  void inc_area() { ++area; }
  int get_area() const { return area; }
private:
  char _id = '.';
  int _x = 0;
  int _y = 0;
  bool infinite = false;
  int area = 0;
};

class Grid 
{
public:
    Grid(const std::vector<std::string>& vs);

    void print_report() const;
    int shift_x(int x) const { return x + min_x; }
    int shift_y(int y) const { return y + min_y; }
    int max_finite_area() const;
    void paint_safe_region(int area);
    int get_safe_region_size() const;
private:
    char nearest_coords(int x, int y) const;
    void check_infinite_coords();
    void count_area();

    int min_x = -1;
    int min_y = -1;
    int max_x = -1;
    int max_y = -1;
    std::vector<Coords> coords;
    std::vector<std::vector<char>> grid;
};