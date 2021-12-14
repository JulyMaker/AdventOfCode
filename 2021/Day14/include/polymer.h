#include <string>
#include <unordered_map>
#include <array>

template<class T, size_t N>
struct std::hash<std::array<T, N>> {
  auto operator() (const std::array<T, N>& key) const {
    std::hash<T> hasher;
    size_t result = 0;
    for (size_t i = 0; i < N; ++i) 
    {
      result = result * 31 + hasher(key[i]); // ??
    }
    return result;
  }
};


class CompressedPolymer 
{
public:
  CompressedPolymer() = default;

  CompressedPolymer(std::string uncompressed);
   
  CompressedPolymer applyRules(const std::unordered_map<std::array<char, 2>, char>& rules) const;

  int64_t Score() const;

private:
  std::unordered_map<std::array<char, 2>, int64_t> pair_counts_;
  char first_ = 0;
  char last_ = 0;
};
