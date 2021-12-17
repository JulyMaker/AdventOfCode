#include <cart.h>
#include <iostream>
#include <string>

Cart::Cart(int x, int y, char c)
{
  this->x = x; this->y = y;
  this->crashed = false;
  this->currTurn = TURNLEFT;

  if (c == '^') this->direc = UP;
  else if (c == '>') this->direc = RIGHT;
  else if (c == 'v') this->direc = DOWN;
  else if (c == '<') this->direc = LEFT;
}

void Cart::turn() 
{
  if (currTurn == TURNLEFT) turnLeft();
  else if (currTurn == TURNRIGHT) turnRight();

  currTurn = TurnDirection((currTurn + 1) % 3);
}

void Cart::turnLeft() 
{
  direc = Direction((direc + 3) % 4);
}

void Cart::turnRight() 
{
  direc = Direction((direc + 1) % 4);
}

void Cart::turnCorner(const char& c)
{
  if (c == '/') 
  {
    if (direc == UP || direc == DOWN) turnRight();
    else if (direc == LEFT || direc == RIGHT) turnLeft();
  }
  else if (c == '\\') 
  {
    if (direc == UP || direc == DOWN) turnLeft();
    else if (direc == LEFT || direc == RIGHT) turnRight();
  }
}

void Cart::advance() 
{
  if (direc == UP)         y--;
  else if (direc == RIGHT) x++;
  else if (direc == DOWN)  y++;
  else if (direc == LEFT)  x--;
}

bool Cart::isCrashed() const 
{
  return crashed;
}

bool Cart::isCrashedWith(const Cart& c2) const 
{
  if (this->isCrashed() || c2.isCrashed())
    return false;

  if (this->x == c2.x && this->y == c2.y) 
    return true;

  return false;
}

void Cart::printTracks(std::vector<std::string>& track, std::vector<Cart>& carts)
{
  std::string aux ="";

  for (int i =0; i < track.size(); ++i)
  {
    if (i < 10)
      std::cout << "00";
    if (i < 100 && i>9)
      std::cout << "0";
    std::cout << i << " ";

    for (int j = 0; j < track[i].size(); ++j)
    {
      aux = track[i][j];
      for(auto& c : carts)
        if (i == c.y && j == c.x)
        {
          if (c.direc == UP) aux="^";
          else if (c.direc == RIGHT) aux = ">";
          else if (c.direc == DOWN) aux = "v";
          else if (c.direc == LEFT) aux = "<";
        }

      std::cout << aux;
    }
      
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}
