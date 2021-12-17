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
#include <cart.h>

void parseCarts(std::ifstream& infile, std::vector<std::string>& tracks, std::vector<Cart>& carts)
{
  std::string line;
  int i = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line != "")
    {
      tracks.push_back(line);

      for(int j = 0; j< line.size(); ++j)
      {
        if (line[j] == '^' || line[j] == 'v')
        {
          carts.push_back(Cart(j, i, line[j]));
          tracks[i][j] = '|';
        }
        else if (line[j] == '<' || line[j] == '>')
        {
          carts.push_back(Cart(j, i, line[j]));
          tracks[i][j] = '-';
        }
      }

      i++;
    }
  }
  infile.close();
}

long long adventDay13problem12018(std::ifstream& infile)
{
  std::vector<std::string> tracks;
  std::vector<Cart> carts;
  parseCarts(infile, tracks, carts);

  while (true) 
  {
    for (int car = 0; car < carts.size(); car++) 
    {
      carts[car].advance();

      if (tracks[carts[car].y][carts[car].x] == '+')
        carts[car].turn();
      else if (tracks[carts[car].y][carts[car].x] == '/' || tracks[carts[car].y][carts[car].x] == '\\')
        carts[car].turnCorner(tracks[carts[car].y][carts[car].x]);

      for (int car2 = 0; car2 < carts.size(); car2++)
      {
        if (car2 != car && carts[car].isCrashedWith(carts[car2])) 
        {
          std::cout << "Answer: " << carts[car].x << "," << carts[car].y << std::endl;
          return 0;
        }
      }
    }
  }

  return -1;
}

long long adventDay13problem22018(std::ifstream& infile)
{
  std::vector<std::string> tracks;
  std::vector<Cart> carts;
  parseCarts(infile, tracks, carts);

  std::sort(carts.begin(), carts.end());

  std::vector<Cart> safeCarts;
  while (carts.size() != 1) 
  {
    safeCarts.clear();

    for (int car = 0; car < carts.size(); car++) 
    {
      carts[car].advance();

      if (tracks[carts[car].y][carts[car].x] == '+')
        carts[car].turn();
      else if (tracks[carts[car].y][carts[car].x] == '/' || tracks[carts[car].y][carts[car].x] == '\\')
        carts[car].turnCorner(tracks[carts[car].y][carts[car].x]);

      for (int car2 = 0; car2 < carts.size(); car2++)
      {
        if (car2 != car && carts[car].isCrashedWith(carts[car2]))
        {
          carts[car].crashed = true;
          carts[car2].crashed = true;
        }
      }  
    }

    for (const Cart& cart : carts)
    {
      if (!cart.isCrashed())
        safeCarts.push_back(cart);
    }

    carts = safeCarts;
    std::sort(carts.begin(), carts.end());
  }

  std::cout << "Answer: " << carts[0].x << "," << carts[0].y << std::endl;

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay13problem12018(infile)
                                        : adventDay13problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day13/input13.txt";
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