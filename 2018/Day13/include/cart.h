#include <vector>

enum Direction { UP, RIGHT, DOWN, LEFT };
enum TurnDirection { TURNLEFT, GOSTRAIGHT, TURNRIGHT };

struct Cart {
  int x, y;

  Direction direc;
  TurnDirection currTurn;
  bool crashed;

  Cart(int, int, char);
  void turn();
  void turnLeft();
  void turnRight();
  void turnCorner(const char&);
  void advance();
  bool isCrashed() const;
  bool isCrashedWith(const Cart&) const;
  void printTracks(std::vector<std::string>& track, std::vector<Cart>& carts);

  bool operator < (const Cart& car) const
  {
    return (y == car.y) ? x < car.x : y < car.y;
  }
};