#include <days.h>

int hash(std::string label)
{
    int stringHash = 0;
    for (auto& c : label)
        stringHash = ((stringHash + int(c)) * 17) % 256;

    return stringHash;
}

uint64_t adventDay15P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= splitS(parseLine(input), ",");
    for (auto& line : in)
        score += hash(line);
        
    return score;
}

struct Lens
{
    std::string label;
    int length;

    bool operator==(Lens l2) const{
        return label == l2.label;
    }
};

uint64_t adventDay15P22024(std::ifstream& input)
{
    uint64_t score = 0;

    constexpr int TOTALBOXES = 256;
    std::vector<std::string> in = splitS(parseLine(input), ",");
    std::vector<std::vector<Lens>> book(TOTALBOXES);
    
    for (auto& line : in)
    {
        if (line[line.size() - 1] == '-')
        {
            std::string label = line.substr(0, line.size() - 1);
            for(auto& box : book)
                 std::erase_if(box, [&label](Lens const& lens) {return lens.label == label; });
        }
        else
        {
            auto lens = splitS(line, "=");
            int box = hash(lens[0]);

            auto it = std::find(book[box].begin(), book[box].end(), Lens{lens[0], 0});

            if (it != book[box].end())
                it->length = std::stoi(lens[1]);
            else
                book[box].push_back(Lens{lens[0], std::stoi(lens[1])});
        }  
    }

    for (int box = 0; box < book.size(); box++)
        for (int lens = 0; lens < book[box].size(); lens++)
            score += (box + 1) * (lens + 1) * book[box][lens].length;


    return score;
}