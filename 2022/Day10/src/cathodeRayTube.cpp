#include <utils.h>


uint64_t adventDay10problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const int CYCLEINC = 40;
  int x = 1;
  int cycle = 0;
  int cycleControl = 20; 

  std::vector<std::string> inst = parseInput(input, '\n');
  for (auto& ins : inst)
  {
    std::vector<std::string> instruction = splitS(ins, " ");

    int cy = (instruction[0] == "noop") ? 1 : 2;
    for (int i = 0; i < cy; i++) // noop is 1 cycle and addx is 2 cycles
    {
      cycle += 1;
      if (cycle == cycleControl) { cycleControl += CYCLEINC;  score += x * cycle; }
    }

    if (instruction[0] == "addx")
      x += stoi(instruction[1]);

    if (cycleControl > 240) break;
  }

  return score;
}

uint64_t adventDay10problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  int x = 1;
  int cycle = 0;
  const int WIDE = 40;
  const int HIGH = 6;

  std::vector<std::vector<char>> screen(HIGH, std::vector<char>(WIDE, ' '));
  
  std::vector<std::string> inst = parseInput(input, '\n');
  for (auto& ins : inst)
  {
    std::vector<std::string> instruction = splitS(ins, " ");

    int cy = (instruction[0] == "noop") ? 1 : 2;
    for (int i = 0; i < cy; i++) // noop is 1 cycle and addx is 2 cycles
    {
      cycle += 1;
      screen[(cycle - 1) / 40][(cycle - 1) % 40] = (std::abs(x - ((cycle - 1) % 40)) <= 1) ? '#' : ' ';
    }

    if(instruction[0] == "addx")
      x += stoi(instruction[1]);
  }

  for (auto& s : screen)
  {
    for (auto& c : s)
      std::cout << c;

    std::cout << std::endl;
  }
    
  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "10";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay10problem12022(inputFile); break;
    case 2: result = adventDay10problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}