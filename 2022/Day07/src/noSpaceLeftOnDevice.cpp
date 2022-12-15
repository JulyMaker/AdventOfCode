#include <utils.h>

void printDir(std::deque<std::string> dirs)
{
  for (auto& d : dirs)
    std::cout << d << "/";
  std::cout << std::endl;
}

uint64_t adventDay07problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  const int TAM = 100000;
  std::deque<std::string> dirs;
  std::map<std::string, uint64_t> tam;

  std::vector<std::string> in= parseInput(input,'\n');

  for (auto& inst : in)
  {
    std::vector<std::string>instruction = splitS(inst, " ");

    if (instruction[0] == "$" && instruction[1] == "cd")
    {
      if (instruction[2] == "..")
      {
        dirs.pop_back();
        //printDir(dirs);
      }
      else
      {
        std::string aux = instruction[2];
        int index = 0;

        while (tam.find(aux) != tam.end())
        {
          index++;
          aux += index;
        }
        tam[aux];
        dirs.push_back(aux);
        //printDir(dirs);
      }
    }
    else if (instruction[0] != "dir" && instruction[0] != "$")
    {
      for (auto& d : dirs)
        tam[d] += stoll(instruction[0]);
    }
  }

  for (auto& t : tam)
    if (t.second <= TAM) score += t.second;

  return score;
}

uint64_t adventDay07problem22022(std::ifstream& input)
{
  uint64_t score = LLONG_MAX;

  std::deque<std::string> dirs;
  std::map<std::string, uint64_t> tam;

  std::vector<std::string> in = parseInput(input, '\n');

  for (auto& inst : in)
  {
    std::vector<std::string>instruction = splitS(inst, " ");

    if (instruction[0] == "$" && instruction[1] == "cd")
    {
      if (instruction[2] == "..")
      {
        dirs.pop_back();
        //printDir(dirs);
      }
      else
      {
        std::string aux = instruction[2];
        int index = 0;

        while (tam.find(aux) != tam.end())
        {
          index++;
          aux += index;
        }
        tam[aux];
        dirs.push_back(aux);
        //printDir(dirs);
      }
    }
    else if (instruction[0] != "dir" && instruction[0] != "$")
    {
      for (auto& d : dirs)
        tam[d] += stoll(instruction[0]);
    }
  }

  const uint64_t FREESPACE = 70000000 - 30000000;
  const uint64_t NEEDFREE = tam["/"] - FREESPACE;

  for (auto& t : tam)
    if(t.second >= NEEDFREE) score = std::min(score, t.second);

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "07";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay07problem12022(inputFile); break;
    case 2: result = adventDay07problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}