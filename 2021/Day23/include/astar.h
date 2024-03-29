#ifndef UTIL_A_STAR_H_
#define UTIL_A_STAR_H_

#include <algorithm>
#include <optional>
#include <queue>
#include <utility>
#include <vector>
#include <state.h>

template <typename Node, typename Cost>
struct BestPath 
{
  std::vector<Node> path;
  Cost cost;
};

template <typename Node>
std::vector<Node> BacktrackPath( Node end, const std::unordered_map<Node, Node, stateHash>& came_from) 
{
  std::vector<Node> path{ end };
  for (auto from_it = came_from.find(end); from_it != came_from.end(); from_it = came_from.find(from_it->second)) 
  {
    path.emplace_back(from_it->second);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

template <typename Node, typename AdjacentFn, typename CostFn>
auto AStar(Node start, Node goal, AdjacentFn get_adjacent, CostFn edge_cost)-> std::optional<BestPath<Node, decltype(edge_cost(start, goal))>> 
{
  using Cost = decltype(edge_cost(start, goal));
  struct NodeAndCost 
  {
    explicit NodeAndCost(Node node_in, Cost cost_in) : node(std::move(node_in)), cost(cost_in) {}

    Node node;
    Cost cost;
  };

  struct GreaterCost 
  {
    bool operator()(const NodeAndCost& a, const NodeAndCost& b) const 
    {
      return a.cost > b.cost;
    }
  };

  std::unordered_map<Node, Node, stateHash> came_from;
  std::unordered_map<Node, Cost, stateHash> cost_to_node{ {start, Cost(0)} };
  std::priority_queue<NodeAndCost, std::vector<NodeAndCost>, GreaterCost> node_queue;

  node_queue.emplace(std::move(start), Cost(0));
  while (!node_queue.empty()) 
  {
    NodeAndCost current = node_queue.top();
    node_queue.pop();
    if (current.node == goal) 
    {
      return BestPath<Node, Cost>{.path = BacktrackPath(goal, came_from),
        .cost = current.cost};
    }

    // It's possible that in the time since a path to this node was put on the
    // queue, a shorter path to the node was already found and processed first.
    // Skip re-processing this node if that happened.
    if (current.cost > cost_to_node[current.node]) continue;

    for (Node adjacent : get_adjacent(current.node)) 
    {
      const Cost tentative_cost = current.cost + edge_cost(current.node, adjacent);
      auto [cost_it, inserted] = cost_to_node.try_emplace(adjacent, tentative_cost);
      if (inserted || tentative_cost < cost_it->second) 
      {
        cost_it->second = tentative_cost;
        came_from[adjacent] = current.node;
        node_queue.emplace(std::move(adjacent), tentative_cost);
      }
    }
  }

  // No path exists.
  return std::nullopt;
}

#endif  // UTIL_A_STAR_H