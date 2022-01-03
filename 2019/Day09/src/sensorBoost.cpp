#include <utils.h>

constexpr int OP_ADD = 1;
constexpr int OP_MUL = 2;
constexpr int OP_IN = 3;
constexpr int OP_OUT = 4;
constexpr int OP_JMPNZ = 5;
constexpr int OP_JMPZ = 6;
constexpr int OP_LS = 7;
constexpr int OP_EQ = 8;
constexpr int OP_BASEOFF = 9;
constexpr int OP_HALT = 99;

constexpr int MOD_POSITION = 0;
constexpr int MOD_IMMEDIATE = 1;
constexpr int MOD_RELBASE = 2;

long long readMemory(std::vector<long long>& memory, ptrdiff_t const off)
{
  if (off < 0) throw std::runtime_error("index out of bounds");

  if (off >= memory.size())
    memory.resize(off + 1, 0);

  return memory[off];
}

void writeMemory(std::vector<long long>& memory, ptrdiff_t const off, int64_t const value)
{
  if (off < 0) throw std::runtime_error("index out of bounds");

  if (off >= memory.size())
    memory.resize(off + 1, 0);

  memory[off] = value;
}


long long readValue(std::vector<long long>& memory, ptrdiff_t const ip, ptrdiff_t const relBase, int const mode)
{
  ptrdiff_t off = -1;

  switch (mode)
  {
    case MOD_POSITION:  off = memory[ip];            break;
    case MOD_IMMEDIATE: off = ip;                    break;
    case MOD_RELBASE:   off = relBase + memory[ip]; break;
    default:            throw std::runtime_error("invalid access mode");
  }

  return readMemory(memory, off);
}

void writeValue(std::vector<int64_t>& memory, ptrdiff_t const ip, ptrdiff_t const relBase, int const mode, int64_t const value)
{
  ptrdiff_t off = -1;

  switch (mode)
  {
    case MOD_POSITION:  off = memory[ip];            break;
    case MOD_IMMEDIATE: throw std::runtime_error("cannot write in immediate mode");
    case MOD_RELBASE:   off = relBase + memory[ip]; break;
    default:            throw std::runtime_error("invalid access mode");
  }

  writeMemory(memory, off, value);
}

uint64_t runProgram(std::vector<int64_t>& memory, int cin = 1)
{
  ptrdiff_t ip = 0;
  ptrdiff_t relBase = 0;
  uint64_t result = 0;

  while (true)
  {
    int64_t inst = memory[ip];
    int opcode = inst % 100;
    inst /= 100;
    int mod1 = inst % 10; inst /= 10;
    int mod2 = inst % 10; inst /= 10;
    int mod3 = inst % 10; inst /= 10;

    if (opcode == OP_HALT) break;

    switch (opcode)
    {
      case OP_ADD:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        int64_t param2 = readValue(memory, ip + 2, relBase, mod2);
        writeValue(memory, ip + 3, relBase, mod3, param1 + param2);
        ip += 4;
      }
      break;
      case OP_MUL:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        int64_t param2 = readValue(memory, ip + 2, relBase, mod2);
        writeValue(memory, ip + 3, relBase, mod3, param1 * param2);
        ip += 4;
      }
      break;
      case OP_IN:
      {
        int64_t value;
        //std::cout << ':'; std::cin >> value;
        value = cin;
        writeValue(memory, ip + 1, relBase, mod1, value);

        ip += 2;
      }
      break;
      case OP_OUT:
      {
        int64_t param = readValue(memory, ip + 1, relBase, mod1);
        //std::cout << param << '\n';
        result = param;
        ip += 2;
      }
      break;
      case OP_JMPNZ:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        ip = (param1 != 0) ? readValue(memory, ip + 2, relBase, mod2) : ip + 3;
      }
      break;
      case OP_JMPZ:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        ip = (param1 == 0) ? readValue(memory, ip + 2, relBase, mod2) : ip + 3;
      }
      break;
      case OP_LS:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        int64_t param2 = readValue(memory, ip + 2, relBase, mod2);
        writeValue(memory, ip + 3, relBase, mod3, param1 < param2 ? 1 : 0);
        ip += 4;
      }
      break;
      case OP_EQ:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        int64_t param2 = readValue(memory, ip + 2, relBase, mod2);
        writeValue(memory, ip + 3, relBase, mod3, param1 == param2 ? 1 : 0);
        ip += 4;
      }
      break;
      case OP_BASEOFF:
      {
        int64_t param1 = readValue(memory, ip + 1, relBase, mod1);
        relBase += param1;
        ip += 2;
      }
      break;
    }
  }

  return result;
}

uint64_t adventDay09problem12019(std::ifstream& input)
{
  std::vector<int64_t> memory = parseInputInt64(input, ',');
  
	return runProgram(memory, 1);
}

uint64_t adventDay09problem22019(std::ifstream& input)
{
  std::vector<int64_t> memory = parseInputInt64(input, ',');

  return runProgram(memory, 2);
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "09";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay09problem12019(inputFile); break;
    case 2: result = adventDay09problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}