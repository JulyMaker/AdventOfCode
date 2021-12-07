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

const int TAM = 5;

struct myBoard
{
  int value[TAM][TAM];
};

std::vector<int> split(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(std::stoi(text.substr(start, end - start)));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(std::stoi(text.substr(start)));
  return tokens;
}

long long calculateResult(myBoard& board, int num)
{
  long long sum = 0;
  for (int i = 0; i < TAM; i++)
    for (int j = 0; j < TAM; j++)
      if (board.value[i][j] != -1) sum += board.value[i][j];

  return sum * num;
}

bool lineWin(myBoard& board, int posX, int posY)
{
  bool line = true;
  for(int i=0; i < TAM; i++)
    if (board.value[i][posY] != -1)
    {
      line = false;
      break;
    }

  if (line) return line;
  line = true;

  for (int i = 0; i < TAM; i++)
    if (board.value[posX][i] != -1)
    {
      line = false;
      break;
    }

  return line;
}

bool winBoard(myBoard& board, int num)
{
  for (int i = 0; i < TAM; i++)
    for (int j = 0; j < TAM; j++)
      if (board.value[i][j] == num)
      {
        board.value[i][j] = -1;
        return lineWin(board, i, j);
      }

  return false;
}

long long adventDay04problem12021(std::vector<int>& numbers, std::vector<myBoard>& boards)
{
  int nextNum = 0;

  while (nextNum < numbers.size())
  {
    for (auto& board : boards)
    {
      if (winBoard(board, numbers[nextNum])) return calculateResult(board, numbers[nextNum]);
    }
    
    nextNum++;
  }

  return 0;
}


long long adventDay04problem22021(std::vector<int>& numbers, std::vector<myBoard>& boards)
{
  int nextNum = 0;

  while (nextNum < numbers.size())
  {
    for (int boardPos = boards.size() -1; boardPos >= 0; boardPos--)
    {
      bool win = winBoard(boards[boardPos], numbers[nextNum]);
      if ( win && boards.size() > 1)
      {
        boards.erase(boards.begin() + boardPos);
      }
      else if (win)
      {
        return calculateResult(boards[0], numbers[nextNum]);
      }
    }

    nextNum++;
  }

  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  std::string line;
  std::string randNumbers;

  std::vector<myBoard> boards;
  std::vector<int> randomNumbers;

  std::getline(infile, randNumbers);
  std::getline(infile, line);

  randomNumbers = split(randNumbers, ",");

  while (!infile.eof())
  {
    std::vector<int> boardLine;
    myBoard board;
    for (int i = 0; i < TAM; ++i)
    {
      std::getline(infile, line);
      if (line != "")
      {
        boardLine = split(line, " ");
        for (int j = 0; j < TAM; ++j)
        {
          board.value[i][j] = boardLine[j];
        }
      }    
    }
    std::getline(infile, line);

    boards.push_back(board);
  }

  infile.close();

  long long result = (problNumber == 1) ? adventDay04problem12021(randomNumbers, boards)
                                        : adventDay04problem22021(randomNumbers, boards);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day04/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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