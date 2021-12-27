#include <utils.h>


uint64_t adventDay01problem12019(std::ifstream& input)
{
  uint64_t result = 0;
  int fuel;
  while (input >> fuel) 
    result += fuel / 3 - 2;

  return result;
}


uint64_t adventDay01problem22019(std::ifstream& input)
{
  uint64_t result = 0;
  int fuel;
  while (input >> fuel) 
  {
    while (fuel / 3 - 2 >= 0) 
    {
      fuel = fuel / 3 - 2;
      result += fuel;
    }
  }

  return  result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "01";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
  case 1:
    result = adventDay01problem12019(inputFile);
    break;
  case 2:
    result = adventDay01problem22019(inputFile);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}