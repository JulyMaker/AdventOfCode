#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <array>
#include <mutex>
#include <numeric>
#include <intrin.h>

struct Node 
{
  std::string name;
  int weight, total;
  Node* parent;
  std::vector<std::string> children;
  std::vector<Node*> cnodes;
};

template<typename It, typename Pred>
It diff(It begin, It end, Pred p) 
{
  if (begin == end)
    return end;
  int seen = 1;
  auto cand = *begin;
  auto pos = end;
  for (auto it = std::next(begin); it != end; ++it)
    if (p(cand, *it))
      ++seen;
    else
      pos = it;
  return (seen == 1) ? begin : pos;
}

template<typename It>
It diff(It begin, It end) 
{
  return diff(begin, end, std::equal_to<void>{});
}


std::unordered_map<std::string, Node> parse(std::unordered_map<std::string, Node>& nodes, std::string& line)
{
  static std::regex re{ "[^a-z0-9]+", std::regex::optimize | std::regex::extended };
  
  line = std::regex_replace(line, re, " ");
  std::istringstream iss{ line };
  std::string name;
  int weight;

  iss >> name >> weight;
  std::vector<std::string> children{ std::istream_iterator<std::string>{iss}, {} };
  nodes[name] = Node{ name, weight, 0, nullptr, children, {} };

  return nodes;
}

int calc_totals(Node* n) 
{
  int total = n->weight;
  for (Node* ch : n->cnodes) 
  {
    total += calc_totals(ch);
  }
  n->total = total;

  return total;
}

Node* find_bad_node(Node* n) 
{
  auto eq = [](Node* lhs, Node* rhs) 
  {
    return lhs->total == rhs->total;
  };

  auto odd = diff(n->cnodes.begin(), n->cnodes.end(), eq);
  if (odd != n->cnodes.end())
    return find_bad_node(*odd);

  return n;
}

long long adventDay07problem12017(std::unordered_map<std::string, Node>& nodes)
{
  for (auto it = nodes.begin(); it != nodes.end(); ++it) 
  {
    Node& node = it->second;

    for (auto& child_name : node.children) 
    {
      Node* child = &nodes[child_name];
      child->parent = &node;
      node.cnodes.push_back(child);
    }
  }

  Node* tree = &nodes.begin()->second;
  while (tree->parent)
    tree = tree->parent;

  std::cout << "Result: " << tree->name << std::endl;

  return 0;
}

long long adventDay07problem22017(std::unordered_map<std::string, Node>& nodes)
{
  for (auto it = nodes.begin(); it != nodes.end(); ++it)
  {
    Node& node = it->second;

    for (auto& child_name : node.children)
    {
      Node* child = &nodes[child_name];
      child->parent = &node;
      node.cnodes.push_back(child);
    }
  }

  Node* tree = &nodes.begin()->second;
  while (tree->parent)
    tree = tree->parent;

  calc_totals(tree);
  Node* bad_node = find_bad_node(tree);
  int bad_total = bad_node->total;
  int diff= 0;

  for (auto const sib : bad_node->parent->cnodes)
    if (sib->total != bad_total)
      diff = sib->total - bad_total;

  return bad_node->weight + diff;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::unordered_map<std::string, Node> nodes;
  long long result = 0;

  while (!infile.eof())
  {
    std::getline(infile, line);
    if (line == "") continue;

    parse(nodes, line);
  }
  infile.close();

  result = (problNumber == 1) ? adventDay07problem12017(nodes)
                              : adventDay07problem22017(nodes);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day07/input07.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
      problem = std::stoi(argv[1]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc == 3)
  {
    fileName = argv[1];
    if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
      problem = std::stoi(argv[2]);
    else
    {
      std::cout << "Problem 1 or 2" << std::endl;
      return -1;
    }
  }
  else if (argc != 1)
  {
    std::cout << "ERROR: problem number missing" << std::endl;
    return -1;
  }


  long long int result = 0;
  switch (problem)
  {
  case 1:
    result = readFile(fileName, problem);
    break;
  case 2:
    result = readFile(fileName, problem);
    break;
  default:
    std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}