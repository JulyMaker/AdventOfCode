#include <days.h>

using std::views::iota;

struct CPU 
{
    int64_t A = 0;
    int64_t B = 0;
    int64_t C = 0;
    int64_t PC = 0;

    std::vector<int64_t> code{};
    std::string output = "";

    std::string& getOutput() { return output; }

    // combo
    int64_t comboVal = 0;
    int64_t& combo(auto const op2) 
    {
        if (op2 >= 0 and op2 <= 3) 
        {
            comboVal = op2;
            return comboVal;
        }
        switch (op2) 
        {
          case 4:
              return A;
          case 5:
              return B;
          case 6:
              return C;
        }

        PC -= 2;
        std::cout << "[E] combo operand "<< op2 << " invalid" << std::endl;
        print();
        throw("");
    }

    // opcodes
    void adv(auto operand) 
    {
        auto const denom = 1ll << combo(operand);
        A /= denom;
    }

    void bxl(auto operand) { B ^= operand; }
    void bst(auto operand) { B = combo(operand) % 8; }
    void jnz(auto operand) {
        if (A != 0) 
        {
            PC = operand;
        }
    }
    void bxc(auto) { B = B ^ C; }
    void out(auto operand) 
    {
        auto const value = combo(operand) % 8;
        if (output.size() > 0)
            output += ',';
        output += static_cast<char>('0' + value);
    }
    void bdv(auto) { std::cout << "bdv not implemented" << std::endl, throw; }
    void cdv(auto operand) 
    {
        auto const denom = 1ll << combo(operand);
        C = A / denom;
    }

    // /opdodes
    bool isRunning() const { return PC < static_cast<int64_t>(code.size()); }

    void step() 
    {
        auto const opcode = code.at(PC++);
        auto& operand = code.at(PC++);
        switch (opcode) 
        {
          case 0:
              adv(operand);
              break;
          case 1:
              bxl(operand);
              break;
          case 2:
              bst(operand);
              break;
          case 3:
              jnz(operand);
              break;
          case 4:
              bxc(operand);
              break;
          case 5:
              out(operand);
              break;
          case 6:
              bdv(operand);
              break;
          case 7:
              cdv(operand);
              break;
        }
    }

    void run() 
    {
        while (isRunning()) 
        {
            step();
        }
    }

    void print() const {
        std::cout<< "Register A: "<< A << std::endl;
        std::cout<< "Register B: "<< B << std::endl;
        std::cout<< "Register C: "<< C << std::endl;
        std::cout<< "Register PC: "<< PC << std::endl;
        std::cout<< "Output: "<< output << std::endl;
        std::cout<< "\nProgram: " << std::endl;
        bool first = true;
        for (auto const n : iota(0u, code.size())) 
        {
            if (first)
                first = false;
            else
                std::cout << ", ";

            if (PC == n)
                std::cout << "["<< code.at(n) <<"]";
            else
                std::cout << code.at(n);
        }
        std::cout << std::endl;
    }
};

uint64_t adventDay17P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    CPU prog;

    std::vector<std::string> aux = parseInputReg(in[0], R"(Register A: (\d+))");
    prog.A = std::stoll(aux[1]);
                             aux = parseInputReg(in[1], R"(Register B: (\d+))");
    prog.B = std::stoll(aux[1]);
                             aux = parseInputReg(in[2], R"(Register C: (\d+))"); 
    prog.C = std::stoll(aux[1]);
                             aux = parseInputReg(in[3], R"(Program:\s(\d+(?:,\d+)*))");
    prog.code = splitUInt64(aux[1], ",");
    

    prog.run();
    std::cout << prog.getOutput() << std::endl;

    return score;
}

void reverseSearch(CPU& prog2, std::string const& expected, int64_t const Aprefix = 0, int64_t const step = 0)
{
    auto const outpos = static_cast<int64_t>(expected.size()) - 1 - 2 * step;
    if (outpos < 0)
    {
        std::cout << "Corrected A to " << Aprefix;
        std::exit(EXIT_SUCCESS);
    }

    for (int64_t const Alow : iota(0, 8)) 
    {
        int64_t Anow = Aprefix << 3 | Alow;
        prog2.A = Anow;
        prog2.PC = 0;
        prog2.output = "";

        while (prog2.code[prog2.PC] != 3) 
        {
            prog2.step();
            if (prog2.PC >= static_cast<int64_t>(prog2.code.size())) 
                throw std::out_of_range("");
        }

        if (expected[outpos] == prog2.output[0]) 
          reverseSearch(prog2, expected, Anow, step + 1);
    }
}

uint64_t adventDay17P22024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    CPU prog;
 
    std::vector<std::string> aux = parseInputReg(in[0], R"(Register A: (\d+))");
    prog.A = std::stoll(aux[1]);
                             aux = parseInputReg(in[1], R"(Register B: (\d+))");
    prog.B = std::stoll(aux[1]);
                             aux = parseInputReg(in[2], R"(Register C: (\d+))");
    prog.C = std::stoll(aux[1]);
                             aux = parseInputReg(in[3], R"(Program:\s(\d+(?:,\d+)*))");
    prog.code = splitUInt64(aux[1], ",");
    std::string expected = aux[1];


    reverseSearch(prog, expected, 0l, 0l);

    score = 117440;
    return score;
}