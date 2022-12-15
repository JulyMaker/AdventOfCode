#include <utils.h>
#include <variant>

struct List : std::variant<std::vector<List>, int>
{
  List* parent = nullptr;
  using std::variant<std::vector<List>, int>::variant;

  std::vector<List>& list() { return std::get<std::vector<List>>(*this); }
  int& Int() { return std::get<int>(*this); }

  friend std::ostream& operator<<(std::ostream& s, List& l)
  {
    if(l.index() == 0)
    {
      auto& v = l.list();

      s << '[';
      for (auto& elem : v)
        s << elem << ',';
      s << ']';
    }
    else
      s << l.Int();

    return s;
  }

  std::weak_ordering compare(List other)
  {
    if (index() == 1 && other.index() == 1)
      return Int() <=> other.Int();

    std::vector<List> left;
    if (index() == 1)
      left.push_back(Int());
    else
      left = list();

    std::vector<List> right;
    if (other.index() == 1)
      right.push_back(other.Int());
    else
      right = other.list();

    int minSize = std::min(left.size(), right.size());

    for (int i = 0; i < minSize; i++)
      if (auto res = left[i].compare(right[i]); res != std::weak_ordering::equivalent)
        return res;

    if (left.size() < right.size())
      return std::weak_ordering::less;

    if (left.size() > right.size())
      return std::weak_ordering::greater;

    return std::weak_ordering::equivalent;
  }
};

void ignoreComma(std::ifstream& fin)
{
  char comma;
  fin >> comma;
  if (comma != ',')
    fin.seekg(-1, std::ios::cur);
}

void parseNext(std::ifstream& fin, List& list)
{
  auto& l = list.list();

  char bracket;
  fin >> bracket;

  if (bracket == '[')
  {
    List newL = std::vector<List>();
    newL.parent = &list;

    l.emplace_back(newL);

    parseNext(fin, l.back());
  }
  else if(bracket == ']')
  {
    if (list.parent)
    {
      ignoreComma(fin);
      parseNext(fin, *list.parent);
    }
  }
  else
  {
    fin.seekg(-1, std::ios::cur);
    int value;
    fin >> value;
    l.push_back(value);

    ignoreComma(fin);
    parseNext(fin, list);
  }
}

uint64_t adventDay13problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::vector<List> lists;
  while (input)
  {
    List list = std::vector<List>{};

    char bracket;
    input >> bracket;

    if (!input) break;

    if (bracket == '[')
      parseNext(input, list);

    lists.emplace_back(list);
  }

  std::vector<std::pair<List, List>> pairs;
  for (int i = 0; i < lists.size(); i+= 2)
    pairs.emplace_back(lists[i], lists[i+1]);

  for (int i = 0; i < pairs.size(); i++)
    if (pairs[i].first.compare(pairs[i].second) == std::weak_ordering::less)
      score += i + 1;

  return score;
}

uint64_t adventDay13problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  std::vector<List> lists;
  while (input)
  {
    List list = std::vector<List>{};

    char bracket;
    input >> bracket;

    if (!input) break;

    if (bracket == '[')
      parseNext(input, list);

    lists.emplace_back(list);
  }

  List divider1 = std::vector<List>{ std::vector<List>{2} };
  lists.push_back(divider1);
  List divider2 = std::vector<List>{ std::vector<List>{6} };
  lists.push_back(divider2);

  std::sort(lists.begin(), lists.end(), 
    [](List a, List b) {
      return a.compare(b) == std::weak_ordering::less; 
  });
  
  score = 1;
  for (int i = 0; i < lists.size(); i++)
  {
    auto& list = lists[i];
    if (list.compare(divider1) == std::weak_ordering::equivalent || list.compare(divider2) == std::weak_ordering::equivalent)
      score *= (i + 1);
  }

  return score;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "13";
  const bool example = false;

  std::string fileName = (example) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay13problem12022(inputFile); break;
    case 2: result = adventDay13problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}