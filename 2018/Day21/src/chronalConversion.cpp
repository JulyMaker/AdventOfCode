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
#include <tuple>
#include <iomanip>
#include <cctype> 
#include <random>
#include <valarray>
#include <thread>
#include <unordered_set>
#include <optional>
#include <deque>
#include <queue>
#include <ctype.h>

enum class Op
{
  addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti,
  gtir, gtri, gtrr, eqir, eqri, eqrr
};

struct Instruction
{
  Op op;
  std::array<int64_t, 3> data;
};

Op toOp(const std::string& op_name)
{
  std::vector<std::string> opNames(
    { "addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr",
     "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr" });

  auto op(std::find(opNames.begin(), opNames.end(), op_name));
  if (op == opNames.end())
    abort();

  return static_cast<Op>(std::distance(opNames.begin(), op));
}

std::istream& operator>>(std::istream& is, Instruction& instruction)
{
  std::string opName;
  is >> opName;

  if (is.good())
  {
    instruction.op = toOp(opName);
    is >> instruction.data[0] >> instruction.data[1] >> instruction.data[2];
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Instruction& instruction)
{
  std::vector<std::string> opNames(
    { "addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr",
     "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr" });
  os << opNames[static_cast<int64_t>(instruction.op)] << " "
    << instruction.data[0] << " " << instruction.data[1] << " "
    << instruction.data[2];

  return os;
}

void
apply_op(std::array<int64_t, 6>& registers, const Instruction& instruction)
{
  auto& input(instruction.data);

  switch (instruction.op)
  {
    case Op::addr:
      registers[input[2]] = registers[input[0]] + registers[input[1]];
      break;
    case Op::addi: registers[input[2]] = registers[input[0]] + input[1]; break;
    case Op::mulr:
      registers[input[2]] = registers[input[0]] * registers[input[1]];
      break;
    case Op::muli: registers[input[2]] = registers[input[0]] * input[1]; break;
    case Op::banr:
      registers[input[2]] = registers[input[0]] & registers[input[1]];
      break;
    case Op::bani: registers[input[2]] = registers[input[0]] & input[1]; break;
    case Op::borr:
      registers[input[2]] = registers[input[0]] | registers[input[1]];
      break;
    case Op::bori: registers[input[2]] = registers[input[0]] | input[1]; break;
    case Op::setr: registers[input[2]] = registers[input[0]]; break;
    case Op::seti: registers[input[2]] = input[0]; break;
    case Op::gtir:
      registers[input[2]] = (input[0] > registers[input[1]] ? 1 : 0);
      break;
    case Op::gtri:
      registers[input[2]] = (registers[input[0]] > input[1] ? 1 : 0);
      break;
    case Op::gtrr:
      registers[input[2]]
        = (registers[input[0]] > registers[input[1]] ? 1 : 0);
      break;
    case Op::eqir:
      registers[input[2]] = (input[0] == registers[input[1]] ? 1 : 0);
      break;
    case Op::eqri:
      registers[input[2]] = (registers[input[0]] == input[1] ? 1 : 0);
      break;
    case Op::eqrr:
      registers[input[2]]
        = (registers[input[0]] == registers[input[1]] ? 1 : 0);
      break;
  }
}


int64_t adventDay21problem12018(std::ifstream& input)
{
  
  std::string temp;
  int64_t ip;
  input >> temp >> ip;
  std::vector<Instruction> instructions( std::istream_iterator<Instruction>(input), {});

  std::array<int64_t, 6> registers;
  registers.fill(0);

  for (; registers[ip] < instructions.size(); registers[ip]++)
  {
    if (instructions[registers[ip]].op == Op::eqrr) // eqrr instruction
    {
      int regA = instructions[registers[ip]].data[0];
      return registers[regA]; // First value in register 3 line 28
    }

    apply_op(registers, instructions[registers[ip]]);
  }

  return 0;
}

int64_t adventDay21problem22018(std::ifstream& input)
{
  std::string temp;
  int64_t ip;
  input >> temp >> ip;
  std::vector<Instruction> instructions(std::istream_iterator<Instruction>(input), {});

  std::array<int64_t, 6> registers;
  registers.fill(0);

  int64_t lastStop;
  std::unordered_set<int64_t> stoppingValues;

  for (; registers[ip] < instructions.size(); registers[ip]++)
  {
    if (instructions[registers[ip]].op == Op::eqrr) // eqrr instruction
    {
      int reg = instructions[registers[ip]].data[0];
      if (stoppingValues.find(registers[reg]) != stoppingValues.end())
      {
        return lastStop; // First repeat value in register 3 line 28
      }

      lastStop = registers[reg];
      stoppingValues.insert(registers[reg]);
    }

    apply_op(registers, instructions[registers[ip]]);
  }

  return 0;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay21problem12018(infile)
                                        : adventDay21problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day21/input21.txt";
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