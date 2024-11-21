#include <days.h>

struct TwoValues
{
    std::string left;
    std::string right;
};

uint64_t adventDay08P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::string path; 
    std::getline(input, path);

    std::vector<std::string> tree = parseInputReg(input, "(.*) = \\((\\w+), (.*)\\)");
    std::map<std::string, TwoValues> parserPath;
    for (int i=0; i<tree.size(); i+= 4)
    {
        parserPath[tree[i + 1]] = { tree[i + 2], tree[i + 3] };
    }

    int index = 0;
    std::string state = "AAA";

    while (state != "ZZZ")
    {
        state = (path[index] == 'L') ? parserPath[state].left : parserPath[state].right;

        score++;
        index = (++index % path.size());
    }

    return score;
}


uint64_t adventDay08P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::string path;
    std::getline(input, path);

    std::vector<std::string> tree = parseInputReg(input, "(.*) = \\((\\w+), (.*)\\)");
    std::map<std::string, TwoValues> parserPath;
    std::vector<std::string> state;
    for (int i = 0; i < tree.size(); i += 4)
    {
        parserPath[tree[i + 1]] = { tree[i + 2], tree[i + 3] };

        if (tree[i + 1][2] == 'A')
            state.push_back(tree[i + 1]);
    }

    
    std::vector<uint64_t> steps;
    
    for (auto& s : state)
    {
        int index = 0;
        uint64_t currentStep = 0;
        while (s[2] != 'Z')
        {
            s = (path[index] == 'L') ? parserPath[s].left : parserPath[s].right;
            
            currentStep++;
            index = (++index % path.size());
        }

        
        steps.push_back(currentStep);
    }
    
    score = std::reduce(steps.begin() + 1, steps.end(), steps[0], std::lcm<uint64_t, uint64_t>);

    return score;
}