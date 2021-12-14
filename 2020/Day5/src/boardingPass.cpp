#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>

#define ROWS 128
#define COLS 8

int adventDay5problem1(std::string& boardingPass)
{
  int minRow = 0;
  int maxRow = ROWS - 1;
  int minCol = 0;
  int maxCol = COLS - 1;

  int sumAux = 0;

  for(int i=0; i< boardingPass.size(); ++i)
  {
    switch(boardingPass[i])
    {
    case 'F':
      sumAux = minRow + maxRow;
      maxRow = (sumAux%2==0)? sumAux/2: (sumAux -1)/2;
      break;
    case 'B':
      sumAux = minRow + maxRow;
      minRow = (sumAux % 2 == 0) ? (sumAux / 2)+1 : ((sumAux - 1) / 2)+1;
      break;
    case 'L':
      sumAux = minCol + maxCol;
      maxCol = (sumAux % 2 == 0) ? sumAux / 2 : (sumAux - 1) / 2;
      break;
    case 'R':
      sumAux = minCol + maxCol;
      minCol = (sumAux % 2 == 0) ? (sumAux / 2) + 1 : ((sumAux - 1) / 2) + 1;
      break;
    }
  }
   
  return minRow * 8 + minCol; // Boarding Pass Id
}


int adventDay5problem2(std::string& boardingPass, std::vector<std::string>& plane)
{
  int minRow = 0;
  int maxRow = ROWS - 1;
  int minCol = 0;
  int maxCol = COLS - 1;

  int sumAux = 0;

  for (int i = 0; i < boardingPass.size(); ++i)
  {
    switch (boardingPass[i])
    {
    case 'F':
      sumAux = minRow + maxRow;
      maxRow = (sumAux % 2 == 0) ? sumAux / 2 : (sumAux - 1) / 2;
      break;
    case 'B':
      sumAux = minRow + maxRow;
      minRow = (sumAux % 2 == 0) ? (sumAux / 2) + 1 : ((sumAux - 1) / 2) + 1;
      break;
    case 'L':
      sumAux = minCol + maxCol;
      maxCol = (sumAux % 2 == 0) ? sumAux / 2 : (sumAux - 1) / 2;
      break;
    case 'R':
      sumAux = minCol + maxCol;
      minCol = (sumAux % 2 == 0) ? (sumAux / 2) + 1 : ((sumAux - 1) / 2) + 1;
      break;
    }
  }

  plane[minRow][minCol] = 'X';

  return minRow * 8 + minCol;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int maxPassId = 0;
  int passId = 0;

  std::vector<std::string> plane(ROWS,"--------");

  while (!infile.eof()) 
  {
    std::getline(infile, line);

    if (line != "")
    {
      passId = (problNumber == 1) ? adventDay5problem1(line)
                                  : adventDay5problem2(line, plane);

      maxPassId = std::max(maxPassId, passId);
    }
  }
  infile.close();

  if (problNumber == 2)
  {
    for(int row =1; row < plane.size()-1; ++row)
    {
      for(int col=1; col < COLS-1; ++col)
      {
        if(plane[row][col] == '-' && plane[row][col-1] == 'X' && plane[row][col + 1] == 'X')
        {
          maxPassId = row * 8 + col; //my seat
          break;
        }
      }
    }
    //Visual problem
    //for (int i = 0; i < plane.size(); ++i)
    //{
    //  std::cout << plane[i] << std::endl; 
    //}
  }

  return maxPassId;
}

int main(int argc, char *argv[])
{
  // argv contain inputTobogan.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputTobogan.txt path or problem number missing" << std::endl;
    return -1;
  }else if((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2) )
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