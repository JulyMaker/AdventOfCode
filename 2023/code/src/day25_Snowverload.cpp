#include <days.h>
#include <ansiColors.h>

// From https://en.wikipedia.org/wiki/Stoer-Wagner_algorithm
auto globalMinCut(std::vector<std::vector<int>>& mat) 
{
    std::pair<int, std::vector<int>> best = { std::numeric_limits<int>::max(), {} };
    int n = mat.size();
    std::vector<std::vector<int>> co(n);

    for (int i = 0; i < n; i++)
        co[i] = { i };

    for (int ph = 1; ph < n; ph++) 
    {
        std::vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
            w[t] = std::numeric_limits<int>::min();
            s = t, t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, { w[t] - mat[t][t], co[t] });
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = std::numeric_limits<int>::min();
    }

    return best;
}

uint64_t adventDay25P12023(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInputReg(input, "(.*): (.*)");
    std::vector<std::pair<int, int>>connections;
    std::map<std::string, int> nameMap;

    auto getIndex = [&nameMap](const std::string& s)
    {
        if (nameMap.find(s) != nameMap.cend())
            return nameMap[s];
        int index = nameMap.size();
        nameMap[s] = index;

        return index;
    };

    for (int i = 0; i < in.size(); i += 3)
    {
        std::string name = in[i + 1];
        int baseIndex = getIndex(name);
        for (auto dest : splitS(in[i + 2], " "))
            connections.emplace_back(baseIndex, getIndex(dest));
    }

    std::vector<std::vector<int>> adj(nameMap.size(), std::vector<int>(nameMap.size(), 0));
    for (const auto& p : connections)
        adj[p.first][p.second] = adj[p.second][p.first] = 1;

    auto result = globalMinCut(adj);
    score= result.second.size() * (nameMap.size() - result.second.size());

    return score;
}

uint64_t adventDay25P22023(std::ifstream& input)
{
    uint64_t score = 0;

    paintAdventCalendar2023();
    std::cout << std::endl;
    std::cout << "        Happy Advent of Code 2023!" << std::endl;

    return score;
}