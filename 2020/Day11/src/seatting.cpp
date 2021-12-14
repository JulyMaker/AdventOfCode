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

int busyAround(std::vector<std::string>& seats, int i, int j)
{
  const int MIN = 0;
  const int MAXROW = seats.size() - 1;
  const int MAXCOL = seats[i].size() - 1;

  int count = 0;
  count += (i-1 >= MIN) ? seats[i-1][j] == '#' : 0;
  count += (i+1 <= MAXROW) ? seats[i+1][j] == '#' : 0;
  count += (j-1 >= MIN) ? seats[i][j-1] == '#' : 0;
  count += (j+1 <= MAXCOL) ? seats[i][j+1] == '#' : 0;

  count += (i-1 >= MIN && j-1 >= MIN) ? seats[i-1][j-1] == '#' : 0;
  count += (i+1 <= MAXROW && j+1 <= MAXCOL) ? seats[i+1][j+1] == '#' : 0;
  count += (i+1 <= MAXROW && j-1 >= MIN) ? seats[i+1][j-1] == '#' : 0;
  count += (i-1 >= MIN && j+1 <= MAXCOL) ? seats[i-1][j+1] == '#' : 0;

  return count;
}

int adventDay11problem1(std::vector<std::string>& seats, std::vector<std::string>& seatsAux, int busySeat)
{
  bool change = false;
  
  for(int i=0; i< seats.size(); ++i)
  {
    for (int j = 0; j < seats[i].size(); ++j)
    {
      int busyAroun = busyAround(seats, i, j);

      if (seats[i][j] == 'L' && busyAroun == 0)
      {  
        change = true;
        seatsAux[i][j] = '#';
        busySeat++;
      }
      else if(seats[i][j] == '#' && busyAroun >= 4)
      {
        change = true;
        seatsAux[i][j] = 'L';
        busySeat--;
      }
      else
      {
        seatsAux[i][j] = seats[i][j];
      }
    }
  }

  if (change)
    return adventDay11problem1(seatsAux, seats, busySeat);
  else
    return busySeat;
}

int busyAround2(std::vector<std::string>& seats, int i, int j)
{
  const int MIN = 0;
  const int MAXROW = seats.size() - 1;
  const int MAXCOL = seats[i].size() - 1;

  int count = 0;

  int k = i-1;
  while (k >= MIN)
  {
    if (seats[k][j] == '#') { count++; break; }
    if (seats[k][j] == 'L') { break; }
    k--;
  }

  k = i+1;
  while (k <= MAXROW)
  {
    if (seats[k][j] == '#') { count++; break; }
    if (seats[k][j] == 'L') { break; }
    k++;
  }

  k = j-1;
  while (k >= MIN)
  {
    if (seats[i][k] == '#') { count++; break; }
    if (seats[i][k] == 'L') { break; }
    k--;
  }

  k = j+1;
  while (k <= MAXCOL)
  {
    if (seats[i][k] == '#') { count++; break; }
    if (seats[i][k] == 'L') { break; }
    k++;
  }

  k = i-1; int m = j-1;
  while (k >= MIN && m >= MIN)
  {
    if (seats[k][m] == '#') { count++; break; }
    if (seats[k][m] == 'L') { break; }
    k--; m--;
  }
    
  k = i+1; m = j+1;
  while (k <= MAXROW && m <= MAXCOL)
  {
    if (seats[k][m] == '#') { count++; break; }
    if (seats[k][m] == 'L') { break; }
    k++; m++;
  }

  k = i+1; m = j-1;
  while (k <= MAXROW && m >= MIN)
  {
    if (seats[k][m] == '#') { count++; break; }
    if (seats[k][m] == 'L') { break; }
    k++; m--;
  }

  k = i-1; m = j+1;
  while (k >= MIN && m <= MAXCOL)
  {
    if (seats[k][m] == '#') { count++; break; }
    if (seats[k][m] == 'L') { break; }
    k--; m++;
  }

  return count;
}

long long adventDay11problem2(std::vector<std::string>& seats, std::vector<std::string>& seatsAux, int busySeat)
{
  bool change = false;

  for (int i = 0; i < seats.size(); ++i)
  {
    for (int j = 0; j < seats[i].size(); ++j)
    {
      int busyAroun = busyAround2(seats, i, j);

      if (seats[i][j] == 'L' && busyAroun == 0)
      {
        change = true;
        seatsAux[i][j] = '#';
        busySeat++;
      }
      else if (seats[i][j] == '#' && busyAroun >= 5)
      {
        change = true;
        seatsAux[i][j] = 'L';
        busySeat--;
      }
      else
      {
        seatsAux[i][j] = seats[i][j];
      }
    }
  }

  if (change)
    return adventDay11problem2(seatsAux, seats, busySeat);
  else
    return busySeat;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::string> seats;
  std::vector<std::string> seatsAux;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;
    seats.push_back(line);

  }
  infile.close();

  seatsAux = seats;

  return (problNumber == 1) ? adventDay11problem1(seats, seatsAux, 0)
                            : adventDay11problem2(seats, seatsAux, 0);
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  if (argc < 3)
  {
    std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long int result = 0;
  switch (std::stoi(argv[2]))
  {
  case 1:
    result = readFile(argv[1], 1);
    break;
  case 2:
    result = readFile(argv[1], 2);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}