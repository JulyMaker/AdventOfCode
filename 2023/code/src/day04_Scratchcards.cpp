#include <days.h>

uint64_t adventDay04P12023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    std::vector<std::string> cards = parseInputReg(input, "Card .*: (.*) \\| (.*)");
    for (int i= 0; i < cards.size()-2; i+= 3)
    {
        std::vector<int> win = splitI(cards[i + 1]," ");
        std::sort(win.begin(), win.end());
        std::vector<int> numbers = splitI(cards[i + 2], " ");
        std::sort(numbers.begin(), numbers.end());

        int points = 0;
        int winPointer = 0;
        for (auto& num : numbers)
        {
            while ( (winPointer < win.size()) && num > win[winPointer])
                winPointer++;

            if (winPointer > win.size() - 1) break;

            if (num == win[winPointer])
            {
                points = (points == 0) ? 1 : points * 2;
                winPointer++;
            } 
        }
        score+= points;
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}

using Card  = std::tuple<int, std::vector<int>, std::vector<int>>; // Copies, winNumbers, gameNumbers
using Cards = std::vector<Card>;

void getCard(const std::vector<std::string>& scratchcards, const int id, std::vector<int>& win, std::vector<int>& numbers)
{
    win = splitI(scratchcards[id + 1], " ");
    std::sort(win.begin(), win.end());
    numbers = splitI(scratchcards[id + 2], " ");
    std::sort(numbers.begin(), numbers.end());
}

uint64_t adventDay04P22023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    Cards cards;
    int cardId = 0;
    std::vector<int> win, numbers;

    std::vector<std::string> scratchcards = parseInputReg(input, "Card\\s+\\d+: (.*) \\| (.*)");

    for(int i=0; i < scratchcards.size() - 2; i+= 3)
    {
        getCard(scratchcards, i, win, numbers);
        Card c = { 1, win, numbers };
        cards.push_back(c);
    }

    
    for(int cardId= 0; cardId < cards.size(); cardId++)
    {
        win = std::get<1>(cards[cardId]);
        numbers = std::get<2>(cards[cardId]);

       int winTimes = 0;
       int winPointer = 0;
       for (auto& num : numbers)
       {
           while ((winPointer < win.size()) && num > win[winPointer])
               winPointer++;
       
           if (winPointer > win.size() - 1) break;
       
           if (num == win[winPointer])
           {
               winTimes++;
               winPointer++;
           }
       }

       for (int times = 1; times <= winTimes; times++)
       {
          std::get<0>(cards[cardId + times])+= std::get<0>(cards[cardId]);
       }

       score+= std::get<0>(cards[cardId]);
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}

//std::get<0>(tpl) = 1;
//std::get<1>(tpl) = 2;
//std::get<2>(tpl) = 3;