#include <days.h>


uint64_t adventDay01P12023(std::ifstream& input)
{
    uint64_t score = 0;

    int64_t sum = 0;

    // To Decimal 
    //std::vector<std::string> in = parseInput(input, '\n');
    //for (auto& s : in)
    //{
    //    int64_t number = 0;
    //    for (int64_t i = s.size() - 1, power = 1; i >= 0; --i, power *= 5)
    //        switch (s[i])
    //        {
    //        case '-': number -= power;     break;
    //        case '=': number -= 2 * power; break;
    //        default:  number += power * (s[i] - '0');
    //        }
    //
    //    sum += number;
    //}
    //
    //// To SNAFU
    std::string result;
    //while (sum)
    //{
    //    char c = '0' + (sum % 5);
    //    bool high = c > '2';
    //    if (high)
    //    {
    //        switch (c)
    //        {
    //        case '3': c = '='; break;
    //        case '4': c = '-'; break;
    //        default:  c = '0';
    //        }
    //    }
    //
    //    result += c;
    //    sum = sum / 5 + high;
    //}
    //
    //std::reverse(result.begin(), result.end());

    std::cout << "El resultado es: " << result << std::endl;
    return score;
}

uint64_t adventDay01P22023(std::ifstream& input)
{
    uint64_t score = 0;

    std::string result;

    std::cout << "El resultado es: " << result << std::endl;
    return score;
}