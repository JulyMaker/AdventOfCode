#include "Guard.h"
#include <algorithm>
#include <numeric>

void Guard::add_sleep_record(int sl, int aw)
{
    asleep_awake.emplace_back(std::make_pair(sl, aw));
}

void Guard::calc_total_sleep()
{
    total_sleep = std::accumulate(std::begin(asleep_awake),
                                  std::end(asleep_awake),
                                  0,
                                  [](int sum, auto aa) {
                                      return sum + aa.second - aa.first;
                                  });
}

void Guard::map_minutes()
{
    for (const auto& aa : asleep_awake) 
        for (int i = aa.first; i < aa.second; ++i)
            ++(mins[i]);
}

void Guard::set_sleepy_min()
{
    auto it = std::max_element(std::begin(mins), std::end(mins));
    sleepy_min = std::distance(std::begin(mins), it);
}
