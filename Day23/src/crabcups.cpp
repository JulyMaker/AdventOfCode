#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>

#define LOOPS 100
#define LOOP2 10000000
#define CUPSMAX 1000000

void moveCups(std::vector<int>& cups, int& current, int& destination)
{
  const int cupSize = cups.size();

  if (current < destination)
  {
    int nextPos = current + 4;
    int emptyPos = current + 1;

    while (nextPos <= destination)
    {
      cups[emptyPos] = cups[nextPos];
      nextPos++;
      emptyPos++;
    }

    destination -= 3;
  }
  else
  {
    int nextPos = current;
    int emptyPos = (current + 3) % cupSize;

    while (nextPos > destination)
    {
      cups[emptyPos] = cups[nextPos];
      nextPos = (nextPos - 1 < 0)? cupSize-1: nextPos - 1;
      emptyPos= (emptyPos-1< 0)? cupSize-1: emptyPos - 1;
    }

    current += 3;
  }
}

long long adventDay23problem1(std::vector<int>& cups, const int MAX, const int MIN)
{
  const int cupSize = cups.size();

  std::vector<int> pickup;
  int current = 0;
  int destination = 0;

  for (int i = 0; i < LOOPS; ++i)
  {
    // three cups
    pickup.push_back(cups[(current + 1) % cupSize]);
    pickup.push_back(cups[(current + 2) % cupSize]);
    pickup.push_back(cups[(current + 3) % cupSize]);

    cups[(current + 1) % cupSize] = -1;
    cups[(current + 2) % cupSize] = -1;
    cups[(current + 3) % cupSize] = -1;

    // search destination
    destination = 0;
    int nextdest = cups[current] - 1;
    bool encontrado = false;
    while (!encontrado)
    {    
      if (nextdest < MIN) nextdest = MAX;

      if (cups[destination] == nextdest)
        encontrado = true;
      else
        destination++;

      if (destination > cupSize-1)
      {
        nextdest--;
        destination = 0;
      }
    }
    
    // move cups
    moveCups(cups, current, destination);
    cups[(destination + 1) % cupSize] = pickup[0];
    cups[(destination + 2) % cupSize] = pickup[1];
    cups[(destination + 3) % cupSize] = pickup[2];

    // update current
    current = (current+1) % cupSize;
    pickup.clear();
  }

  int onePos = 0;
  bool found = false;
  while (!found)
  {
    if (cups[onePos] == 1)
      found = true;
    else
      onePos++;
  }

  std::string result="";
  current = (onePos+1) % cupSize;
  while (current != onePos)
  {
    result += std::to_string(cups[current]);
    current = (current+1) % cupSize;
  }

  return std::stoll(result);
}

//long long adventDay23problem2(std::vector<int>& cups, const int MAX, const int MIN)
//{
//  for(int i=MAX+1; i<=CUPSMAX; ++i)
//  {
//    cups.push_back(i);
//  }
//
//  const int cupSize = cups.size();
//
//  std::vector<int> pickup;
//  int current = 0;
//  int destination = 0;
//
//  for (int i = 0; i < LOOP2; ++i)
//  {
//    // three cups
//    pickup.push_back(cups[(current + 1) % cupSize]);
//    pickup.push_back(cups[(current + 2) % cupSize]);
//    pickup.push_back(cups[(current + 3) % cupSize]);
//
//    cups[(current + 1) % cupSize] = -1;
//    cups[(current + 2) % cupSize] = -1;
//    cups[(current + 3) % cupSize] = -1;
//
//    // search destination
//    destination = 0;
//    int nextdest = cups[current] - 1;
//    bool encontrado = false;
//    while (!encontrado)
//    {
//      if (nextdest < MIN) nextdest = MAX;
//
//      if (cups[destination] == nextdest)
//        encontrado = true;
//      else
//        destination++;
//
//      if (destination > cupSize - 1)
//      {
//        nextdest--;
//        destination = 0;
//      }
//    }
//
//    // move cups
//    moveCups(cups, current, destination);
//    cups[(destination + 1) % cupSize] = pickup[0];
//    cups[(destination + 2) % cupSize] = pickup[1];
//    cups[(destination + 3) % cupSize] = pickup[2];
//
//    // update current
//    current = (current + 1) % cupSize;
//    pickup.clear();
//  }
//
//  int onePos = 0;
//  bool found = false;
//  while (!found)
//  {
//    if (cups[onePos] == 1)
//      found = true;
//    else
//      onePos++;
//  }
//
//  return cups[onePos + 1] * cups[onePos + 2];
//}

struct cup {
  int64_t value;
  cup* next{ nullptr };
};

long long adventDay23problem2(std::vector<int>& cups, const int MAX, const int MIN)
{
  std::vector<cup*> index(CUPSMAX + 1);
  std::vector<cup>  nodes(CUPSMAX);

  for (int i = 0; i < cups.size(); ++i) 
  {
    nodes[i] = { cups[i], nullptr };
    index[nodes[i].value] = &nodes[i];

    if (i > 0) nodes[i - 1].next = &nodes[i];
  }

  for (int i = cups.size(); i < CUPSMAX; ++i) {
    nodes[i] = { i + 1, nullptr };
    index[nodes[i].value] = &nodes[i];

    if (i > 0) nodes[i - 1].next = &nodes[i];
  }

  nodes.back().next = &nodes[0];

  std::array<int64_t, 3> pickup;
  cup *current = &nodes[0], *cupAux = nullptr, *nextCup = nullptr;

  for (int i = 0; i < LOOP2; ++i) {
    cupAux = current->next;
    pickup[0] = cupAux->value; cupAux = cupAux->next;
    pickup[1] = cupAux->value; cupAux = cupAux->next;
    pickup[2] = cupAux->value;

    int nextCupInd = current->value - 1; 
    if (nextCupInd < MIN) nextCupInd = MAX;

    while (std::find(pickup.begin(), pickup.end(), nextCupInd) != pickup.end()) {
      if (--nextCupInd < MIN) nextCupInd = MAX;
    }
    nextCup = index[nextCupInd];

    cup* aux = cupAux->next;
    cupAux->next = nextCup->next;
    nextCup->next = current->next;
    current->next = aux;

    current = current->next;
  }

  auto onePos = index[1];
  return onePos->next->value * onePos->next->next->value;
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  long long result=0;
  std::vector<int> cups{ 5,8,6,4,3,9,1,7,2 };

  const int max = *std::max_element(cups.begin(), cups.end());
  const int min = *std::min_element(cups.begin(), cups.end());
  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //
  //  if (line == "") continue;
  //
  //  process(players, line);  
  //}
  //infile.close();

  result = (problNumber == 1) ? adventDay23problem1(cups, max, min)
                               : adventDay23problem2(cups, CUPSMAX, min);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 //if (argc < 3)
 //{
 //  std::cout << "ERROR: *.txt path or problem number missing" << std::endl;
 //  return -1;
 //}
 //else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
 //{
 //  std::cout << "Problem 1 or 2" << std::endl;
 //  return -1;
 //}

 long long int result = 0;
 switch (std::stoi(argv[1]))
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