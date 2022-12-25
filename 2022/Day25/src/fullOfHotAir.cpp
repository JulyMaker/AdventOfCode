#include <utils.h>
#include <ansiColors.h>

uint64_t adventDay25problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  int64_t sum = 0;

  // To Decimal 
  std::vector<std::string> in = parseInput(input, '\n');
  for(auto& s : in)
  {
    int64_t number = 0;
    for (int64_t i = s.size() - 1, power = 1; i >= 0; --i, power *= 5)
      switch (s[i])
      {
        case '-': number -= power;     break;
        case '=': number -= 2 * power; break;
        default:  number += power * (s[i] - '0');
      }

    sum += number;
  }

  // To SNAFU
  std::string result;
  while (sum)
  {
    char c = '0' + (sum % 5);
    bool high = c > '2';
    if (high)
    {
      switch (c)
      {
        case '3': c = '='; break;
        case '4': c = '-'; break;
        default:  c = '0';
      }
    }
      
    result += c;
    sum = sum / 5 + high;
  }

  std::reverse(result.begin(), result.end());

  std::cout << "El resultado es: " << result <<std::endl;
  return score;
}

uint64_t adventDay25problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  paintAdventCalendar2022();
  std::cout << std::endl;
  std::cout << "        Happy Advent of Code 2022!" << std::endl;

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 1;
  std::string day = "25";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay25problem12022(inputFile); break;
    case 2: result = adventDay25problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  //std::cout << "Answer is: " << result << std::endl;
  return 0;
}