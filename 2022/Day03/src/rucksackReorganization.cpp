#include <utils.h>

/* 'a' is 97, 'A' is 65 */

uint64_t adventDay03problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::set<char> repeatCompartments1;
  std::set<char> repeatCompartments2;

  std::vector<std::string> in = parseInput<std::string>(input);
  for(auto& ruck : in)
  {
    const int size = ruck.size();
    for(int i=0; i < size/2; i++)
    {
      if (repeatCompartments2.contains(ruck[i]))
      {
        const int sub = (islower(ruck[i])) ? int('a')-1 : int('A') - 1;
        const int add = (isupper(ruck[i])) ? 26 : 0;
        score += int(ruck[i]) - sub + add;
        break;
      }
      else
        repeatCompartments1.insert(ruck[i]);

      const int compartments2 = size / 2 + i;
      if (repeatCompartments1.contains(ruck[compartments2]))
      {
        const int sub = (islower(ruck[compartments2])) ? int('a') - 1 : int('A') - 1;
        const int add = (isupper(ruck[compartments2])) ? 26 : 0;
        score += int(ruck[compartments2]) - sub + add;
        break;
      }
      else
        repeatCompartments2.insert(ruck[compartments2]);
    }

    repeatCompartments1.clear();
    repeatCompartments2.clear();
  }

  return score;
}


uint64_t adventDay03problem22022(std::ifstream& input)
{
  uint64_t score = 0;
 
  std::string solve;

  std::set<char> repeatCompartments1;
  std::set<char> repeatCompartments2;
  std::set<char> repeatCompartments3;

  std::vector<std::string> in = parseInput<std::string>(input);
  for (int i =0; i <= in.size()-3; i=i+3)
  {
    const int size = std::max(std::max(in[i].size(), in[i + 1].size()), in[i+2].size());
    for (int j = 0; j < size; j++)
    {
      if (j < in[i].size())
      {
        if (repeatCompartments2.contains(in[i][j]) && repeatCompartments3.contains(in[i][j]))
        {
          solve += int(in[i][j]);
          break;
        }
        else
          repeatCompartments1.insert(in[i][j]);
      }
      
      if (j < in[i + 1].size())
      {
        if (repeatCompartments1.contains(in[i + 1][j]) && repeatCompartments3.contains(in[i + 1][j]))
        {
          solve += int(in[i + 1][j]);
          break;
        }
        else
          repeatCompartments2.insert(in[i + 1][j]);
      }
      
      if (j < in[i + 2].size())
      {
        if (repeatCompartments1.contains(in[i + 2][j]) && repeatCompartments2.contains(in[i + 2][j]))
        {
          solve += int(in[i + 2][j]);
          break;
        }
        else
          repeatCompartments3.insert(in[i + 2][j]);
      }
    }

    repeatCompartments1.clear();
    repeatCompartments2.clear();
    repeatCompartments3.clear();
  }

  for (char c : solve)
  {
    const int sub = (islower(c)) ? int('a') - 1 : int('A') - 1;
    const int add = (isupper(c)) ? 26 : 0;
    score += int(c) - sub + add;
  }
  
  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "03";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay03problem12022(inputFile); break;
    case 2: result = adventDay03problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}