#include <utils.h>

using connectionsMap = std::map<std::string, std::vector<std::string>>;
using flowRatesMap = std::map<std::string, int64_t>;
using edge = std::pair<std::string, int64_t>;
using edges = std::map<std::string, std::vector<edge>>;

edges shortestDists(const flowRatesMap& rates, const connectionsMap& conns)
{
  edges dists;
  for (const auto& [valve, valves] : conns) 
  {
    auto& edges = dists[valve];
    std::deque<edge> q;
    q.emplace_back(valve, 0);
    std::set<std::string> v;
    v.insert(valve);

    while (!q.empty()) 
    {
      auto [cur, d] = q.front();
      q.pop_front();
      for (const auto& nbr : conns.at(cur)) 
      {
        if (v.count(nbr)) continue;
        v.insert(nbr);
        edges.emplace_back(nbr, d + 1);
        q.emplace_back(nbr, d + 1);
      }
    }
  }
  return dists;
}

using dists = std::vector<std::vector<int64_t>>;
using flowRates = std::vector<int64_t>;

std::tuple<flowRates, dists, int> prune(const flowRatesMap& rates_map, const edges& edges)
{
  flowRates rates;
  std::map<std::string, int> idx;
  for (const auto& [valve, rate] : rates_map) 
  {
    if (rate == 0 && valve != "AA") continue;
    idx[valve] = rates.size();
    rates.push_back(rate);
  }

  dists dists(rates.size(), std::vector<int64_t>(rates.size(), -1));
  for (const auto& [from, es] : edges) 
  {
    if (rates_map.at(from) == 0 && from != "AA") continue;

    dists[idx[from]][idx[from]] = 0;
    for (const auto& [to, dist] : es) 
    {
      if (rates_map.at(to) == 0) continue;

      dists[idx[from]][idx[to]] = dist;
    }
  }

  return { rates, dists, idx["AA"] };
}

struct explorer 
{
  int valve;      // 4 bits
  int remaining;  // 5 bit
  bool free;      // 1 bit
};

int16_t key(const explorer& e) 
{
  return (e.valve << 6) | (e.remaining << 1) | (e.free);
}

int64_t key(std::pair<explorer, explorer> es, int minute, const std::vector<bool>& open)
{
  if (es.first.valve < es.second.valve) es = { es.second, es.first };

  int64_t k = 0;
  for (int i = 0; i < open.size(); i++)
    if (open[i]) k |= (1 << i);

  k <<= 16;
  k |= key(es.first);
  k <<= 16;
  k |= key(es.second);
  k <<= 4;
  k |= minute;

  return k;
}

int64_t releasing(const std::vector<bool>& open, const flowRates& rates) 
{
  int64_t sum = 0;
  for (int i = 0; i < open.size(); i++) 
  {
    if (open[i]) sum += rates[i];
  }

  return sum;
}

int64_t maxReleased(const dists& dists, const flowRates& rates, std::pair<explorer, explorer> es, int minute,
  int maxMinute, std::vector<bool>& open, std::unordered_map<int64_t, int64_t>& memo, bool elephant) 
{
  if (minute > maxMinute) return 0;

  auto k = key(es, minute, open);
  if (auto it = memo.find(k); it != memo.end()) return it->second;
  bool flipped1 = false;

  if (!es.first.free && es.first.remaining == 0) 
  {
    open[es.first.valve] = true;
    es.first.free = true;
    flipped1 = true;
  }

  bool flipped2 = false;
  if (!es.second.free && es.second.remaining == 0) 
  {
    open[es.second.valve] = true;
    es.second.free = true;
    flipped2 = true;
  }

  int64_t per_tick = releasing(open, rates);
  int64_t released = std::numeric_limits<int64_t>::min();
  for (int i = 0; i < dists.size(); i++) 
  {
    for (int j = 0; j < dists.size(); j++) 
    {
      if (elephant && i == j) continue;

      auto next = es;
      int go = std::numeric_limits<int>::max();

      if (es.first.free) 
      {
        int dist1 = dists[es.first.valve][i];
        if (dist1 < 0) continue;
        if (open[i]) continue;
        // start moving
        next.first.valve = i;
        next.first.remaining = dist1 + 1;
        next.first.free = false;
        go = std::min(go, dist1 + 1);
      }
      else 
      {
        go = std::min(go, es.first.remaining);
      }

      if (elephant) 
      {
        if (es.second.free) 
        {
          int dist2 = dists[es.second.valve][j];
          if (dist2 < 0) continue;
          if (open[j]) continue;
          // start moving
          next.second.valve = j;
          next.second.remaining = dist2 + 1;
          next.second.free = false;
          go = std::min(go, dist2 + 1);
        }
        else 
        {
          go = std::min(go, es.second.remaining);
        }
      }

      if (minute + go > maxMinute) continue;

      // move there and open it
      int64_t before = per_tick * go;
      next.first.remaining -= go;
      if (elephant) next.second.remaining -= go;

      int64_t after = maxReleased(dists, rates, next, minute + go, maxMinute, open, memo, elephant);
      released = std::max(released, before + after);

      if (!es.second.free || !elephant) break;
    }

    if (!es.first.free) break;
  }

  if (flipped1) open[es.first.valve] = false;
  if (flipped2) open[es.second.valve] = false;

  // what if we do nothing
  released = std::max(released, per_tick * (maxMinute - minute + 1));
  memo[k] = released;
  return released;
}