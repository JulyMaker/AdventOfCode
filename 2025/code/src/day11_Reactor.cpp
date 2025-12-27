#include <days.h>

using listDevices_t = std::unordered_map<std::string, std::vector<std::string>>;
using memoMap_t = std::unordered_map<std::string, int64_t>;

int64_t evalDevice(const listDevices_t& devices, const std::string& dev_name, const std::string& dest_name,
    memoMap_t& memo_map)
{
    const auto& outputs = devices.at(dev_name);
    int64_t value= 0;
    for (const auto& output : outputs) 
    {
        if (memo_map.contains(output))
            value += memo_map.at(output);
        else if (output == dest_name)
            value++;
        else if (output != "out")
            value += evalDevice(devices, output, dest_name, memo_map);
    }
 
    memo_map.emplace(dev_name, value);

    return value;
}

uint64_t adventDay11P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    listDevices_t devices;

    for (auto& line : in)
    {
        std::istringstream ss(line);
        std::string name;

        ss >> name;
        name.pop_back();

        std::vector<std::string> outputs;
        std::string output;
        while (ss >> output)
            outputs.push_back(output);

        devices.emplace(name, outputs);
    }

    memoMap_t memo_map;
    score = evalDevice(devices, "you", "out", memo_map);


    return score;
}

uint64_t adventDay11P22025(std::ifstream& input)
{
    uint64_t score = 0;
	
    std::vector<std::string> in = parseInput(input, '\n');
    listDevices_t devices;

    for (auto& line : in)
    {
        std::istringstream ss(line);
        std::string name;

        ss >> name;
        name.pop_back();

        std::vector<std::string> outputs;
        std::string output;
        while (ss >> output)
            outputs.push_back(output);

        devices.emplace(name, outputs);
    }

    const std::array<std::array<std::string, 4>, 2> paths{ "svr", "fft", "dac", "out", "svr", "dac", "fft", "out" };

    for (const auto& path : paths) 
    {
        int64_t pathResult= 0;
        memoMap_t memoMap;
        for (auto i = path.rbegin(); i < path.rend() - 1; ++i) 
        {
            pathResult = evalDevice(devices, *(i + 1), *i, memoMap);
            memoMap = memoMap_t();
            memoMap.emplace(*(i + 1), pathResult);
        }
        score += pathResult;
    }

    return score;
}