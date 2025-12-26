#include <days.h>


template<typename Container>
auto propagate_tachyons(const Container& tachyons,
    const std::unordered_set<int>& splitters)
    -> std::pair<std::vector<int>, int> {

    std::unordered_set<int> resultSet;
    int count = 0;

    std::for_each(tachyons.begin(), tachyons.end(),
        [&](int pos) {
            if (splitters.contains(pos)) {
                resultSet.insert({ pos - 1, pos + 1 });
                ++count;
            }
            else {
                resultSet.insert(pos);
            }
        });

    return { {resultSet.begin(), resultSet.end()}, count };
}

uint64_t adventDay07P12025(std::ifstream& input)
{
    uint64_t score = 0;
;
    std::vector<std::string> in = parseInput(input, '\n');
    
    auto start = in[0].find('S');
    if (start == std::string::npos) return 1;

    std::vector<int> tachyons{ static_cast<int>(start) };
    std::vector<std::unordered_set<int>> splitters;

    in.erase(in.begin());
    for(auto& line : in)
    {
        std::unordered_set<int> rowSplitters;
        for (size_t i = 0; i < line.size(); ++i) 
          if (line[i] == '^') rowSplitters.insert(i);

        if (!rowSplitters.empty())
          splitters.push_back(std::move(rowSplitters));
    }

    for (const auto& row : splitters) 
    {
        auto [new_tachyons, hits] = propagate_tachyons(tachyons, row);
        tachyons = std::move(new_tachyons);
        score += hits;
    }

    return score;
}


auto propagateTachyons(const std::unordered_map<uint64_t, uint64_t>& tachyons,
    const std::unordered_set<int>& splitters)
    -> std::unordered_map<uint64_t, uint64_t> {

    std::unordered_map<uint64_t, uint64_t> newTachyons;
    newTachyons.reserve(tachyons.size() * 2);

    for (const auto& [pos, count] : tachyons) 
    {
        if (splitters.contains(pos)) 
        {
            newTachyons[pos - 1] += count;
            newTachyons[pos + 1] += count;
        }
        else
            newTachyons[pos] += count;
    }

    return newTachyons;
}

template <std::ranges::range R>
auto enumerate(R&& range)
{
    return std::views::transform(
        std::forward<R>(range),
        [i = std::size_t{ 0 }](auto&& value) mutable {
            return std::pair{ i++, std::forward<decltype(value)>(value) };
        }
    );
}

uint64_t adventDay07P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    auto start = in[0].find('S');
    if (start == std::string::npos) return 1;

    std::unordered_map<uint64_t, uint64_t> tachyons{ {static_cast<int>(start), 1} };
    std::vector<std::unordered_set<int>> splitters;

    in.erase(in.begin());
    for (auto& line : in)
    {
        std::unordered_set<int> splitterRow;

        for (auto [idx, ch] : enumerate(line)) 
        {
          if (ch == '^')
            splitterRow.insert(static_cast<int>(idx));
        }

        if (!splitterRow.empty())
            splitters.push_back(std::move(splitterRow));
    }

    for (const auto& row : splitters)
        tachyons = propagateTachyons(tachyons, row);
    
    for (const auto& [_, count] : tachyons)
        score += count;
 

    return score;
}