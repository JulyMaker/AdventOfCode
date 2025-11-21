#include <days.h>

struct Points
{
    int64_t x, y;

    Points operator+(Points p2)
    {
        return { x + p2.x, y + p2.y };
    }
    Points operator+(Points p2) const
    {
        return { x + p2.x, y + p2.y };
    }

    void operator+=(Points p2)
    {
        x = x + p2.x;
        y = y + p2.y;
    }

    Points operator-(const Points p2) const
    {
        return { x - p2.x, y - p2.y };
    }

    bool operator==(Points p2)
    {
        return (x == p2.x) && (y == p2.y);
    }
    bool operator==(const Points p2) const
    {
        return (x == p2.x) && (y == p2.y);
    }

    bool operator<(const Points& p2)
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }

    const bool operator<(const Points& p2) const
    {
        return (x == p2.x) ? y < p2.y : x < p2.x;
    }
};

using std::views::iota;
std::array<std::string_view const, 4> keypadLayout = { "789", "456", "123", " 0A" };
std::array<std::string_view const, 2> keypadLayout2 = { " ^A", "<v>" };

std::array<Points, 128> keypadFindPositions(auto& layout)
{
    std::array<Points, 128> positions;
    for (auto const y : iota(0, static_cast<int64_t>(layout.size()))) 
    {
        auto const& scanline = layout[y];
        for (auto const x : iota(0, static_cast<int64_t>(scanline.size()))) 
            positions[scanline[x]] = Points{ x, y };
    }
    return positions;
}

auto keypadPositions = keypadFindPositions(keypadLayout);
auto keypadPositions2 = keypadFindPositions(keypadLayout2);

static std::map<char, Points> const dirVec = { {'^', {0, -1}}, {'<', {-1, 0}}, {'v', {0, 1}}, {'>', {1, 0}} };

auto isValidMove(auto const& kpLayout, auto const& kpStart, auto const& moveString) 
{
    auto kpPos = kpStart;
    for (auto const key : moveString) 
    {
        kpPos += dirVec.at(key);
        if (kpLayout[kpPos.y][kpPos.x] == ' ')
            return false;
    }
    return true;
}

auto getMoves(auto const& layout, Points const& srcPos, Points const& dstPos) 
{
    auto const moveDiff = dstPos - srcPos;
    std::string horizMove{}, verticalMove{};
    std::set<std::string> moves;

    if (moveDiff.x > 0)
        horizMove = std::string{ ">>###", static_cast<size_t>(moveDiff.x) };
    else
        horizMove = std::string{ "<<###", static_cast<size_t>(-moveDiff.x) };


    if (moveDiff.y > 0)
        verticalMove = std::string{ "vvv##", static_cast<size_t>(moveDiff.y) };
    else
        verticalMove = std::string{ "^^^##", static_cast<size_t>(-moveDiff.y) };


    if (isValidMove(layout, srcPos, horizMove + verticalMove))
        moves.insert(horizMove + verticalMove + 'A');

    if (isValidMove(layout, srcPos, verticalMove + horizMove))
        moves.insert(verticalMove + horizMove + 'A');

    // for (auto const &m : moves) {
    //     fmt::print("{} ", m);
    // }
    // fmt::println("");
    return moves;
}

std::map<std::pair<std::string, int64_t>, int64_t> memofFkc{};
int64_t findKeypadCost_(std::string const& line, int64_t const depth);
int64_t findKeypadCost(std::string const& line, int64_t const depth) 
{
    if (auto resultIt = memofFkc.find({ line, depth }); resultIt != memofFkc.end()) {
        return resultIt->second;
    }
    auto const result = findKeypadCost_(line, depth);
    memofFkc[{line, depth}] = result;
    return result;
}

int64_t findKeypadCost_(std::string const& line, int64_t const depth) 
{
    if (depth == 0)
        return int64_t{ 1 };

    int64_t cost = 0;
    char src = 'A';
    for (auto const dst : line) 
    {
        auto moveList = getMoves(keypadLayout2, keypadPositions2[src], keypadPositions2[dst]);
        //if (moveList.size() == 0)
        //    fmt::println("No move in {} from {} to {}", line, src, dst);

        int64_t minCost = std::numeric_limits<int64_t>::max();
        for (auto const& move : moveList)
            minCost = std::min(minCost, findKeypadCost(move, depth - 1));

        cost += minCost;
        src = dst;
    }

    return cost;
}

auto findNumpadCost(std::string const& line, auto const depth) 
{
    int64_t cost = 0;
    char src = 'A';
    for (auto const dst : line) 
    {
        auto moveList = getMoves(keypadLayout, keypadPositions[src], keypadPositions[dst]);

        int64_t minCost = std::numeric_limits<int64_t>::max();
        for (auto const& move : moveList)
            minCost = std::min(minCost, findKeypadCost(move, depth));

        cost += minCost;
        src = dst;
    }
    return cost;
}

auto findCost(std::string const& line, auto const depth) 
{
    int64_t value;
    std::from_chars(line.data(), line.data() + line.size(), value, 10);
    auto const result = findNumpadCost(line, depth);
    // std::cout << "Complexity of \"{}\" is {} * {} = {}", line, result, value, result * value) << std::endl;
    return result * value;
}

uint64_t adventDay21P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    for (auto const& line : in) 
    {
        auto const result = findCost(line, 2 + 1);
        score += result;
    }

    return score;
}


uint64_t adventDay21P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    for (auto const& line : in) 
    {
        auto const result = findCost(line, 25 + 1);
        score += result;
    }

    return score;
}