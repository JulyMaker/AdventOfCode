#include <utils.h>

enum class OP{ SUM, SUB, MUL, DIV, NUM };

struct Monkey
{
  OP op;
  std::string operand1;
  std::string operand2;
};

OP getOperation(const char& op)
{
  switch (op)
  {
    case '+': return OP::SUM;
    case '-': return OP::SUB;
    case '*': return OP::MUL;
    case '/': return OP::DIV;
  };
}

using Monkeys = std::unordered_map<std::string, Monkey>;
using Hierarchy = std::unordered_map<std::string, std::string>;

int64_t monckeyValue( Monkeys& monkeys, const std::string& monkeyName)
{
  auto monkey = monkeys[monkeyName];

  if (monkey.op == OP::NUM)
    return stoll(monkey.operand1);
  else
  {
    int64_t op1 = monckeyValue(monkeys, monkey.operand1);
    int64_t op2 = monckeyValue(monkeys, monkey.operand2);

    switch (monkey.op)
    {
      case OP::SUM: return op1 + op2; 
      case OP::SUB: return op1 - op2;
      case OP::MUL: return op1 * op2;
      case OP::DIV: return op1 / op2;
    };
  }

  return 0;
}

uint64_t adventDay21problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  Monkeys monkeys;
  const std::string monkeyName = "root";

  std::vector<std::string> monkeysIn = parseInput(input, '\n');
  for (auto& monkey : monkeysIn)
  {
    std::vector<std::string> number = parseInputReg(monkey, "(\\w+): (\\d+)");
    if (number.size() > 0)
    {
      monkeys[number[1]].operand1 = number[2];
      monkeys[number[1]].op = OP::NUM;
    }
    else
    {
      std::vector<std::string> equation = parseInputReg(monkey, "(\\w+): (\\w+) (.) (\\w+)");
      monkeys[equation[1]].operand1 = equation[2];
      monkeys[equation[1]].operand2 = equation[4];

      monkeys[equation[1]].op = getOperation(equation[3][0]);
    }
  }

  score = monckeyValue(monkeys, monkeyName);

  return score;
}

int64_t searchValue(Monkeys& monkeys, Hierarchy& parent, const std::string& monkeyName, const std::string& child = "")
{
  if (monkeyName == "humn")
    return searchValue(monkeys, parent, parent[monkeyName], monkeyName);
  else
  {
    auto monkey = monkeys[monkeyName];
    const std::string knownMonkey = (monkey.operand1 == child ? monkey.operand2 : monkey.operand1);

    if (monkeyName == "root")
      return monckeyValue(monkeys, knownMonkey);
    else
    {
      int64_t num = monckeyValue(monkeys, knownMonkey);
      int64_t searchVal = searchValue(monkeys, parent, parent[monkeyName], monkeyName);

      switch (monkey.op)
      {
        case OP::SUM: return searchVal - num;
        case OP::SUB: return (child == monkey.operand1)? num + searchVal : num - searchVal;
        case OP::MUL: return searchVal / num;
        case OP::DIV: return (child == monkey.operand1)? num * searchVal : num / searchVal;
      }
    }
  }
}


uint64_t adventDay21problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
  Monkeys monkeys;
  const std::string monkeyName = "humn";
  Hierarchy parent;

  std::vector<std::string> monkeysIn = parseInput(input, '\n');
  for (auto& monkey : monkeysIn)
  {
    std::vector<std::string> number = parseInputReg(monkey, "(\\w+): (\\d+)");
    if (number.size() > 0)
    {
      monkeys[number[1]].operand1 = number[2];
      monkeys[number[1]].op = OP::NUM;
    }
    else
    {
      std::vector<std::string> equation = parseInputReg(monkey, "(\\w+): (\\w+) (.) (\\w+)");
      monkeys[equation[1]].operand1 = equation[2];
      monkeys[equation[1]].operand2 = equation[4];

      monkeys[equation[1]].op = getOperation(equation[3][0]);

      parent[equation[2]] = equation[1];
      parent[equation[4]] = equation[1];
    }
  }

  score = searchValue(monkeys, parent, monkeyName);

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "21";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay21problem12022(inputFile); break;
    case 2: result = adventDay21problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}