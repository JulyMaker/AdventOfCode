#include <days.h>

using std::views::iota;

struct Gate 
{
    std::string src1, src2;
    std::string gate;
    std::string dest;

    bool produce(auto& wires) const 
    {
        if (wires.contains(src1) and wires.contains(src2)) 
        {
            if (gate == "AND") 
            {
                wires[dest] = wires[src1] & wires[src2];
                return true;
            }
            else if (gate == "OR") 
            {
                wires[dest] = wires[src1] | wires[src2];
                return true;
            }
            else if (gate == "XOR") 
            {
                wires[dest] = wires[src1] ^ wires[src2];
                return true;
            }
        }
        return false;
    }
};

bool step1(auto& wires, auto& gates) 
{
    bool toggled = false;
    auto gateIt = gates.begin();
    while (gateIt != gates.end()) 
    {
        if (gateIt->produce(wires)) 
        {
          toggled = true;
          gateIt = gates.erase(gateIt);
        }
        else
          ++gateIt;
    }
    return toggled;
}

std::string regName(char const reg, int64_t const bit) 
{
    return std::format("{}{:02d}", reg, bit);
}

constexpr int64_t wireValue(auto const& wires, char const wireName = 'z') 
{
    int64_t result = 0;
    for (auto const bit : iota(0)) 
    {
        auto const outname = regName(wireName, bit);
        if (!wires.contains(outname))
            break;

        result |= (int64_t{ 1 } << bit) * wires.at(outname);
    }
    return result;
}

int64_t evaluate(auto wires, auto const& gates) 
{
    std::list<Gate> unchecked{};
    for (auto const& [name, gate] : gates) 
    {
        unchecked.push_back(gate);
    }

    while (step1(wires, unchecked) && !wires.empty()) { }

    return wireValue(wires);
}

uint64_t adventDay24P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInput(input, '\n');

    std::map<std::string, int64_t> wires;
    std::vector<Gate> gates;
    std::map<std::string, Gate> gatesByOutput;

    bool isWire = true;
    for (auto& line : in)
    {
        if (isWire)
        {
            std::vector<std::string> wire = parseInputReg(line, R"(([a-zA-Z][0-9]+): ([0-9]+))");
            if (wire.size() > 0)
                wires[wire[1]] = std::stoll(wire[2]);
            else
                isWire = false;
                
        }

        if(!isWire)
        {
            std::vector<std::string> gate = splitS(line, " -> ");

            gates.emplace_back(gate[0], gate[2], gate[1], gate[3]);
            gatesByOutput.emplace(gate[3], gates.back());
        }
    }

    score = evaluate(wires, gatesByOutput);
   
    return score;
}


std::set<std::string> swappedWires{};


bool testBit(auto& gatesByOutput, int64_t const digit) 
{
    if (digit == 0) // Cannot test bit 0, assume it is correct
        return true;

    for (auto const testpattern : iota(0, 3 * 3)) 
    {
        auto const xp = (testpattern % 3) == 0 ? 0 : 1;
        auto const yp = (testpattern % 3) == 2 ? 1 : 0;
        auto const xn = (testpattern / 3) == 0 ? 0 : 1;
        auto const yn = (testpattern / 3) == 2 ? 1 : 0;

        std::map<std::string, int64_t> inputs;
        // set up carry from digit-2 (only digit-2 is needed to be set,
        // but other wires need to be present, too)
        if (digit > 1) 
        {
            for (auto const bit : iota(0, digit - 1)) 
            {
                inputs[regName('x', bit)] = 1;
                inputs[regName('y', bit)] = 1;
            }
        }

        inputs[regName('x', digit - 1)] = xp;
        inputs[regName('y', digit - 1)] = yp;
        inputs[regName('x', digit)] = xn;
        inputs[regName('y', digit)] = yn;

        auto const xvalue = wireValue(inputs, 'x');
        auto const yvalue = wireValue(inputs, 'y');
        auto const sumdigit = (xvalue + yvalue) & (int64_t{ 1 } << digit);
        auto const zdigit = evaluate(inputs, gatesByOutput) & (int64_t{ 1 } << digit);

        if (sumdigit != zdigit)
            return false;
    }

    return true;
}

auto connectedTo(auto const& gatesByOutput, int64_t const digit) 
{
    std::queue<std::string> frontier{};
    std::set<std::string> visited{};
    frontier.push(regName('z', digit));
    visited.insert(regName('z', digit));
    while (!frontier.empty()) 
    {
        auto const currentWire = frontier.front();
        frontier.pop();
        if (gatesByOutput.contains(currentWire)) 
        {
            auto const& gate = gatesByOutput.at(currentWire);

            if (!visited.contains(gate.src1)) 
            {
                frontier.push(gate.src1);
                visited.insert(gate.src1);
            }

            if (!visited.contains(gate.src2)) 
            {
                frontier.push(gate.src2);
                visited.insert(gate.src2);
            }
        }
    }

    return visited;
}

auto outputConnections(auto const& gatesByOutput) 
{
    std::set<std::string> seenWires{};
    std::vector<std::set<std::string>> result{};
    for (auto const digit : iota(0, 45)) 
    {
        auto wires = connectedTo(gatesByOutput, digit);
        auto currentOutput = regName('z', digit);
        auto& currentLevel = result.emplace_back();
        for (auto const& wire : wires) 
        {
            if (!seenWires.contains(wire)) 
            {
                seenWires.insert(wire);
                currentLevel.insert(wire);
            }
        }
    }

    return result;
}

void swapWires(auto& gatesByOutput, auto const& w1, auto const w2) 
{
    std::swap(gatesByOutput[w1].dest, gatesByOutput[w2].dest);
    std::swap(gatesByOutput[w1], gatesByOutput[w2]);
}

void unswapWires(auto& gatesByOutput, auto const& w1, auto const w2) 
{
    std::swap(gatesByOutput[w1].dest, gatesByOutput[w2].dest);
    std::swap(gatesByOutput[w1], gatesByOutput[w2]);
}

bool trySwapWires(auto& gatesByOutput, auto const digit, auto const& list1, auto const& list2) 
{
    for (auto const& wire1 : list1) 
    {
        for (auto const& wire2 : list2) 
        {
            if (wire1 == wire2)
                continue;

            swapWires(gatesByOutput, wire1, wire2);
            if (testBit(gatesByOutput, digit)) 
            {
                swappedWires.insert(wire1);
                swappedWires.insert(wire2);
                return true;
            }
            unswapWires(gatesByOutput, wire1, wire2);
        }
    }

    return false;
}

uint64_t adventDay24P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::map<std::string, int64_t> wires;
    std::vector<Gate> gates;
    std::map<std::string, Gate> gatesByOutput;

    bool isWire = true;
    for (auto& line : in)
    {
        if (isWire)
        {
            std::vector<std::string> wire = parseInputReg(line, R"(([a-zA-Z][0-9]+): ([0-9]+))");
            if (wire.size() > 0)
                wires[wire[1]] = std::stoll(wire[2]);
            else
                isWire = false;

        }

        if (!isWire)
        {
            std::vector<std::string> gate = splitS(line, " -> ");

            gates.emplace_back(gate[0], gate[2], gate[1], gate[3]);
            gatesByOutput.emplace(gate[3], gates.back());
        }
    }

    score = evaluate(wires, gatesByOutput);

    // assume bit 0 is connected corretly (verified by looking)
    for (auto const digit : iota(1, 45)) 
    {
        if (testBit(gatesByOutput, digit))
            continue;

        auto firstConnections = outputConnections(gatesByOutput);
        for (auto const swapWithLevel : iota(digit, 45)) {
            if (trySwapWires(gatesByOutput, digit, firstConnections[digit],
                firstConnections[swapWithLevel])) {
                break;
            }
        }
    }

    if (swappedWires.size() > 0) {
        std::cout << "Swapped wires: " << *swappedWires.begin();
        for (auto const& wire : swappedWires | std::views::drop(1)) 
            std::cout << "," << wire;

        std::cout << std::endl;
    }
    else
        std::cout << "Can't swap wires." << std::endl;

    return score;
}