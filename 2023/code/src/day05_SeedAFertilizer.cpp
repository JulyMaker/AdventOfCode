#include <days.h>

using Maps = std::vector<std::vector<std::tuple<uint64_t, uint64_t, uint64_t>>>;

uint64_t adventDay05P12023(std::ifstream& input)
{
    uint64_t score = UINT64_MAX;

    Maps maps;
    std::vector<uint64_t> seeds;
    readInput05_2023(input, seeds, maps);

    for (auto& map : maps)
    {
        for (auto& seed : seeds)
        {
            for (auto& nums : map)
            {
                uint64_t start = std::get<1>(nums);
                uint64_t limit = std::get<1>(nums) + std::get<2>(nums) - 1;
                if (start <= seed && seed <= limit)
                {
                    seed = std::get<0>(nums) + (seed - std::get<1>(nums));
                    break;
                }
            }
        }
    }
    
    for (auto& seed : seeds)
        score = (seed < score) ? seed : score;

    return score;
}

struct Range 
{
    uint64_t start;
    uint64_t range;
};

using Map = std::vector<std::tuple<uint64_t, uint64_t, uint64_t>>;
using Interv = std::tuple<uint64_t, uint64_t, uint64_t>;

bool isInRange(uint64_t source, Interv intv)
{
    return std::get<1>(intv) <= source && std::get<1>(intv) + std::get<2>(intv) > source;
}

bool inInterval(Range range, Interv intv)
{
    return isInRange(range.start, intv) ||  isInRange(range.start + range.range, intv) ||
        (range.start < std::get<1>(intv) && range.start + range.range >= std::get<1>(intv) + std::get<2>(intv));
}

std::vector<Range> getPossibleRanges(Range rangeMain, Map& map) 
{
    std::vector<Range> in = { rangeMain };
    std::vector<Range> out;
    Range rangeOut;
    Range rangeIn1;
    Range rangeIn2;

    for (auto& interv : map) 
    {
        std::vector<Range> temp;
        for (auto& range : in) 
        {
            if (inInterval(range, interv))
            {
                if (range.start < std::get<1>(interv) && range.start + range.range < std::get<1>(interv) + std::get<2>(interv))
                {
                    rangeOut.start = std::get<0>(interv);
                    rangeOut.range = (range.start + range.range) - std::get<1>(interv);
                    rangeIn1.start = range.start;
                    rangeIn1.range = std::get<1>(interv) - range.start;
                    if (rangeIn1.range != 0) 
                        temp.push_back(rangeIn1);
                }
                else if (range.start + range.range > std::get<1>(interv) + std::get<2>(interv) && range.start >= std::get<1>(interv))
                {
                    rangeOut.start = std::get<0>(interv) + (range.start - std::get<1>(interv));
                    rangeOut.range = (std::get<1>(interv) + std::get<2>(interv)) - range.start;
                    rangeIn1.start = std::get<1>(interv) + std::get<2>(interv);
                    rangeIn1.range = (range.start + range.range) - (std::get<1>(interv) + std::get<2>(interv));
                    if (rangeIn1.range != 0) 
                        temp.push_back(rangeIn1);
                }
                else if (range.start <= std::get<1>(interv) && range.start + range.range >= std::get<1>(interv) + std::get<2>(interv))
                {
                    rangeOut.start = std::get<0>(interv);
                    rangeOut.range = std::get<2>(interv);
                    rangeIn1.start = range.start;
                    rangeIn1.range = std::get<1>(interv) - range.start;
                    rangeIn2.start = std::get<1>(interv) + std::get<2>(interv);
                    rangeIn2.range = (range.start + range.range) - (std::get<1>(interv) + std::get<2>(interv));

                    if (rangeIn1.range != 0)
                        temp.push_back(rangeIn1);

                    if (rangeIn2.range != 0)
                        temp.push_back(rangeIn2);
                }
                else 
                {
                    rangeOut.start = std::get<0>(interv) + (range.start - std::get<1>(interv));
                    rangeOut.range = range.range;
                }
                out.push_back(rangeOut);
            }
            else 
            {
                temp.push_back({ range.start , range.range });
            }
        }
        in = temp;
    }

    if (in.size() > 0) 
        out.insert(out.end(), in.begin(), in.end());

    return out;
}


uint64_t adventDay05P22023(std::ifstream& input)
{
    uint64_t score = UINT64_MAX;

    Maps maps;
    std::vector<uint64_t> seeds;
    readInput05_2023(input, seeds, maps);

    std::vector<Range> ranges;
    for (int i = 0; i < seeds.size(); i += 2) 
        ranges.push_back({ seeds[i] , seeds[i + 1] });

    std::vector<Range> swap;
    for (auto& map : maps)
    {
        swap.clear();
        for (auto& range : ranges)
        {
            std::vector<Range> result = getPossibleRanges(range, map);
            swap.insert(swap.end(), result.begin(), result.end());
        }
        ranges = swap;
    }


    for (auto& range : ranges)
        score = (range.start < score) ? range.start : score;


    return score;
}