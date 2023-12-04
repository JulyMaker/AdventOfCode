#include <days.h>

void getCard(const std::vector<std::string>& scratchcards, const int id, std::vector<int>& win, std::vector<int>& numbers)
{
    win = splitI(scratchcards[id * 3 + 1], " ");
    numbers = splitI(scratchcards[id * 3 + 2], " ");
    std::sort(win.begin(), win.end());
    std::sort(numbers.begin(), numbers.end());
}

uint64_t adventDay04P12023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    std::vector<int> win, numbers;
    std::vector<std::string> cards = parseInputReg(input, "Card .*: (.*) \\| (.*)");
    for (int cardId= 0; cardId < cards.size()/3; cardId++)
    {
        getCard(cards, cardId, win, numbers);

        std::vector<int> intersection;
        std::set_intersection(win.begin(), win.end(), numbers.begin(), numbers.end(),
            std::back_inserter(intersection));

        score+= (intersection.size() == 0)? 0 : std::pow(2, intersection.size()-1);
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}


uint64_t adventDay04P22023(std::ifstream& input)
{
    uint64_t score = 0;
    std::string result;

    std::vector<int> win, numbers;
    std::vector<std::string> scratchcards = parseInputReg(input, "Card .*: (.*) \\| (.*)");
    std::vector<int> cardsCopies = std::vector<int>(scratchcards.size()/3, 1);
    
    for(int cardId= 0; cardId < cardsCopies.size(); cardId++)
    {
        getCard(scratchcards, cardId, win, numbers);

        std::vector<int> intersection;
        std::set_intersection(win.begin(), win.end(), numbers.begin(), numbers.end(),
            std::back_inserter(intersection));


       for (int times = 1; times <= intersection.size(); times++)
       {
           cardsCopies[cardId + times]+= cardsCopies[cardId];
       }

       score+= cardsCopies[cardId];
    }

    result = std::to_string(score);
    std::cout << "El resultado es: " << result << std::endl;
    return score;
}
