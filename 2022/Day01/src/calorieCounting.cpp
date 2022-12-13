#include <utils.h>

uint64_t adventDay01problem12022(std::ifstream& input)
{
  uint64_t maxCalories = 0;
  uint64_t elfCalories=0;

  std::string calories;
  while (std::getline(input, calories))
  {
    if (calories != "")
    {
      elfCalories += stoi(calories);
    }
    else
    {
      maxCalories = std::max(maxCalories, elfCalories);
      elfCalories = 0;
    }
  }
  input.close();

  return maxCalories;
}

uint64_t adventDay01problem22022(std::ifstream& input)
{
  uint64_t elfCalories = 0;
  int maxCal[3]  = {0,0,0};

  std::string calories;
  while (!input.eof())
  {
    std::getline(input, calories);
    if (calories != "")
    {
      elfCalories += stoi(calories);
    }
    else
    {
      if (elfCalories >= maxCal[0])
      {
        maxCal[2] = maxCal[1];
        maxCal[1] = maxCal[0];
        maxCal[0] = elfCalories;
      }
      else if (elfCalories >= maxCal[1])
      {
        maxCal[2] = maxCal[1];
        maxCal[1] = elfCalories;
      }
      else if (elfCalories > maxCal[2])
      {
        maxCal[2] = elfCalories;
      }

      elfCalories = 0;
    }
  }
  input.close();

  return maxCal[0] + maxCal[1] + maxCal[2];
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "01";

  std::string fileName = DAY_PATH(day);
  //fileName = DAY_EXAMPLE_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay01problem12022(inputFile); break;
    case 2: result = adventDay01problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}