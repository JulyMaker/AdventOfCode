#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void readFile(std::string file, std::vector<int>& vector)
{
  std::ifstream infile(file);
  unsigned int num;

  while (!infile.eof()) {
    infile >> num;
    vector.push_back(num);
  }
  infile.close();
}

unsigned int adventDay1problem1(std::vector<int>& vector)
{
  #define SEARCHSUM 2020

  unsigned int ptr = 1;

  while (ptr < vector.size() -1)
  {
    unsigned int ptrNumber = vector[ptr];

    for(unsigned int i=ptr + 1; i < vector.size(); i++)
    {
      unsigned int sum = ptrNumber + vector[i];
      if (sum == SEARCHSUM)
      {
        std::cout << "Number1: " << ptrNumber << " pos: " << ptr << std::endl;
        std::cout << "Number2: " << vector[i] << " pos: " << i << std::endl;
        return ptrNumber * vector[i];
      }
    }

    ptr++;
  }

  std::cout << "No solution" << std::endl;

  return 0;
}

unsigned int adventDay1problem2(std::vector<int>& vector)
{
#define SEARCHSUM 2020

  unsigned int ptr = 1;

  while (ptr < vector.size() - 2)
  {
    unsigned int ptrNumber = vector[ptr];

    for (unsigned int i = ptr + 1; i < vector.size()-1; i++)
    {
      for (unsigned int j = i + 1; j < vector.size(); j++)
      {
        unsigned int sum = ptrNumber + vector[i] + vector[j];
        if (sum == SEARCHSUM)
        {
          std::cout << "Number1: " << ptrNumber << " pos: " << ptr << std::endl;
          std::cout << "Number2: " << vector[i] << " pos: " << i << std::endl;
          std::cout << "Number3: " << vector[j] << " pos: " << j << std::endl;
          return ptrNumber * vector[i] * vector[j];
        }
      }
    }

    ptr++;
  }

  std::cout << "No solution" << std::endl;

  return 0;
}

int main(int argc, char *argv[])
{
  // argv contain inputNumbers.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputNumbers.txt path" << std::endl;
    return -1;
  }

  std::vector<int> miVector;
  readFile(argv[1], miVector);
 
  unsigned int result = 0;
  switch (std::stoi(argv[2]))
  {
    case 1: 
      result= adventDay1problem1(miVector);     
      break;
    case 2:
      result = adventDay1problem2(miVector);
      break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }
  
  std::cout << "Answer is: " << result << std::endl;
  return 0;
}