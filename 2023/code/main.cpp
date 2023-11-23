#include <days.h>



int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 1;
  const std::string day = "01";
  const bool EXAMPLE = false;
  const std::string FUNCTIONNAME = "adventDay" + day + "P" + std::to_string(problem) + "2023";

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;

  switch (problem)
  {
    case 1: result = launchProblem[FUNCTIONNAME](inputFile); break;
    case 2: result = launchProblem[FUNCTIONNAME](inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  //std::cout << "Answer is: " << result << std::endl;
  return 0;
}