#include <iostream>
#include <string>
#include <fstream>
#include <regex>

unsigned int adventDay2problem1(unsigned int min, unsigned int max, char c, std::string pass)
{
   unsigned int count = std::count(pass.begin(), pass.end(), c);

   if ((count >= min) && (count <= max))
   {
     return 1;
   }else
   {
     return 0;
   }
}

unsigned int adventDay2problem2(unsigned int pos1, unsigned int pos2, char c, std::string pass)
{
  if ((pass[pos1-1] == c) ^ (pass[pos2-1] == c)) // pos-1 string begin pos=1
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

unsigned int readFile2(std::string file, int problNumber)
{
  std::ifstream infile(file);
  char maxmin[6];
  char letter[3];
  char passw[30];

  char* split;
  unsigned int count = 0;

  while (!infile.eof()) 
  {
    infile >> maxmin >> letter >> passw;

    split = strtok(maxmin, "-");
    if (split != NULL)
    {
      unsigned int num1 = std::stoi(split);
      split = strtok(NULL, "-");

      count += (problNumber == 1)? adventDay2problem1(num1, std::stoi(split), letter[0], passw)
                                 : adventDay2problem2(num1, std::stoi(split), letter[0], passw);
    }
  }
  infile.close();

  return count;
}

unsigned int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  std::smatch sm;
  std::regex regExp("(\\d+)-(\\d+) (\\w): (\\w+)");

  unsigned int count = 0;

  while (!infile.eof()) 
  {
    std::getline(infile, line);

    if (regex_search(line, sm, regExp))
    {
      count += (problNumber == 1) ? adventDay2problem1(std::stoi(sm[1].str()), std::stoi(sm[2].str()), sm[3].str()[0], sm[4].str())
        : adventDay2problem2(std::stoi(sm[1].str()), std::stoi(sm[2].str()), sm[3].str()[0], sm[4].str());
    }
  }
  infile.close();

  return count;
}

int main(int argc, char *argv[])
{
  // argv contain inputPassw.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputPassw.txt path or problem number missing" << std::endl;
    return -1;
  }else if((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2) )
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }
 
  unsigned int result = 0;
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