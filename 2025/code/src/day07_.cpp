#include <days.h>

template <typename FuncT>
bool combinations(std::span<size_t> numbers, size_t res, FuncT&& func, size_t currentRes = 0) 
{
    if (numbers.empty()) return currentRes == res;

    if (combinations(numbers.subspan(1), res, std::plus{}, func(numbers.front(), currentRes))) return true;
    return combinations(numbers.subspan(1), res, std::multiplies{}, func(numbers.front(), currentRes));
}


uint64_t adventDay07P12025(std::ifstream& input)
{
    uint64_t score = 0;
;
    std::vector<std::string> equations = parseInput(input, '\n');
    
    for(auto& equationStr : equations)
    {
        std::vector<std::string> equation = parseInputReg(equationStr, R"((\d+):((?:\s\d+)+))");
        uint64_t result = std::stoll(equation[1]);
        std::vector<uint64_t> nums = splitUInt(equation[2], " ");

        score+= combinations(nums, result, std::plus{}) ? result : 0;
    }

    return score;
}

template <typename T>
struct concatenation 
{
    T operator()(const T& x, const T& y) const 
    {
        auto z = y;
        size_t y_size = 1;
        while (z != 0) 
        {
            z /= 10;
            y_size *= 10;
        }

        return x * y_size + y;
    }
};

template <typename FuncT>
bool combinations2(std::span<size_t> numbers, size_t res, FuncT&& func, size_t currentRes = 0) {
    if (numbers.empty()) return currentRes == res;
    if (combinations2(numbers.subspan(1), res, std::plus{}, func(currentRes, numbers.front()))) return true;
    if (combinations2(numbers.subspan(1), res, std::multiplies{}, func(currentRes, numbers.front()))) return true;
    return combinations2(numbers.subspan(1), res, concatenation<size_t>{}, func(currentRes, numbers.front()));
}

uint64_t adventDay07P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> equations = parseInput(input, '\n');

    for (auto& equationStr : equations)
    {
        std::vector<std::string> equation = parseInputReg(equationStr, R"((\d+):((?:\s\d+)+))");
        uint64_t result = std::stoll(equation[1]);
        std::vector<uint64_t> nums = splitUInt(equation[2], " ");

        score += combinations2(nums, result, std::plus{}) ? result : 0;
    }
    
    return score;
}