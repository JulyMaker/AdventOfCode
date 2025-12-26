#include <days.h>


uint64_t adventDay03P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> lines = parseInput(input, '\n');
    
    for (auto& line : lines)
    {
      std::vector<int> bank;
      bank.reserve(line.size());
      for (const char c : line) 
        bank.push_back(c - '0');

      const auto firstIt = std::max_element(std::begin(line), std::prev(std::end(line)));
      const auto secondIt = std::max_element(std::next(firstIt), std::end(line));
      score += (*firstIt - '0') * 10 + (*secondIt - '0');
    }
        
    return score;
}

uint64_t adventDay03P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> lines = parseInput(input, '\n');

    for (auto& line : lines)
    {
      std::vector<std::size_t> bank;
      bank.reserve(line.size());
      for (const char c : line)
          bank.push_back(c - '0');

      std::size_t joltage = 0;
      auto it = std::begin(line);
      const int nDigits = 12;
      for (int i = 0; i < nDigits; i++) 
      {
          it = std::max_element(it, std::prev(std::end(line), nDigits - i - 1));
          joltage = joltage * 10 + (*it - '0');
          it = std::next(it);
      }
      score += joltage;
    }


    return score;
}