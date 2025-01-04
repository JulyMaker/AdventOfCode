#include <days.h>

size_t prune(size_t num) { return num % 16777216; }
size_t mix(size_t num_a, size_t num_b) { return num_a ^ num_b; }

size_t generateNextSecretNumber(size_t secretNumber)
{
    secretNumber = prune(mix(secretNumber, secretNumber * 64));
    secretNumber = prune(mix(secretNumber, secretNumber / 32));
    secretNumber = prune(mix(secretNumber, secretNumber * 2048));

    return secretNumber;
}

size_t generateSecretNumbers(size_t secretNumber, const int n)
{
    for (int i = 0; i < n; i++)
        secretNumber = generateNextSecretNumber(secretNumber);

    return secretNumber;
}

uint64_t adventDay22P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    for (auto& num : in)
        score += generateSecretNumbers(std::stoull(num), 2000);

    return score;
}

int ones(size_t num) { return (int)(num % 10); }

size_t nextSecretNum(size_t secret) 
{
    secret = prune(mix(secret << 6, secret));
    secret = prune(mix(secret >> 5, secret));
    secret = prune(mix(secret << 11, secret));

    return secret;
}

using seq_t = std::array<int, 4>;

struct hasher {
    std::size_t operator()(const seq_t& arr) const {
        return (arr[3] + 9) * (19 * 19 * 19) + (arr[2] + 9) * (19 * 19) + (arr[1] + 9) * 19 + (arr[0] + 9);
    }
};

using seqPriceMap_t = std::unordered_map<seq_t, uint64_t, hasher>;

uint64_t adventDay22P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');
    std::vector<size_t> numbers;

    for (auto& num : in)
        numbers.push_back(std::stoull(num));
     
    seq_t changeSeq;
    seqPriceMap_t seqPriceMax;

    for (size_t number : numbers) 
    {
        seqPriceMap_t seqPriceMap;

        size_t secret = number;
        for (int i = 0; i < 2000; ++i) 
        {
            size_t prevSecret = secret;
            secret = nextSecretNum(secret);

            int price_i = ones(secret);
            changeSeq[i % 4] = ones(secret) - ones(prevSecret);

            if (i >= 3) 
            {
                seq_t seq{ changeSeq[(i - 3) % 4], changeSeq[(i - 2) % 4], changeSeq[(i - 1) % 4], changeSeq[i % 4] };
                if (!seqPriceMap.count(seq))
                    seqPriceMap[seq] = price_i;
            }
        }

        for (auto& [seq, price] : seqPriceMap)
        {
            seqPriceMax[seq] += price;
            score = std::max(score, seqPriceMax[seq]);
        }
    }

    return score;
}