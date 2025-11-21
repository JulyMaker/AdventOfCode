#include <days.h>

using std::views::iota;
int64_t maxTowelColors;

int64_t countDesign(auto const& avail, auto const& pattern, std::vector<int64_t>& memoCount)
{
    if (auto const res = memoCount.at(pattern.size()); res != -1)
        return res;


    int64_t count = 0;
    for (auto const len : iota(1, maxTowelColors + 1)) 
    {
        if (static_cast<int64_t>(pattern.size()) >= len && avail.contains(pattern.substr(0, len))) 
            count += countDesign(avail, pattern.substr(len), memoCount);
    }

    memoCount[pattern.size()] = count;

    return count;
}

auto variationsDesigns(auto const& avail, auto const& requested) 
{
    int64_t possible = 0;
    int64_t variations = 0;

    std::unordered_set<std::string_view> availSv{ avail.begin(), avail.end() };
    std::vector<std::string_view> requestedSv{ requested.begin(), requested.end() };
    std::vector<int64_t> memoCount;

    for (auto const& pattern : requestedSv) 
    {
        memoCount = { 1 };
        memoCount.resize(pattern.size() + 1, -1);
        auto const num = countDesign(availSv, pattern, memoCount);

        if (num > 0)
            ++possible;

        variations += num;
    }
    return std::pair(possible, variations);
}

uint64_t adventDay19P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
	
    std::unordered_set<std::string> avail;
    std::vector<std::string> requested;

    std::vector<std::string> availSplit = splitS(in[0], ", ");
    for (auto& towel : availSplit)
        avail.insert(towel);

    for (int i = 1; i < in.size(); ++i)
        requested.push_back(in[i]);

    maxTowelColors = std::accumulate(avail.begin(), avail.end(), int64_t{ 0 }, [](int64_t lhs, auto const& rhs)
        {
            return std::max(lhs, static_cast<int64_t>(rhs.size()));
        });

    auto const [possibleDesigns, allWays] = variationsDesigns(avail, requested);

    score = possibleDesigns;

    return score;
}



uint64_t adventDay19P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::unordered_set<std::string> avail;
    std::vector<std::string> requested;

    std::vector<std::string> availSplit = splitS(in[0], ", ");
    for (auto& towel : availSplit)
        avail.insert(towel);

    for (int i = 1; i < in.size(); ++i)
        requested.push_back(in[i]);

    maxTowelColors = std::accumulate(avail.begin(), avail.end(), int64_t{ 0 }, [](int64_t lhs, auto const& rhs)
        {
            return std::max(lhs, static_cast<int64_t>(rhs.size()));
        });

    auto const [possibleDesigns, allWays] = variationsDesigns(avail, requested);

    score = allWays;

    return score;
}