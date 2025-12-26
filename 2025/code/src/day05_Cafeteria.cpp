#include <days.h>

using Rules = std::map<int, std::set<uint64_t>>;
using Update = std::vector<int>;

struct Range 
{
    std::size_t start, end;
};

uint64_t adventDay05P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<Range> ranges;
    int init = 0;
    for(auto& line : in)
    {
      if (!line.contains("-")) break;

      init++;
      const std::size_t dash_idx = line.find('-');
      ranges.emplace_back();
      ranges.back().start = std::stoull(line.substr(0, dash_idx));
      ranges.back().end = std::stoull(line.substr(dash_idx + 1, line.size() - dash_idx));
    }

    std::unordered_set<std::size_t> nFresh;
    for(int i=init; i<in.size(); i++)
    {
        const std::size_t id = std::stoull(in[i]);
        for (const auto& r : ranges)
          if (id >= r.start && id <= r.end)
              nFresh.insert(id);
    }

    score = nFresh.size();

    return score;
}

struct Range2 
{
    std::size_t start, end;
    bool invalid = false;
    bool operator == (const Range& r) const 
    {
        return start == r.start && end == r.end;
    }
};

bool merge(Range2& r1, Range2& r2) 
{
    if (r1.invalid || r2.invalid) return false;
    if (r1.start >= r2.start && r1.end <= r2.end) 
    {
        r1.invalid = true;
        return true;
    }
    if (r2.start >= r1.start && r2.end <= r1.end) 
    {
        r2.invalid = true;
        return true;
    }
    if ((r1.start >= r2.start && r1.start <= r2.end) || (r1.end >= r2.start && r1.end <= r2.end)) 
    {
        r1.start = std::min(r1.start, r2.start);
        r1.end = std::max(r1.end, r2.end);
        r2.invalid = true;
        return true;
    }

    return false;
}

bool filter(std::vector<Range2>& ranges) 
{
    // Do not ignore pairs of ranges if their values are the same; they should be processed unless their indices
    const auto n = ranges.size();
    std::sort(std::begin(ranges), std::end(ranges), [](const Range2& r1, const Range2& r2) {return !r1.invalid && r2.invalid; });
    const auto it = std::find_if(std::begin(ranges), std::end(ranges), [](const auto& r) {return r.invalid; });
    if (it != std::end(ranges)) 
    {
        ranges.erase(it, std::end(ranges));
    }

    return (n != ranges.size());
}

uint64_t adventDay05P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<Range2> ranges;

    for (auto& line : in)
    {
        if (!line.contains("-")) break;

        const std::size_t dash_idx = line.find('-');
        ranges.emplace_back();
        ranges.back().start = std::stoull(line.substr(0, dash_idx));
        ranges.back().end = std::stoull(line.substr(dash_idx + 1, line.size() - dash_idx));
    }

    do {
        for (std::size_t idx = 0; idx < ranges.size(); idx++) 
        {
            auto& r1 = ranges[idx];
            for (std::size_t idy = 0; idy < ranges.size(); idy++) 
            {
                if (idx == idy) continue;

                auto& r2 = ranges[idy];
                merge(r1, r2);
            }
        }
    } while (filter(ranges));

    for (const auto& r : ranges) 
      if (!r.invalid) score += (r.end - r.start + 1);


    return score;
}