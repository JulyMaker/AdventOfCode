#include <days.h>

uint64_t adventDay09P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::string in = parseLine(input);

    std::vector<std::pair<size_t, long long>> availableIndexes;
    std::vector<std::pair<size_t, size_t>> idToRequiredSpace; // vec index - id, first - starting index, second - required space
    size_t totalRequiredSpace = 0;
    bool isFreeSpace = false;
    int index = 0;

    for (auto& c : in)
    {
      int requiredSpace = c - '0';
      if (requiredSpace)
      {
          if (!isFreeSpace)
          {
              idToRequiredSpace.emplace_back(index, c - '0');
              totalRequiredSpace += idToRequiredSpace.back().second;
          }
          else
              availableIndexes.emplace_back(index, c - '0');
      }
      
      isFreeSpace = !isFreeSpace;
      index += c - '0';
    }
    
    // Fill available locations
    auto availableIndexesIt = availableIndexes.begin();
    const size_t lastIndex = totalRequiredSpace;
    for (auto required_space_rit = idToRequiredSpace.rbegin(); required_space_rit != idToRequiredSpace.rend() &&
        availableIndexesIt != availableIndexes.end() && availableIndexesIt->first < lastIndex; ++required_space_rit)
    {
        size_t id = std::distance(required_space_rit, idToRequiredSpace.rend()) - 1;
        auto& requiredSpace = required_space_rit->second;

        while (requiredSpace && availableIndexesIt != availableIndexes.end() && availableIndexesIt->first < lastIndex)
        {
            score += availableIndexesIt->first++ * id;
            if (!--availableIndexesIt->second) ++availableIndexesIt;
            --requiredSpace;
        }
    }

    // Iterate over all ids
    size_t currentId = 0;
    auto idToRequiredSpaceIt = idToRequiredSpace.begin();
    while (idToRequiredSpaceIt != idToRequiredSpace.end())
    {
        while (idToRequiredSpaceIt != idToRequiredSpace.end() && !idToRequiredSpaceIt->second)
        {
            ++idToRequiredSpaceIt;
            ++currentId;
        }

        if (idToRequiredSpaceIt == idToRequiredSpace.end()) break;

        score += currentId * idToRequiredSpaceIt->first++;
        --idToRequiredSpaceIt->second;
    }

    return score;
}

uint64_t adventDay09P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::string in = parseLine(input);

    std::vector<std::pair<size_t, long long>> availableIndexes;
    std::vector<std::pair<size_t, size_t>> idToRequiredSpace; // vec index - id, first - starting index, second - required space
    size_t totalRequiredSpace = 0;
    bool isFreeSpace = false;
    int index = 0;

    for (auto& c : in)
    {
        int requiredSpace = c - '0';
        if (requiredSpace)
        {
            if (!isFreeSpace)
            {
                idToRequiredSpace.emplace_back(index, c - '0');
                totalRequiredSpace += idToRequiredSpace.back().second;
            }
            else
                availableIndexes.emplace_back(index, c - '0');
        }

        isFreeSpace = !isFreeSpace;
        index += c - '0';
    }

    // Fill available locations 
    for (auto required_space_rit = idToRequiredSpace.rbegin(); required_space_rit != idToRequiredSpace.rend() &&
        !availableIndexes.empty(); ++required_space_rit)
    {
        size_t id = std::distance(required_space_rit, idToRequiredSpace.rend()) - 1;
        auto& requiredSpace = required_space_rit->second;

        auto availableIndexesIt = availableIndexes.begin();
        for (; availableIndexesIt != availableIndexes.end() && availableIndexesIt->first < required_space_rit->first; ++availableIndexesIt) 
        {
            if (availableIndexesIt->second >= requiredSpace)
            {
                availableIndexesIt->second -= static_cast<long long>(requiredSpace);
                while (requiredSpace--)
                    score += availableIndexesIt->first++ * id;

                requiredSpace = 0;

                if (!availableIndexesIt->second)
                    availableIndexes.erase(availableIndexesIt);

                break;
            }
        }
    }

    // Iterate over all ids
    size_t currentId = 0;
    auto idToRequiredSpaceIt = idToRequiredSpace.begin();
    while (idToRequiredSpaceIt != idToRequiredSpace.end())
    {
        while (idToRequiredSpaceIt != idToRequiredSpace.end() && !idToRequiredSpaceIt->second)
        {
            ++idToRequiredSpaceIt;
            ++currentId;
        }

        if (idToRequiredSpaceIt == idToRequiredSpace.end()) break;

        score += currentId * idToRequiredSpaceIt->first++;
        --idToRequiredSpaceIt->second;
    }


    return score;
}