#include "taskManager.h"
#include <algorithm>
#include <numeric>

Task_mgr::Task_mgr(size_t max_w, size_t num_s, int base_t)
    : max_workers{max_w},
      num_steps{num_s},
      base_tt{base_t},
      pool{std::vector<char>(num_s)}
{
    std::iota(std::begin(pool), std::end(pool), first_token);
}

int Task_mgr::get_task_time(char task) const
{
    return base_tt + 1 + task - first_token;
}

void Task_mgr::assign_task(char t)
{
    workers.push_back(Worker{t, get_task_time(t)});
}

void Task_mgr::advance_time()
{
    std::for_each(std::begin(workers), std::end(workers),
            [](auto& w) { w.dec_time(); });
}

bool Task_mgr::check_workers()
{
    if (workers.size() == 0)
        return true;

    bool change = false;
    for (auto it = std::begin(workers); it != std::end(workers); )
        if (it->time_left <= 0) {
            done.push_back(it->task);
            change = true;
            it = workers.erase(it);
        } else {
            ++it;
        }
    return change;
}

void Task_mgr::review_tasks(const std::vector<Step>& steps)
{
    ready.resize(pool.size());
    std::copy(std::begin(pool), std::end(pool), std::begin(ready));
    pool.clear();

    for (const auto& s : steps) 
    {
        auto dit = std::find(done.begin(), done.end(), s.prereq);
        if (dit == done.end()) 
        {
            auto rit = std::find(ready.begin(), ready.end(),
                                 s.step_token);
            if (rit != ready.end()) 
            {
                ready.erase(rit);
                pool.push_back(s.step_token);
            }
        }
    }

    for (auto it = std::begin(ready); it != ready.end() && workers.size() < max_workers; )
    {
      assign_task(*it);
      ready.erase(it);
      it = ready.begin();
      //++it;
      //ready.erase(it-1);
      //ready.pop_back();
    }

    //std::sort(std::rbegin(ready), std::rend(ready));
    //for (auto it = std::rbegin(ready); it != ready.rend() && workers.size() < max_workers; ) 
    //{
    //    assign_task(*it);
    //    ++it;
    //    ready.pop_back();
    //
    //    auto itAux = std::rend(ready);
    //}

    std::sort(std::rbegin(ready), std::rend(ready));
    for (const auto c : ready)
        pool.push_back(c);
    ready.clear();
}

int Task_mgr::run(const std::vector<Step>& steps)
{
    int total_time = 0;

    while (!tasks_complete()) 
    {
        if (check_workers())
            review_tasks(steps);

        if (!tasks_complete()) 
        {
            advance_time();
            ++total_time;
        }
    }

    return total_time;
}

std::string Task_mgr::get_order_string() const
{
    return std::string{done.begin(), done.end()};
}