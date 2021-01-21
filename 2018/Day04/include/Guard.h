#include <vector>

class Guard 
{
public:
    explicit Guard(int i) : id{i}, mins{std::vector<int>(60, 0)}{}

    auto get_aoc_answer()  const -> int { return id * sleepy_min; }
    auto get_id()          const -> int { return id; }
    auto get_total_sleep() const -> int { return total_sleep; }
    auto get_sleepy_min()  const -> int { return sleepy_min; }
    auto get_mins()        const -> const std::vector<int>& { return mins; }

    void add_sleep_record(int sl, int aw);
    void calc_total_sleep();
    void map_minutes();
    void set_sleepy_min();
private:
    int id = 0;
    int total_sleep = 0;
    int sleepy_min = -1;
    std::vector<std::pair<int,int>> asleep_awake;
    std::vector<int> mins;
};