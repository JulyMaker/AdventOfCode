#include <days.h>

std::unordered_map<char, int> cardOrder =
{
    {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8},
    {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}
};

struct Card
{
    std::string hand;
    int bid;

    bool operator>(const Card& c2) const 
    {
        for (int i=0; i< hand.size(); i++)
        {
            if (cardOrder[hand[i]] > cardOrder[c2.hand[i]])
                return true;
            else if (cardOrder[hand[i]] < cardOrder[c2.hand[i]])
                return false;
        }

        return false;
    }

    bool operator<(const Card& c2) const
    {
        for (int i = 0; i < hand.size(); i++)
        {
            if (cardOrder[hand[i]] < cardOrder[c2.hand[i]])
                return true;
            else if (cardOrder[hand[i]] > cardOrder[c2.hand[i]])
                return false;
            
        }

        return false;
    }

    bool operator==(const Card& c2) const {
        return hand == c2.hand;
    }

    bool operator!=(const Card& c2) const {
        return hand != c2.hand;
    }
};

uint64_t adventDay07P12023(std::ifstream& input)
{
    uint64_t score = 0;

    const int HANDTYPES = 7;
    std::vector<std::string> cards = parseInputReg(input, "(.*) (\\d+)");
    std::vector<std::vector<Card>> order(HANDTYPES); // High card, One pair, Two pair, Three of a kind, Full house, Four of a kind, Five of a kind
    for (int i = 0; i < cards.size(); i += 3)
    {
        Card card;
        card.hand = cards[i + 1];
        card.bid  = stoi(cards[i + 2]);

        int type = 0;
        std::map<char, int> times;
        for (auto& h : card.hand)
        {
            times[h]++;
        }

        auto iter = times.begin();
        while (iter != times.end()) 
        {
            switch (iter->second)
            {
                case 2: type++;
                    break;
                case 3: type += 3;
                    break;
                case 4: type += 5;
                    break;
                case 5: type += 6;
                    break;
            }
            
            ++iter;
        }

        order[type].push_back(card);
    }

    for(auto& o : order)
        std::sort(o.begin(), o.end());

    uint64_t rank = 1;
    for (auto& ord : order)
    {
        for (auto& card : ord)
        {
            score += rank * card.bid;
            rank++;
        }
    }

    return score;
}

std::unordered_map<char, int> cardOrder2 =
{
    {'A', 14}, {'K', 13}, {'Q', 12}, {'T', 10}, {'9', 9}, {'8', 8},
    {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}, {'J', 1}
};

struct Card2
{
    std::string hand;
    int bid;

    bool operator>(const Card2& c2) const
    {
        for (int i = 0; i < hand.size(); i++)
        {
            if (cardOrder2[hand[i]] > cardOrder2[c2.hand[i]])
                return true;
            else if (cardOrder2[hand[i]] < cardOrder2[c2.hand[i]])
                return false;
        }

        return false;
    }

    bool operator<(const Card2& c2) const
    {
        for (int i = 0; i < hand.size(); i++)
        {
            if (cardOrder2[hand[i]] < cardOrder2[c2.hand[i]])
                return true;
            else if (cardOrder2[hand[i]] > cardOrder2[c2.hand[i]])
                return false;

        }

        return false;
    }

    bool operator==(const Card2& c2) const {
        return hand == c2.hand;
    }

    bool operator!=(const Card2& c2) const {
        return hand != c2.hand;
    }
};

uint64_t adventDay07P22023(std::ifstream& input)
{
    uint64_t score = 0;

    const int HANDTYPES = 7;
    std::vector<std::string> cards = parseInputReg(input, "(.*) (\\d+)");
    std::vector<std::vector<Card2>> order(HANDTYPES); // High card, One pair, Two pair, Three of a kind, Full house, Four of a kind, Five of a kind
    for (int i = 0; i < cards.size(); i += 3)
    {
        Card2 card;
        card.hand = cards[i + 1];
        card.bid = stoi(cards[i + 2]);

        std::map<char, int> times;
        std::tuple<int, char> maxElem = {0, 'J'};
        for (auto& h : card.hand)
        {
            times[h]++;
            if ( (h != 'J') && (times[h] > std::get<0>(maxElem)))
            {
                std::get<0>(maxElem) = times[h];
                std::get<1>(maxElem) = h;
            }
        }
        
        
        int type = 0;
        if (times['J'] != 5)
        {
            //Joockers
            times[std::get<1>(maxElem)] += times['J'];
            times.erase('J');

            auto iter = times.begin();
            while (iter != times.end())
            {
                switch (iter->second)
                {
                   case 2: type++;
                       break;
                   case 3: type += 3;
                       break;
                   case 4: type += 5;
                       break;
                   case 5: type += 6;
                       break;
                }

                ++iter;
            }
        }
        else
            type = 6;
            
        order[type].push_back(card);
    }

    for (auto& o : order)
        std::sort(o.begin(), o.end());

    uint64_t rank = 1;
    for (auto& ord : order)
    {
        for (auto& card : ord)
        {
            score += rank * card.bid;
            rank++;
        }
    }

    return score;
}