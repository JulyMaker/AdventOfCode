#include <days.h>



int main(int argc, char *argv[])
{
  // argv contain inputFile, day, problem and example
  int problem = 2;
  std::string DAY = "01";
  bool EXAMPLE = false;
  const std::string YEAR = "2024";

  std::string fileName;

  /* CONTROL */
  if (!mainControl(argc, argv, fileName, DAY, problem, EXAMPLE)) return -1;
  if(fileName == "") fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(DAY, std::to_string(problem)) : DAY_PATH(DAY);
  if(!EXAMPLE) if(!inputControl(DAY, YEAR, fileName)) return -1;

  /* PROGRAM */
  const std::string FUNCTIONNAME = "adventDay" + DAY + "P" + std::to_string(problem) + YEAR;
  std::ifstream inputFile(fileName);
  uint64_t result = 0;

  switch (problem)
  {
    case 1: result = launchProblem[FUNCTIONNAME](inputFile); break;
    case 2: result = launchProblem[FUNCTIONNAME](inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}