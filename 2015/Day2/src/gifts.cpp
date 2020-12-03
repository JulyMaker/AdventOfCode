#include <iostream>
#include <string>
#include <fstream>
#include <regex>

unsigned int adventDay2problem12015(unsigned int l, unsigned int w, unsigned int h)
{
  // 2*l*w + 2*w*h + 2*h*l
  int mul1 = l * w;
  int mul2 = w * h;
  int mul3 = h * l;

  return 2 * mul1 + 2 * mul2 + 2 * mul3 + std::min({ mul1, mul2, mul3 });//std::min(std::min(mul1, mul2), mul3);
}

unsigned int adventDay2problem22015(unsigned int l, unsigned int w, unsigned int h)
{
  int min = std::min({ l, w, h });
  int med = std::max({ std::min(l, w), std::min(w,h), std::min(l, h) });
  
  return 2*min + 2*med + (l*w*h);
}

unsigned int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::smatch sm;
  std::regex regExp("(\\d+)x(\\d+)x(\\d+)");
  unsigned int count = 0;

  std::string line;

  std::vector<std::string> parenthesis;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (regex_search(line, sm, regExp))
    {
      count += (problNumber == 1) ? adventDay2problem12015(std::stoi(sm[1].str()), std::stoi(sm[2].str()), std::stoi(sm[3].str()))
                                  : adventDay2problem22015(std::stoi(sm[1].str()), std::stoi(sm[2].str()), std::stoi(sm[3].str()));
    }
  }
  infile.close();

  

  return count;
}

int main(int argc, char *argv[])
{
  // argv contain inputGifts.txt path
  if (argc < 3)
  {
    std::cout << "ERROR: inputGifts.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  int result = 0;
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