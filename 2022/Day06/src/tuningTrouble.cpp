#include <utils.h>

// Example sum 39
uint64_t adventDay06problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const int MARK = 4;
  std::set<char> repeat;
  uint64_t marker = MARK;

  std::vector<std::string> in = parseInput<std::string>(input);
  for (std::string s : in)
  {
    for (int i = 0; i < s.size() - (MARK - 1); i++)
    {
      for (int j = i; j < marker; j++)
      {
        repeat.insert(s[j]);
      }

      if (repeat.size() == MARK)
      {
        score += marker;
        break;
      }
      else
      {
        repeat.clear();
        marker++;
      }
    }

    marker = MARK;
  }

  return score;
}

// Example sum 120
uint64_t adventDay06problem22022(std::ifstream& input)
{
  uint64_t score = 0;
 
  const int MARK = 14;
  std::set<char> repeat;
  uint64_t marker = MARK;

  std::vector<std::string> in = parseInput<std::string>(input);
  for (std::string s : in)
  {
    for (int i = 0; i < s.size() - (MARK - 1); i++)
    {
      for (int j = i; j < marker; j++)
      {
        repeat.insert(s[j]);
      }

      if (repeat.size() == MARK)
      {
        score += marker;
        break;
      }
      else
      {
        repeat.clear();
        marker++;
      }
    }

    marker = MARK;
  }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "06";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay06problem12022(inputFile); break;
    case 2: result = adventDay06problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}