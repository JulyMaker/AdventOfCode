#include <utils.h>

uint64_t adventDay05problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<std::stack<char>> crane;
  std::vector<std::vector<int>> moves;

  readInput05(input, crane, moves);

  for (auto& move : moves)
  {
    for (int i = 0; i < move[0]; i++)
    {
      crane[move[2] - 1].push(crane[move[1] - 1].top());
      crane[move[1] - 1].pop();
    }
  }

  for (auto& c : crane)
    std::cout << c.top();

  std::cout << std::endl;

  return score;
}


uint64_t adventDay05problem22022(std::ifstream& input)
{
  uint64_t score = 0;
 
  std::vector<std::stack<char>> crane;
  std::vector<std::vector<int>> moves;

  readInput05(input, crane, moves);

  for (auto& move : moves)
  {
    std::vector<char> aux;
    for (int i = 0; i < move[0]; i++)
    {
      aux.push_back(crane[move[1] - 1].top());
      crane[move[1] - 1].pop();
    }

    for(int j= aux.size() - 1; j >= 0; j--)
      crane[move[2] - 1].push(aux[j]);
  }

  for (auto& c : crane)
    std::cout << c.top();

  std::cout << std::endl;
  
  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "05";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay05problem12022(inputFile); break;
    case 2: result = adventDay05problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}