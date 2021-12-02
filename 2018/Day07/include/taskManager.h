#include <vector>
#include <list>

struct Step
{
  char prereq;
  char step_token;
};

struct Worker 
{
    char task = '\0';
    int time_left = 0;
    void dec_time() { --time_left; }
};

class Task_mgr 
{
public:
    Task_mgr(size_t max_w, size_t num_s, int base_t = 0);

    std::string get_order_string() const;

    int  run(const std::vector<Step>& steps);

private:
    int  get_task_time(char t) const;
    bool tasks_complete() const { return done.size() == num_steps; }

    void assign_task(char t);
    void advance_time();
    bool check_workers();
    void review_tasks(const std::vector<Step>& steps);

    const char    first_token = 'A';
    const size_t  max_workers;  // max workers
    const size_t  num_steps;    // number of tasks
    const int     base_tt;      // base task time
    std::vector<char> done;
    std::vector<char> ready;
    std::vector<char> pool;
    std::list<Worker> workers;
};