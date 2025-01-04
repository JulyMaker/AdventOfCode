#include <days.h>


uint64_t adventDay23P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::unordered_set<std::string> edges;
    std::unordered_map<std::string, std::unordered_set<std::string>> connections;
    for (auto& line : in)
    {
        std::vector<std::string> nodes = splitS(line, "-");
        edges.insert(nodes[0] + nodes[1]);
        edges.insert(nodes[1] + nodes[0]);
        connections[nodes[0]].insert(nodes[1]);
        connections[nodes[1]].insert(nodes[0]);
    }

    std::vector<std::vector<std::string>> triplets;
    for (auto const& edge : edges) 
    {
        auto const node1 = edge.substr(0, 2);
        auto const node2 = edge.substr(2, 2);

        if (node1 >= node2)
            continue;
 
        for (auto const& node3 : connections[node2]) 
        {
            if (node2 >= node3)
                continue;
 
            if (!edges.contains(node1 + node3))
                continue;

            if (!edges.contains(node2 + node3))
                continue;

            std::vector<std::string> triplet{ node1, node2, node3 };
            triplets.push_back(triplet);
        }
    }


    for (auto const& clique : triplets)
        for (auto const& node : clique)
            if (node[0] == 't') 
            {
                ++score;
                break;
            }


    return score;
}

using std::views::iota;

auto expand(auto const& edges, auto const& connections, auto const& connected) 
{
    std::vector<std::vector<std::string>> expanded;
    for (auto const& clique : connected) 
    {
        auto const lastNode = clique.back();
        for (auto const& newNode : connections.at(lastNode)) 
        {
            if (lastNode >= newNode)
                continue;

            bool connectsToAll = true;
            for (auto const& oldNode : clique) 
            {
                if (!edges.contains(oldNode + newNode)) 
                {
                    connectsToAll = false;
                    break;
                }
            }

            if (connectsToAll) 
            {
                expanded.push_back(clique);
                expanded.back().push_back(newNode);
            }
        }
    }

    return expanded;
}

uint64_t adventDay23P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::unordered_set<std::string> edges;
    std::unordered_map<std::string, std::unordered_set<std::string>> connections;
    for (auto& line : in)
    {
        std::vector<std::string> nodes = splitS(line, "-");
        edges.insert(nodes[0] + nodes[1]);
        edges.insert(nodes[1] + nodes[0]);
        connections[nodes[0]].insert(nodes[1]);
        connections[nodes[1]].insert(nodes[0]);
    }

    std::vector<std::vector<std::string>> triplets;
    for (auto const& edge : edges)
    {
        auto const node1 = edge.substr(0, 2);
        auto const node2 = edge.substr(2, 2);

        if (node1 >= node2)
            continue;

        for (auto const& node3 : connections[node2])
        {
            if (node2 >= node3)
                continue;

            if (!edges.contains(node1 + node3))
                continue;

            if (!edges.contains(node2 + node3))
                continue;

            std::vector<std::string> triplet{ node1, node2, node3 };
            triplets.push_back(triplet);
        }
    }

    auto& connected = triplets;
    int64_t cliqueSize = 3;
    while (connected.size() > 1) 
    {
        auto expanded = expand(edges, connections, connected);
        ++cliqueSize;
        connected = std::move(expanded);
    }

    std::cout << "The password is " << connected[0][0];
    for (auto const& node : connected[0] | std::views::drop(1)) 
    {
        std::cout << "," << node;
    }
    std::cout << std::endl;

    return score;
}