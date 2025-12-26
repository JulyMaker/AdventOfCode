#include <days.h>

uint64_t adventDay04P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> inputS = parseInput(input,'\n');
    std::vector<std::string> diagram;
    diagram.emplace_back();

    for(auto& line : inputS)
        diagram.push_back('.' + line + '.');

    diagram[0] = std::string(diagram[1].size(), '.');
    diagram.push_back(diagram[0]);

    auto counter = std::vector<std::vector<int>>(diagram.size(), std::vector<int>(diagram[0].size(), 0));
    for (int row = 1; row < diagram.size() - 1; row++) 
      for (int col = 1; col < diagram[0].size() - 1; col++) 
        if (diagram[row][col] == '@') 
        {
          counter[row + 1][col]++;
          counter[row][col + 1]++;
          counter[row + 1][col + 1]++;
          counter[row - 1][col - 1]++;
          counter[row][col - 1]++;
          counter[row - 1][col]++;
          counter[row - 1][col + 1]++;
          counter[row + 1][col - 1]++;
        }

    for (int row = 1; row < diagram.size() - 1; row++) 
      for (int col = 1; col < diagram[0].size() - 1; col++) 
        if (diagram[row][col] == '@' && counter[row][col] < 4) 
          score++;


    return score;
}

void getAccessible(std::vector<std::vector<int>>& counter, const std::vector<std::string>& diagram) 
{
  for (int row = 1; row < diagram.size() - 1; row++)
    for (int col = 1; col < diagram[0].size() - 1; col++)
      if (diagram[row][col] == '@') 
      {
          counter[row + 1][col]++;
          counter[row][col + 1]++;
          counter[row + 1][col + 1]++;
          counter[row - 1][col - 1]++;
          counter[row][col - 1]++;
          counter[row - 1][col]++;
          counter[row - 1][col + 1]++;
          counter[row + 1][col - 1]++;
      }
}

std::size_t removeAccessible(const std::vector<std::vector<int>>& counter, std::vector<std::string>& diagram) 
{
    std::size_t count = 0;
    for (int row = 1; row < diagram.size() - 1; row++) 
      for (int col = 1; col < diagram[0].size() - 1; col++) 
        if (diagram[row][col] == '@' && counter[row][col] < 4) 
        {
            count++;
            diagram[row][col] = '.';
        }

    return count;
}

uint64_t adventDay04P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> inputS = parseInput(input, '\n');
    std::vector<std::string> diagram;
    diagram.emplace_back();

    for (auto& line : inputS)
        diagram.push_back('.' + line + '.');

    diagram[0] = std::string(diagram[1].size(), '.');
    diagram.push_back(diagram[0]);
    std::size_t count = 0;

    do {
        auto counter = std::vector<std::vector<int>>(diagram.size(), std::vector<int>(diagram[0].size(), 0));
        getAccessible(counter, diagram);
        count = removeAccessible(counter, diagram);
        score += count;
    } while (count > 0);

    return score;
}
