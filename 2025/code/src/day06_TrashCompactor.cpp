#include <days.h>

uint64_t adventDay06P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::vector<std::vector<int>> numbers;
    std::vector<std::string> signs;
    for (auto& line : in)
    {
        if (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/')
        {
          signs = splitS(line, " ");
          break;
        }
        
        std::vector<int> nums = splitI(line, " ");
        numbers.push_back(nums);
    }

    for (std::size_t x = 0; x < signs.size(); x++)
    {
      std::size_t val = numbers[0][x];
      for (std::size_t y = 1; y < numbers.size(); y++) 
      {
          switch (signs[x][0])
          {
            case '+': val += numbers[y][x];
                break;
            case '-': val -= numbers[y][x];
                break;
            case '*': val *= numbers[y][x];
                break;
            case '/': val /= numbers[y][x];
                break;
          }
      }

      score += val;
    }

    return score;
}


uint64_t adventDay06P22025(std::ifstream& input)
{
    uint64_t score = 0;
   
    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<std::string> signs = splitS(in[in.size() - 1], " ");


    int sign = signs.size() - 1;
    uint64_t total = 0;

    for (int i = in[0].size() - 1; i >= 0; i--)
    {
        std::string numS;
        for (int j = 0; j < in.size() - 1; j++)
        {
            char c = in[j][i];
            if (c != ' ') numS += c;
        }

        if (numS.empty())
        {
            sign--;
            score += total;
            total = 0;
        }
        else
        {
            if (total == 0)
              total = std::stoull(numS);
            else 
            {
                switch (signs[sign][0])
                {
                  case '+': total += std::stoull(numS);
                      break;
                  case '*': total *= std::stoull(numS);
                      break;
                } 
            }

            numS = "";
        }
    }

    score += total;

    return score; 
}