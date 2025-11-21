#include <days.h>
#include <ansiColors.h>
#include <ranges>

constexpr int ROWS = 7;
constexpr int COLS = 5;

using LOCK = std::vector<std::array<std::array<char, COLS>, ROWS>>;
using KEY = std::vector<std::array<std::array<char, COLS>, ROWS>>;
using ITEM = std::array<std::array<char, COLS>, ROWS>;

bool checkFit( const ITEM& lock, const ITEM& key)
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (lock[i][j] == '#' && key[i][j] == '#') return false;

    return true;
}

uint64_t adventDay25P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    LOCK locks;
    KEY keys;

    int row = 0;
    ITEM item;
    for(auto& line : in)
    { 
      for (int idx=0; idx < line.size(); ++idx) 
          item[row][idx] = line[idx];
      
      if (row == ROWS - 1)
      {
          if (std::all_of(item[0].begin(), item[0].end(), [](const char c) { return c == '#'; }))
              locks.push_back(item);
          else
              keys.push_back(item);
      
          row = 0;
      }
      else
        ++row;
    }

    for (const auto& lock : locks)
        for (const auto& key : keys)
            if (checkFit(lock, key)) score++;

    return score;
}

uint64_t adventDay25P22025(std::ifstream& input)
{
    uint64_t score = 0;

    paintAdventCalendar2025();
    std::cout << std::endl;
    std::cout << "        Happy Advent of Code 2025!" << std::endl;

    return score;
}