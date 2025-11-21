#include <days.h>

struct Rules 
{
    bool complete = false;
    int64_t toSplit = -1;
    std::pair<int64_t, int64_t> splitNumbers;
    int64_t number = -1;

    bool operator<(const Rules& b) const
    {
        if (toSplit < b.toSplit) return true;
        if (toSplit > b.toSplit) return false;
        if (splitNumbers.first < b.splitNumbers.first) return true;
        if (splitNumbers.first > b.splitNumbers.first) return false;
        if (splitNumbers.second < b.splitNumbers.second) return true;
        if (splitNumbers.second > b.splitNumbers.second) return false;
        if (number < b.number) return true;
        return false;
    }
};

int64_t digitsCount(int64_t number) 
{
    int64_t counter = 0;
    while (number != 0) 
    {
        number /= 10;
        ++counter;
    }

    return counter;
}

std::pair<int64_t, int64_t> splitNumber(int64_t number, const uint8_t digitsCount) 
{
    const uint8_t half = digitsCount / 2;
    std::pair<int64_t, int64_t> splitNumbers = { 0, 0 };
    int64_t tensSecond = static_cast<int64_t>(std::pow(10, digitsCount - 1));

    splitNumbers.second = number % static_cast<int64_t>(std::pow(10, half));

    for (uint8_t digits = 0; digits < half; ++digits)
    {
        splitNumbers.first *= 10;
        splitNumbers.first += number / tensSecond;
        number -= (splitNumbers.first % 10) * tensSecond;
        tensSecond /= 10;
    }

    return splitNumbers;
}


Rules startRule(int64_t number) 
{
    uint8_t iterations = 0;
    uint8_t digits;
    int64_t sourceNumber = number;

    if (!number) 
    {
        iterations = 1;
        number = 1;
    }

    while ((digits = digitsCount(number)) % 2)
    {
        number *= 2024;
        ++iterations;
    }

    return Rules{
            .complete = true,
            .toSplit = iterations,
            .splitNumbers = splitNumber(number, digits),
            .number = sourceNumber
    };
}


uint64_t adventDay11P12025(std::ifstream& input)
{
    uint64_t score = 0;

    int TIMES = 25;
    std::vector<uint64_t> in = splitUInt(parseLine(input), " ");

    std::unordered_map<int64_t, Rules> conclusions;
    std::map<Rules, size_t> data;

    for (auto n : in)
    {
        auto& r = conclusions[n];
        if (!r.complete)
            r = startRule(n);

        ++data[r];
    }

    while (TIMES > 0)
    {
        int64_t forwardIt = data.begin()->first.toSplit + 1;
        std::map<Rules, size_t> newData;
        for (auto& [r, count] : data) 
        {
            if (r.toSplit - forwardIt < 0)
            {
                auto& newR1 = conclusions[r.splitNumbers.first];
                auto& newR2 = conclusions[r.splitNumbers.second];
                if (!newR1.complete) newR1 = startRule(r.splitNumbers.first);
                if (!newR2.complete) newR2 = startRule(r.splitNumbers.second);
                newData[newR1] += count;
                newData[newR2] += count;
            }
            else 
            {
                newData[{
                    .complete = true,
                    .toSplit = static_cast<uint8_t>(r.toSplit - forwardIt),
                    .splitNumbers = r.splitNumbers,
                    .number = (r.number == 0) ? 1 : r.number * 2024
                }] += count;
            }
        }

        TIMES -= forwardIt;
        std::swap(data, newData);
    }

    score+= std::transform_reduce(data.begin(), data.end(), 0ull, std::plus<>{}, [](auto& val) {
                                   return val.second;
                                 });

    return score;
}

uint64_t adventDay11P22025(std::ifstream& input)
{
    uint64_t score = 0;
	
    int TIMES = 75;
    std::vector<uint64_t> in = splitUInt(parseLine(input), " ");

    std::unordered_map<int64_t, Rules> conclusions;
    std::map<Rules, size_t> data;

    for (auto n : in)
    {
        auto& r = conclusions[n];
        if (!r.complete)
            r = startRule(n);

        ++data[r];
    }

    while (TIMES > 0)
    {
        int64_t forwardIt = data.begin()->first.toSplit + 1;
        std::map<Rules, size_t> newData;
        for (auto& [r, count] : data)
        {
            if (r.toSplit - forwardIt < 0)
            {
                auto& newR1 = conclusions[r.splitNumbers.first];
                auto& newR2 = conclusions[r.splitNumbers.second];
                if (!newR1.complete) newR1 = startRule(r.splitNumbers.first);
                if (!newR2.complete) newR2 = startRule(r.splitNumbers.second);
                newData[newR1] += count;
                newData[newR2] += count;
            }
            else
            {
                newData[{
                    .complete = true,
                        .toSplit = static_cast<uint8_t>(r.toSplit - forwardIt),
                        .splitNumbers = r.splitNumbers,
                        .number = (r.number == 0) ? 1 : r.number * 2024
                }] += count;
            }
        }

        TIMES -= forwardIt;
        std::swap(data, newData);
    }

    score += std::transform_reduce(data.begin(), data.end(), 0ull, std::plus<>{}, [](auto& val) {
        return val.second;
        });


    return score;
}