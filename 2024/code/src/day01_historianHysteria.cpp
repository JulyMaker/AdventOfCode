#include <days.h>


uint64_t adventDay01P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<int> leftList;
    std::vector<int> rightList;

    int leftnNum, rightNum;
    while (input >> leftnNum >> rightNum) 
    {
        leftList.push_back(leftnNum);
        rightList.push_back(rightNum);
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for (int i=0; i < leftList.size(); i++)
        score += std::abs(leftList[i] - rightList[i]);

    return score;
}

uint64_t adventDay01P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<int> leftList;
    std::unordered_map<int, int> count;

    int leftnNum, rightNum;
    while (input >> leftnNum >> rightNum)
    {
        leftList.push_back(leftnNum);
        count[rightNum]++;
    }
        
    for (int num : leftList)
    {
        int times = 0;
        if (count.find(num) != count.end())
            times = count[num];
        
        score += num * times;
    }

    return score;
}