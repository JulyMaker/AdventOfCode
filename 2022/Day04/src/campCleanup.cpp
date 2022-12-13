#include <utils.h>

uint64_t adventDay04problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::string rex = "(\\d+)-(\\d+),(\\d+)-(\\d+)";
  std::vector<std::string> in = parseInputReg(input, rex);

  for(int i=0; i<= in.size()-5; i=i+5)
  {
    const int min1 = stoi(in[i + 1]);
    const int max1 = stoi(in[i + 2]);
    const int min2 = stoi(in[i + 3]);
    const int max2 = stoi(in[i + 4]);

    if ((min1 <= min2) && (max1 >= max2) ||
      (min2 <= min1) && (max2 >= max1))
      score++;
  }

  return score;
}


uint64_t adventDay04problem22022(std::ifstream& input)
{
  uint64_t score = 0;
 
  std::string rex = "(\\d+)-(\\d+),(\\d+)-(\\d+)";
  std::vector<std::string> in = parseInputReg(input, rex);

  for (int i = 0; i <= in.size() - 5; i = i + 5)
  {
    const int min1 = stoi(in[i + 1]);
    const int max1 = stoi(in[i + 2]);
    const int min2 = stoi(in[i + 3]);
    const int max2 = stoi(in[i + 4]);

    if (std::min(max1, max2) >= std::max(min1,min2))
      score++;
  }
  
  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "04";

  std::string fileName = DAY_PATH(day);
  //fileName = DAY_EXAMPLE_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay04problem12022(inputFile); break;
    case 2: result = adventDay04problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}