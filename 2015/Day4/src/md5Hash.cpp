#include <string>
#include "md5.h"


#define CODE "ckczppom"

unsigned int adventDay4problem12015()
{
  long long int x = -1;
  bool encontrado = false;

  while (!encontrado)
  {
    x++;
    // MD5
    std::string AdventCoins = CODE + std::to_string(x);
    std::string md5Hash = md5(AdventCoins);

    if (md5Hash.substr(0,5) =="00000")
    {
      encontrado = true;
    }
  }

  return x;
}

int adventDay4problem22015()
{
  long long int x = -1;
  bool encontrado = false;

  while (!encontrado)
  {
    x++;
    // MD5
    std::string AdventCoins = CODE + std::to_string(x);
    std::string md5Hash = md5(AdventCoins);

    if (md5Hash.substr(0, 6) == "000000")
    {
      encontrado = true;
    }
  }

  return x;
}


int main(int argc, char *argv[])
{
  if((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2) )
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long int result = 0;
  switch (std::stoi(argv[1]))
  {
    case 1: 
      result = adventDay4problem12015();
      break;
    case 2:
      result = adventDay4problem22015();
      break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }
  
  std::cout << "Answer is: " << result << std::endl;
  return 0;
}