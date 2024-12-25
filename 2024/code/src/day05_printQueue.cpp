#include <days.h>

using Rules = std::map<int, std::set<uint64_t>>;
using Update = std::vector<int>;

bool isValid(Update& update, Rules& rules) {
    for (auto num : update) 
    {
        bool after = false;
        for (auto& numnNested : update)
        {
            if (after && rules.find(numnNested) != rules.end())
            {
                for (auto setIter : rules.at(numnNested)) 
                {
                    if (num == setIter)
                        return false;
                }
            }

            if (numnNested == num) after = true;
        }
    }

    return true;
}

uint64_t adventDay05P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    Rules rules;
    bool isUpdates = false;

    for (auto& line : in)
    {
        if (!isUpdates)
        {
            std::vector<uint64_t> rule = splitUInt(line, "|");
            if (rule.size() < 2) isUpdates = true;

            if(!isUpdates)
            {
              auto iter = rules.find(rule[0]);
              if (iter != rules.end()) 
                  iter->second.emplace(rule[1]);
              else 
              {
                std::set<uint64_t> auxSet = { rule[1]};
                rules.emplace(rule[0], auxSet);
              };
            }
        }

        if (isUpdates)
        {
            Update update = splitI(line, ",");
            if (isValid(update, rules))
                score += update[(update.size() / 2)];
        }
        
    }

    return score;
}

uint64_t fixBrokenUpdate(Rules& rules, Update& brokenUpd) 
{
    std::vector<std::vector<int>> fixed_updates;
    int iter = 0;

    Update fixUpdate = {};
    fixUpdate.push_back(brokenUpd.front());
    brokenUpd.erase(brokenUpd.begin());

    for (auto& num : brokenUpd) 
    {
      int index = -1;
      for (int i = 0; i < fixUpdate.size(); i++) 
      {
          if (rules.find(fixUpdate[i]) == rules.end()) index = i;
          else if (rules.at(fixUpdate[i]).find(num) != rules.at(fixUpdate[i]).end()) continue;
          else index = i;

          break;
      }

      if (index == -1) fixUpdate.push_back(num);
      else fixUpdate.insert(fixUpdate.begin() + index, num);
    }
    
    return fixUpdate[(fixUpdate.size() / 2)];
}

uint64_t adventDay05P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    Rules rules;
    bool isUpdates = false;

    for (auto& line : in)
    {
        if (!isUpdates)
        {
            std::vector<uint64_t> rule = splitUInt(line, "|");
            if (rule.size() < 2) isUpdates = true;

            if (!isUpdates)
            {
                auto iter = rules.find(rule[0]);
                if (iter != rules.end()) iter->second.emplace(rule[1]);
                else
                {
                    std::set<uint64_t> auxSet = { rule[1] };
                    rules.emplace(rule[0], auxSet);
                };
            }
        }

        if (isUpdates)
        {
            Update update = splitI(line, ",");
            if (!isValid(update, rules))
                score += fixBrokenUpdate(rules, update);
        }

    }


    return score;
}