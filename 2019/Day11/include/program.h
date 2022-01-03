#include <utils.h>

using offset_t = ptrdiff_t;
using result_t = std::pair<std::vector<int64_t>, bool>;

class program_t
{
  std::vector<int64_t> memory;
  offset_t ip = 0;
  offset_t relBase = 0;

  constexpr static int OP_ADD = 1;
  constexpr static int OP_MUL = 2;
  constexpr static int OP_IN = 3;
  constexpr static int OP_OUT = 4;
  constexpr static int OP_JMPNZ = 5;
  constexpr static int OP_JMPZ = 6;
  constexpr static int OP_LS = 7;
  constexpr static int OP_EQ = 8;
  constexpr static int OP_BASEOFF = 9;
  constexpr static int OP_HALT = 99;

  constexpr static int MOD_POSITION = 0;
  constexpr static int MOD_IMMEDIATE = 1;
  constexpr static int MOD_RELBASE = 2;

private:
  int64_t readMemory(offset_t const off)
  {
    if (off < 0) throw std::runtime_error("index out of bounds");

    if (off >= memory.size())
      memory.resize(off + 1, 0);

    return memory[off];
  }

  void writeMemory(offset_t const off, int64_t const value)
  {
    if (off < 0) throw std::runtime_error("index out of bounds");

    if (off >= memory.size())
      memory.resize(off + 1, 0);

    memory[off] = value;
  }

  int64_t readValue(ptrdiff_t const ip, ptrdiff_t const relBase, int const mode)
  {
    offset_t off = -1;

    switch (mode)
    {
      case MOD_POSITION:  off = memory[ip];            break;
      case MOD_IMMEDIATE: off = ip;                    break;
      case MOD_RELBASE:   off = relBase + memory[ip]; break;
      default:            throw std::runtime_error("invalid access mode");
    }

    return readMemory(off);
  }

  void writeValue(ptrdiff_t const ip, offset_t const relBase, int const mode, int64_t const value)
  {
    offset_t off = -1;

    switch (mode)
    {
      case MOD_POSITION:  off = memory[ip];            break;
      case MOD_IMMEDIATE: throw std::runtime_error("cannot write in immediate mode");
      case MOD_RELBASE:   off = relBase + memory[ip]; break;
      default:            throw std::runtime_error("invalid access mode");
    }

    writeMemory(off, value);
  }

public:
  program_t(std::vector<int64_t> const& mem) :memory(mem) {}

  program_t(std::initializer_list<int64_t> mem) : memory(mem) {}

  result_t execute(int64_t const input)
  {
    std::vector<int64_t> output;
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
        case OP_ADD:      execute_add(mod1, mod2, mod3); break;
        case OP_MUL:      execute_mul(mod1, mod2, mod3); break;
        case OP_IN:       execute_in(mod1, input); break;
        case OP_OUT:      output.push_back(execute_out(mod1));
                          if (output.size() == 2) return { output, false }; break;
        case OP_JMPNZ:    execute_jump_nz(mod1, mod2); break;
        case OP_JMPZ:     execute_jump_z(mod1, mod2); break;
        case OP_LS:       execute_less(mod1, mod2, mod3); break;
        case OP_EQ:       execute_equal(mod1, mod2, mod3); break;
        case OP_BASEOFF:  execute_baseoff(mod1); break;
      }
    }

    return { output, true };
  }

private:
  void execute_add(int const mod1, int const mod2, int const mod3)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    int64_t param2 = readValue(ip + 2, relBase, mod2);
    writeValue(ip + 3, relBase, mod3, param1 + param2);
    ip += 4;
  }

  void execute_mul(int const mod1, int const mod2, int const mod3)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    int64_t param2 = readValue(ip + 2, relBase, mod2);
    writeValue(ip + 3, relBase, mod3, param1 * param2);
    ip += 4;
  }

  void execute_in(int const mod1, int64_t const input)
  {
    writeValue(ip + 1, relBase, mod1, input);
    ip += 2;
  }

  int64_t execute_out(int const mod1)
  {
    int64_t param = readValue(ip + 1, relBase, mod1);
    ip += 2;
    return param;
  }

  void execute_jump_nz(int const mod1, int const mod2)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    ip = (param1 != 0) ? readValue(ip + 2, relBase, mod2) : ip + 3;
  }

  void execute_jump_z(int const mod1, int const mod2)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    ip = (param1 == 0) ? readValue(ip + 2, relBase, mod2) : ip + 3;
  }

  void execute_less(int const mod1, int const mod2, int const mod3)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    int64_t param2 = readValue(ip + 2, relBase, mod2);
    writeValue(ip + 3, relBase, mod3, param1 < param2 ? 1 : 0);
    ip += 4;
  }

  void execute_equal(int const mod1, int const mod2, int const mod3)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    int64_t param2 = readValue(ip + 2, relBase, mod2);
    writeValue(ip + 3, relBase, mod3, param1 == param2 ? 1 : 0);
    ip += 4;
  }

  void execute_baseoff(int const mod1)
  {
    int64_t param1 = readValue(ip + 1, relBase, mod1);
    relBase += param1;
    ip += 2;
  }
};

struct position_t
{
  int x;
  int y;
};

struct panel_t
{
  int color;
  int paint_count;
};

enum class direction_t { left, right, up, down };

constexpr int TURN_LEFT = 0;
constexpr int TURN_RIGHT = 1;

bool operator==(position_t const& p1, position_t const& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

bool operator<(position_t const& p1, position_t const& p2)
{
  return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}


std::map<position_t, panel_t> countPanels(program_t program, int const startColor = 0)
{
  std::map<position_t, panel_t> panels;

  position_t crt{ 0,0 };
  int color = startColor;
  direction_t direction = direction_t::up;

  while (true)
  {
    auto pit = panels.find(crt);
    if (pit != panels.end())
      color = pit->second.color;
    else if (!panels.empty())
      color = 0;

    auto res = program.execute(color);
    if (res.first.size() == 2)
    {
      auto newcolor = res.first.front();
      auto nextturn = res.first.back();

      if (pit != panels.end())
      {
        pit->second.color = newcolor;
        pit->second.paint_count++;
      }
      else
      {
        panel_t p = { newcolor, 1 };
        panels.insert(std::make_pair(crt, p));
      }

      if (nextturn == TURN_LEFT)
      {
        switch (direction)
        {
          case direction_t::left:
            crt.y--; direction = direction_t::down;
            break;
          case direction_t::right:
            crt.y++; direction = direction_t::up;
            break;
          case direction_t::up:
            crt.x--; direction = direction_t::left;
            break;
          case direction_t::down:
            crt.x++; direction = direction_t::right;
            break;
        }
      }
      else
      {
        switch (direction)
        {
          case direction_t::left:
            crt.y++; direction = direction_t::up;
            break;
          case direction_t::right:
            crt.y--; direction = direction_t::down;
            break;
          case direction_t::up:
            crt.x++; direction = direction_t::right;
            break;
          case direction_t::down:
            crt.x--; direction = direction_t::left;
            break;
        }
      }
    }

    if (res.second)
      break;
  }

  return panels;
}

void paint(std::map<position_t, panel_t>& panels)
{
  int xmin = std::numeric_limits<int>::max();
  int xmax = std::numeric_limits<int>::min();
  int ymin = std::numeric_limits<int>::max();
  int ymax = std::numeric_limits<int>::min();

  for (auto const& kvp : panels)
  {
    if (kvp.first.x > xmax) xmax = kvp.first.x;
    if (kvp.first.x < xmin) xmin = kvp.first.x;
    if (kvp.first.y > ymax) ymax = kvp.first.y;
    if (kvp.first.y < ymin) ymin = kvp.first.y;
  }

  size_t width = static_cast<size_t>(xmax) - static_cast<size_t>(xmin) + 1;
  size_t height = static_cast<size_t>(ymax) - static_cast<size_t>(ymin) + 1;

  std::vector<int> data(width * height, 0);
  for (auto const& kvp : panels)
  {
    int row = ymax - kvp.first.y;
    int col = kvp.first.x - xmin;

    data[row * width + col] = kvp.second.color;
  }

  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      if (data[r * width + c] == 1)
        std::cout << '#';
      else
        std::cout << ' ';
    }
    std::cout << '\n';
  }

  std::cout << '\n';
}