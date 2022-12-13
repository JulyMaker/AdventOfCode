#include <utils.h>


uint64_t adventDay11problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const int ROUNDS = 20;
  std::vector<monckey> monckeys;
  readInput11(input, monckeys);

  const uint64_t DIVISOR = 3;

  for (int i = 0; i< ROUNDS; i++)
  {
    for (auto& mon : monckeys)
    {
      mon.inspects += mon.items.size();
      for (auto& it : mon.items)
      {
        int num = (mon.op[1] == "old") ? it : stoi(mon.op[1]);
        uint64_t oper = ((mon.op[0] == "*") ? it * num : it + num) / DIVISOR;

        if (oper % mon.test[0] == 0)
          monckeys[mon.test[1]].items.push_back(oper);
        else 
          monckeys[mon.test[2]].items.push_back(oper);
      }

      mon.items.clear();
    }
  }
  
  std::sort(monckeys.begin(), monckeys.end(), &monckey::monckeySort);
  score = monckeys[0].inspects * monckeys[1].inspects;

  return score;
}

uint64_t adventDay11problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  const int ROUNDS = 10000;
  std::vector<monckey> monckeys;
  readInput11(input, monckeys);

  uint64_t DIVISOR = 1;
  for (auto& mon : monckeys) DIVISOR *= mon.test[0];

  for (int i = 0; i < ROUNDS; i++)
  {
    for (auto& mon : monckeys)
    {
      mon.inspects += mon.items.size();
      for (auto& it : mon.items)
      {
        uint64_t num = (mon.op[1] == "old") ? it : stoi(mon.op[1]);
        uint64_t oper = ((mon.op[0] == "*") ? it * num : it + num) % DIVISOR;

        if (oper % mon.test[0] == 0)
          monckeys[mon.test[1]].items.push_back(oper);
        else
          monckeys[mon.test[2]].items.push_back(oper);
      }

      mon.items.clear();
    }
  }

  std::sort(monckeys.begin(), monckeys.end(), &monckey::monckeySort);
  score = monckeys[0].inspects * monckeys[1].inspects;

  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "11";

  std::string fileName = DAY_PATH(day);
  //fileName = DAY_EXAMPLE_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay11problem12022(inputFile); break;
    case 2: result = adventDay11problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}