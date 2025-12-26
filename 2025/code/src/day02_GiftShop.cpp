#include <days.h>

struct Range 
{
    std::size_t start, end;
};

uint64_t adventDay02P12025(std::ifstream& input)
{
    uint64_t score = 0;
    
    std::vector<Range> ranges;

    std::vector<std::string> rangesString = parseInput(input,'\n');
    for (auto& rangesStr : rangesString)
    {
        std::vector<std::string> rangesS = splitS(rangesStr, ",");
        for (auto& r : rangesS)
        {
          std::vector<uint64_t>rangeUI= splitUInt(r, "-");
          Range current;
          current.start = rangeUI[0];
          current.end = rangeUI[1];
          ranges.push_back(current);
        } 
    }

    for (const auto& range : ranges) 
    {
        for (std::size_t num = range.start; num <= range.end; num++)
        {
            std::size_t n = num;
            std::size_t numSize = 0;
            while (n > 0) 
            {
                numSize++;
                n /= 10;
            }
            if (numSize % 2 != 0) continue;

            std::size_t halfNum1 = num;
            std::size_t modBy = 1;
            for (int i = 0; i < numSize / 2; i++)
            {
                halfNum1 /= 10;
                modBy *= 10;
            }
            std::size_t halfNum2 = num % modBy;
            if (halfNum1 == halfNum2)
                score += num;
        }
    }

    return score;
}

uint64_t adventDay02P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<Range> ranges;

    std::vector<std::string> rangesString = parseInput(input, '\n');
    for (auto& rangesStr : rangesString)
    {
        std::vector<std::string> rangesS = splitS(rangesStr, ",");
        for (auto& r : rangesS)
        {
            std::vector<uint64_t>rangeUI = splitUInt(r, "-");
            Range current;
            current.start = rangeUI[0];
            current.end = rangeUI[1];
            ranges.push_back(current);
        }
    }

    for (const auto& r : ranges)
    {
        for (std::size_t number = r.start; number <= r.end; number++) 
        {
          std::size_t nDigits = 0;
          {
                std::size_t n = number;
                while (n > 0) 
                {
                    n /= 10;
                    nDigits++;
                }
          }

          for (std::size_t seqSize = 1; seqSize < nDigits; seqSize++)
          {
              if (nDigits % seqSize != 0) continue;

              std::size_t order_of_sequence = 1; // order of magnitue of the sequence, 10^n_parts
              for (int i = 0; i < seqSize; i++)
                  order_of_sequence *= 10;

              const std::size_t sequence = number % order_of_sequence;
              std::size_t n = number;
              bool isPattern = true;
              while (n > 0) 
              {
                  if (n % order_of_sequence != sequence) 
                  {
                      isPattern = false;
                      break;
                  }
                  n /= order_of_sequence;
              }

              if (isPattern)
              {
                  score += number;
                  break;
              }
          }
        }
    }

    return score;
}