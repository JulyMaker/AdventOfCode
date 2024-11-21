#include <days.h>


using Cache = std::unordered_map<std::pair<std::string, std::vector<int>>, uint64_t>;

uint64_t arrangements(std::string spring, std::vector<int> numbers, Cache& cache)
{
    if (spring.size() == 0)
        return (numbers.size() == 0) ? 1 : 0;

    if (cache.find({ spring, numbers }) != cache.end()) return cache[{spring, numbers}];
    
    if (spring[0] == '.')
    {
        spring.erase(spring.begin());
        return arrangements(spring, numbers, cache);
    }

    if (spring[0] == '?')
    {
        spring[0] = '.';
        std::string s1 = spring;
        spring[0] = '#';
        std::string s2 = spring;

        uint64_t result = arrangements(s2, numbers, cache);
        cache[{s2, numbers}] = result;

        return arrangements(s1, numbers, cache) + result ;
    }
     
    if (spring[0] == '#')
    {
        if (numbers.size() == 0) return 0;
        if (spring.size() < numbers[0]) return 0;

        // Case contain .
        std::string nCharacters = spring.substr(0, numbers[0]);
        size_t posicion = nCharacters.find('.');
        if (posicion != std::string::npos) return 0;
 
        if (numbers.size() > 1)
        {
            if ((spring.size() < (numbers[0] + 1)) || spring[numbers[0]] == '#') return 0;

            std::string nCharacters = spring.substr(numbers[0] + 1, spring.size());
            numbers.erase(numbers.begin());

            uint64_t result = arrangements(nCharacters, numbers, cache);
            cache[{nCharacters, numbers}] = result;

            return result;
        }
        else{
            std::string nCharacters = spring.substr(numbers[0], spring.size());
            numbers.erase(numbers.begin());
            return arrangements(nCharacters, numbers, cache);
        }
    }
}

uint64_t adventDay12P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInputReg(input,"(.*) (.*)");
    std::vector<std::string> springs;
    std::vector<std::vector<int>> numbers;

    for (int i=0; i<in.size(); i+= 3)
    {
        springs.push_back(in[i + 1]);
        numbers.push_back(splitI(in[i + 2], ","));
    }

    Cache cache;
    for (int springN = 0; springN < springs.size(); springN++)
        score += arrangements(springs[springN], numbers[springN], cache);
    
    return score;
}

uint64_t adventDay12P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInputReg(input, "(.*) (.*)");
    std::vector<std::string> springs;
    std::vector<std::vector<int>> numbers;

    for (int i = 0; i < in.size(); i += 3)
    {
        std::string springFive= in[i + 1];
        std::vector<int> numberFive = splitI(in[i + 2], ",");
        std::vector<int> auxNum = numberFive;

        for (int j = 0; j < 4; j++)
        {
            springFive += "?" + in[i + 1];
            numberFive.insert(numberFive.end(), auxNum.begin(), auxNum.end());
        }

        springs.push_back(springFive);
        numbers.push_back(numberFive);
    }


    Cache cache;
    for (int springN = 0; springN < springs.size(); springN++)
        score += arrangements(springs[springN], numbers[springN], cache);

    return score;
}