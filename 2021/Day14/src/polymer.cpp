#include <polymer.h>
#include <algorithm>

CompressedPolymer::CompressedPolymer(std::string uncompressed)
: first_(uncompressed.front()), last_(uncompressed.back()) 
{
  for (int pos = 1; pos < uncompressed.size(); ++pos) 
  {
    ++pair_counts_[{uncompressed[pos-1], uncompressed[pos]}];
  }
}

CompressedPolymer CompressedPolymer::applyRules(const std::unordered_map<std::array<char, 2>, char>& rules) const
{
  CompressedPolymer next;
  next.first_ = first_;
  next.last_ = last_;

  for (auto [pair, count] : pair_counts_) 
  {
    auto rule_it = rules.find(pair);
    if (rule_it == rules.end()) 
    {
      next.pair_counts_[pair] += count;
      continue;
    }
    next.pair_counts_[{pair[0], rule_it->second}] += count;
    next.pair_counts_[{rule_it->second, pair[1]}] += count;
  }
  return next;
}

int64_t CompressedPolymer::Score() const
{
  std::unordered_map<char, int64_t> element_counts;
  for (auto [pair, count] : pair_counts_) 
  {
    element_counts[pair[0]] += count;
    element_counts[pair[1]] += count;
  }
  ++element_counts[first_];
  ++element_counts[last_];

  for (auto& [_, count] : element_counts) 
    count /= 2;


  auto [min_it, max_it] = std::minmax_element(
    element_counts.begin(), element_counts.end(),
    [](const auto l, const auto r) { return l.second < r.second; });

  return max_it->second - min_it->second;
}