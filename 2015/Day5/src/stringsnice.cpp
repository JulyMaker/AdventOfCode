#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

unsigned int adventDay5problem12015(std::string& line)
{
  if (line.find("ab") != std::string::npos || 
      line.find("cd") != std::string::npos || 
      line.find("pq") != std::string::npos || 
      line.find("xy") != std::string::npos) return false;
  if (std::count_if(line.begin(), line.end(), [](char c) {return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }) < 3) return false;
  
  for(int i=0; i< line.size();++i)
  {
    if (line[i] == line[i+1])  return true;
  }

  return false;
}

int adventDay5problem22015(std::string& line)
{
  bool lettersTwice = false;

  for (int i = 0; i < line.size() - 3; ++i)
  {
    std::string letters = line.substr(i, 2);
    std::string searchLine = line.substr(i+2, line.size()-(i+2));

    if (searchLine.find(letters) != std::string::npos)
    {
      lettersTwice = true;
      break;
    }
  }

  if(lettersTwice)
  {
    for (int i = 0; i < line.size() - 2; ++i)
    {
      if (line[i] == line[i + 2])  return true;    
    }
  }
  
  return false;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int count = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;
    count+= (problNumber == 1) ? adventDay5problem12015(line)
                               : adventDay5problem22015(line);
  }
  
  infile.close();

  return count;

}

int main(int argc, char *argv[])
{
  // argv contain inputStringsNice.txt path
  if (argc < 3)
  {
    std::cout << "ERROR: inputStringsNice.txt path or problem number missing" << std::endl;
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