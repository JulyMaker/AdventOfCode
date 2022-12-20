#include <utils.h>

struct Node
{
  uint64_t id;
  int64_t val;
  Node *prev, *next;

  void swap(Node* node)
  {
    int64_t auxVal = val;
    uint64_t auxId = id;

    val = node->val;
    id = node->id;

    node->val = auxVal;
    node->id = auxId;
  }
};

struct LinkedList
{
  Node* front = nullptr;
  Node* back = nullptr;
  int64_t size = 0;

  void push_back(Node* newNode)
  {
    newNode->prev = back;

    if (back != nullptr)
      back->next = newNode;
    else
      front = newNode;

    back = newNode;

    front->prev = back;
    back->next = front;

    size++;
  }
};


uint64_t adventDay20problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  LinkedList linkedList;
  std::vector<uint64_t> ids;
  uint64_t id = 0;

  std::vector<int> in = parseInputInt(input, '\n');
  for(auto& val : in)
  {
    Node* node = new Node{ id, val };
    linkedList.push_back(node);
    ids.push_back(id++);
  }

  for (int64_t id : ids)
  {
    Node* node = linkedList.front;
    while (node->id != id) node = node->next;

    int steps = abs(node->val) % (linkedList.size - 1);

    for (int i = 0; i < steps; i++)
    {
      if (node->val < 0)
      {
        node->swap(node->prev);
        node = node->prev;
      }
      else if (node->val > 0)
      {
        node->swap(node->next);
        node = node->next;
      }
    }
  }

  Node* node = linkedList.front;
  while (node->val != 0) node = node->next; // Node with value 0

  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < 1000; j++) node = node->next; // 1000th, 2000th, 3000th

    score += node->val;
  }

  return score;
}


uint64_t adventDay20problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  const int MIXTIMES = 10;
  const int64_t MULTIPLY = 811589153;

  LinkedList linkedList;
  std::vector<uint64_t> ids;
  uint64_t id = 0;

  std::vector<int> in = parseInputInt(input, '\n');
  for (auto& val : in)
  {
    Node* node = new Node{id, val * MULTIPLY };
    linkedList.push_back(node);
    ids.push_back(id++);
  }

  for (int t = 0; t < MIXTIMES; t++)
  {
    for (int64_t id : ids)
    {
      Node* node = linkedList.front;
      while (node->id != id) node = node->next;

      int steps = abs(node->val) % (linkedList.size - 1);
      for (int i = 0; i < steps; i++)
      {
        if (node->val < 0)
        {
          node->swap(node->prev);
          node = node->prev;
        }
        else if (node->val > 0)
        {
          node->swap(node->next);
          node = node->next;
        }
      }
    }
  }

  Node* node = linkedList.front;
  while (node->val != 0) node = node->next; // Node with value 0

  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < 1000; j++) node = node->next; // 1000th, 2000th, 3000th

    score += node->val;
  }

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "20";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay20problem12022(inputFile); break;
    case 2: result = adventDay20problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}