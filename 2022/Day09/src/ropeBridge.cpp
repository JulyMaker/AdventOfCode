#include <utils.h>

uint64_t adventDay09problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::map<std::string, int> HOR{ {"L", -1}, {"U", 0}, {"R", 1}, {"D", 0} };
  std::map<std::string, int> VER{ {"L", 0}, {"U", 1}, {"R", 0}, {"D", -1} };
  
  std::pair<int, int> head = {0,0};
  std::pair<int, int> tail = {0,0};
  std::set<std::pair<int, int>> visitedPos;

  std::vector<std::string> moves = parseInput(input, '\n');
  for (auto& m : moves)
  {
    const std::vector<std::string> mov =  splitS(m, " ");
    const std::string dir = mov[0];
    const int steps = stoi(mov[1]);

    for (int s=0; s<steps; s++)
    {
      head.first  += HOR[dir];
      head.second += VER[dir];

      int dh = head.first - tail.first;
      int dv = head.second - tail.second;

      if (std::abs(dh) > 1 || std::abs(dv) > 1)
      {
        dh = std::max(-1, std::min(1, dh));
        dv = std::max(-1, std::min(1, dv));

        tail.first += dh;
        tail.second += dv;
      }

      visitedPos.insert(tail);
    } 
  }
  
  score = visitedPos.size();

  return score;
}

uint64_t adventDay09problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  std::map<std::string, int> HOR{ {"L", -1}, {"U", 0}, {"R", 1}, {"D", 0} };
  std::map<std::string, int> VER{ {"L", 0}, {"U", 1}, {"R", 0}, {"D", -1} };

  std::set<std::pair<int, int>> visitedPos;
  std::vector<std::pair<int, int>> body;
  const int NUMKNOTS = 9;
  
  for (int i = 0; i <= NUMKNOTS; i++) // 0 is head and size is tail
    body.push_back({0,0});

  std::vector<std::string> moves = parseInput(input, '\n');
  for (auto& m : moves)
  {
    const std::vector<std::string> mov = splitS(m, " ");
    const std::string dir = mov[0];
    const int steps = stoi(mov[1]);

    for (int s = 0; s < steps; s++)
    {
      body[0].first += HOR[dir];
      body[0].second += VER[dir];

      for (int j = 1; j <= NUMKNOTS; j++)
      {
        int dh = body[j-1].first - body[j].first;
        int dv = body[j-1].second - body[j].second;

        if (std::abs(dh) > 1 || std::abs(dv) > 1)
        {
          dh = std::max(-1, std::min(1, dh));
          dv = std::max(-1, std::min(1, dv));

          body[j].first += dh;
          body[j].second += dv;
        }
      }
      
      visitedPos.insert(body[body.size()-1]);
    }
  }

  score = visitedPos.size();

  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "09";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay09problem12022(inputFile); break;
    case 2: result = adventDay09problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}