#include <utils.h>

/* A for Rock, B for Paper, and C for Scissors */
/* X for Rock, Y for Paper, and Z for Scissors */
/* 1 for Rock, 2 for Paper, and 3 for Scissors */
/* 0 if you lost, 3 if the round was a draw, and 6 if you won */

int winTurn(const char player1, const char player2)
{
  if ((player1 == 'A' && player2 == 'X') ||
      (player1 == 'B' && player2 == 'Y') || 
      (player1 == 'C' && player2 == 'Z'))
        return 3;

  if ((player1 == 'A' && player2 == 'Z') ||  // Rock vs Scissors
      (player1 == 'B' && player2 == 'X') ||  // Paper vs Rock
      (player1 == 'C' && player2 == 'Y'))    // Scissors vs Paper
        return 0;

  return 6;
}

uint64_t adventDay02problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<std::vector<char>> in = parseInputChars(input);
  for (auto& turn : in)
  {
    score += (turn[2] == 'X') ? 1 : ((turn[2] == 'Y')? 2: 3);
    score += winTurn(turn[0], turn[2]);
  }

  return score;
}

/* X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win */

enum class RESULT {WIN=6, LOSE=0, DRAW=3};
enum class OBJ { ROCK=1, PAPER=2, SCISSORS=3, NUM_OBJ=4 };

OBJ& operator++(OBJ& mode)
{
  mode = static_cast<OBJ>(( (int)mode % ((int)OBJ::NUM_OBJ-1)) +1);
  return mode;
}

OBJ& operator--(OBJ& mode)
{
  if (mode == OBJ::ROCK) mode = OBJ::NUM_OBJ;

  mode = static_cast<OBJ>((int)mode -1);
  return mode;
}

int objetScore(const char player1, const RESULT res)
{
  OBJ obj = (player1 == 'A') ? OBJ::ROCK: ((player1 == 'B')? OBJ::PAPER : OBJ::SCISSORS);

  return (int)((res == RESULT::WIN) ? ++obj : ((res == RESULT::LOSE) ? --obj : obj));
}

uint64_t adventDay02problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  RESULT res= RESULT::WIN;

  std::vector<std::vector<char>> in = parseInputChars(input);
  for (auto& turn : in)
  {
    OBJ obj = (turn[2] == 'X') ? OBJ::ROCK : ((turn[2] == 'Y') ? OBJ::PAPER : OBJ::SCISSORS);

    switch (obj)
    {
      case OBJ::ROCK:
        score += (int)(res = RESULT::LOSE);
        break;
      case OBJ::PAPER:
        score += (int)(res = RESULT::DRAW);
        break;
      case OBJ::SCISSORS:
        score += (int)(res = RESULT::WIN);
        break;
    }
    
    score += objetScore(turn[0], res);
  }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "02";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay02problem12022(inputFile); break;
    case 2: result = adventDay02problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}