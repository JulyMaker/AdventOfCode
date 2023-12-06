#include <days.h>

uint64_t adventDay06P12023(std::ifstream& input)
{
    uint64_t score = 1;

    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<int> time     = splitI(parseInputReg(in[0], "Time:(.*)")[1], " ");
    std::vector<int> distances = splitI(parseInputReg(in[1], "Distance:(.*)")[1], " ");

    for (int t= 0; t < time.size(); t++)
    {
        int winTimes = 0;
        const bool par = time[t] % 2 == 0;
        const int limit = (par) ? (time[t]/2) + 1 : (time[t] + 1)/2; // Repeat half times
        for (int i = 1; i < limit; i++)
        {
            int distance = i * (time[t] - i);
            if (distance > distances[t]) winTimes++;
        }

        winTimes = (winTimes * 2) - ((par) ? 1 : 0);
        score*= winTimes;
    }
    

    return score;
}

uint64_t adventDay06P22023(std::ifstream& input)
{
    uint64_t score = 1;
    std::vector<std::string> in = parseInput(input, '\n');
    std::string time = parseInputReg(in[0], "Time:(.*)")[1];
    time.erase(std::remove_if(time.begin(), time.end(), ::isspace), time.end());
    uint64_t t = std::stoll(time);

    std::string distances = parseInputReg(in[1], "Distance:(.*)")[1];
    distances.erase(std::remove_if(distances.begin(), distances.end(), ::isspace), distances.end());
    uint64_t d = std::stoll(distances);

    int winTimes = 0;
    const bool par = t % 2 == 0;
    const int limit = (par) ? (t / 2) + 1 : (t + 1) / 2; // Repeat half times
    for (uint64_t i = 1; i < limit; i++)
    {
        uint64_t distance = i * (t - i);
        if (distance > d) winTimes++;
    }

    winTimes = (winTimes * 2) - ((par) ? 1 : 0);
    score *= winTimes;

    return score;
}