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

enum Opcode { na, addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };

struct Instruction 
{
  Opcode opcode;
  int A, B, C;

  std::vector<int> execute(std::vector<int>);
  void reset() { opcode = na; A = 0; B = 0; C = 0; }
};

std::vector<int> Instruction::execute(std::vector<int> regs) {
  switch (opcode) {
  case addr:
    regs[C] = regs[A] + regs[B]; break;
  case addi:
    regs[C] = regs[A] + B; break;
  case mulr:
    regs[C] = regs[A] * regs[B]; break;
  case muli:
    regs[C] = regs[A] * B; break;
  case banr:
    regs[C] = regs[A] & regs[B]; break;
  case bani:
    regs[C] = regs[A] & B; break;
  case borr:
    regs[C] = regs[A] | regs[B]; break;
  case bori:
    regs[C] = regs[A] | B; break;
  case setr:
    regs[C] = regs[A]; break;
  case seti:
    regs[C] = A; break;
  case gtir:
    (A > regs[B]) ? regs[C] = 1 : regs[C] = 0; break;
  case gtri:
    (regs[A] > B) ? regs[C] = 1 : regs[C] = 0; break;
  case gtrr:
    (regs[A] > regs[B]) ? regs[C] = 1 : regs[C] = 0; break;
  case eqir:
    (A == regs[B]) ? regs[C] = 1 : regs[C] = 0; break;
  case eqri:
    (regs[A] == B) ? regs[C] = 1 : regs[C] = 0; break;
  case eqrr:
    (regs[A] == regs[B]) ? regs[C] = 1 : regs[C] = 0; break;
  default:
    break;
  }

  return regs;
}

int64_t adventDay16problem12018(std::ifstream& input)
{
  std::vector<int> registers(4, 0);

  std::unordered_map<int, Opcode> realOpcodes;
  std::unordered_map<int, std::vector<Opcode>> possibleOpcodes;
  std::vector<Opcode> allOpcodes;

  for (int i = 0; i < 16; i++) 
  {
    allOpcodes.clear();
    for (int j = 1; j <= 16; j++) 
      allOpcodes.push_back(Opcode(j));

    possibleOpcodes[i] = allOpcodes;
  }

  int totalCount = 0, opcode;
  Instruction inst;
  std::vector<int> afterRegs(4);

  std::string before, instruction, after;
  std::vector<Opcode> workingOpcodes;
  while (!input.eof())
  {
    getline(input, before);
    if (before == "" || (before[0] != 'B')) continue;
    getline(input, instruction); getline(input, after);
    input.seekg(1, input.cur);

    sscanf(before.c_str(), "Before: [%d, %d, %d, %d]", &registers[0], &registers[1], &registers[2], &registers[3]);
    sscanf(instruction.c_str(), "%d %d %d %d", &opcode, &inst.A, &inst.B, &inst.C);
    sscanf(after.c_str(), "After:  [%d, %d, %d, %d]", &afterRegs[0], &afterRegs[1], &afterRegs[2], &afterRegs[3]);

    workingOpcodes.clear();
    for (int op = 1; op <= 16; op++) 
    {
      inst.opcode = Opcode(op);
      std::vector<int> finalRegs = inst.execute(registers);
      if (finalRegs == afterRegs) workingOpcodes.push_back(inst.opcode);
    }

    if (workingOpcodes.size() >= 3) totalCount++;

    std::sort(workingOpcodes.begin(), workingOpcodes.end());
    std::sort(possibleOpcodes[opcode].begin(), possibleOpcodes[opcode].end());

    std::vector<Opcode> matchedOpcodes;
    std::set_intersection(possibleOpcodes[opcode].begin(), possibleOpcodes[opcode].end(), workingOpcodes.begin(), workingOpcodes.end(), std::back_inserter(matchedOpcodes));
    possibleOpcodes[opcode] = matchedOpcodes;

    inst.reset();
  }

  return totalCount;
}

int64_t adventDay16problem22018(std::ifstream& input)
{
  std::vector<int> registers(4, 0);

  std::unordered_map<int, Opcode> realOpcodes;
  std::unordered_map<int, std::vector<Opcode>> possibleOpcodes;
  std::vector<Opcode> allOpcodes;

  for (int i = 0; i < 16; i++)
  {
    allOpcodes.clear();
    for (int j = 1; j <= 16; j++)
      allOpcodes.push_back(Opcode(j));

    possibleOpcodes[i] = allOpcodes;
  }

  int opcode, count =0;
  Instruction inst;
  std::vector<int> afterRegs(4);

  std::string before, instruction, after;
  std::vector<Opcode> workingOpcodes;
  while (!input.eof())
  {
    getline(input, before);
    if (before == "")
    {
      count++;
      if (count > 1)
        break;
      continue;
    }

    getline(input, instruction); getline(input, after);
    input.seekg(1, input.cur);

    sscanf(before.c_str(), "Before: [%d, %d, %d, %d]", &registers[0], &registers[1], &registers[2], &registers[3]);
    sscanf(instruction.c_str(), "%d %d %d %d", &opcode, &inst.A, &inst.B, &inst.C);
    sscanf(after.c_str(), "After:  [%d, %d, %d, %d]", &afterRegs[0], &afterRegs[1], &afterRegs[2], &afterRegs[3]);

    workingOpcodes.clear();
    for (int op = 1; op <= 16; op++)
    {
      inst.opcode = Opcode(op);
      std::vector<int> finalRegs = inst.execute(registers);
      if (finalRegs == afterRegs) workingOpcodes.push_back(inst.opcode);
    }

    std::sort(workingOpcodes.begin(), workingOpcodes.end());
    std::sort(possibleOpcodes[opcode].begin(), possibleOpcodes[opcode].end());

    std::vector<Opcode> matchedOpcodes;
    std::set_intersection(possibleOpcodes[opcode].begin(), possibleOpcodes[opcode].end(), workingOpcodes.begin(), workingOpcodes.end(), std::back_inserter(matchedOpcodes));
    possibleOpcodes[opcode] = matchedOpcodes;

    inst.reset();
    count = 0;
  }

  //////////////////////////////////////////////////////////////////////

  std::fill(registers.begin(), registers.end(), 0);
  inst.reset();

  while (realOpcodes.size() < 16) 
  {
    for (auto& [op, possibleOps] : possibleOpcodes) 
    {
      if (possibleOps.size() == 1) 
      {
        realOpcodes[op] = possibleOps[0];
        for (auto& [otherOp, otherPossibleOps] : possibleOpcodes) 
        {
          if (otherOp != op)
            otherPossibleOps.erase(std::remove(otherPossibleOps.begin(), otherPossibleOps.end(), realOpcodes[op]), otherPossibleOps.end());
        }
      }
    }
  }

  while (getline(input, instruction))
  {
    if (instruction == "") continue;

    sscanf(instruction.c_str(), "%d %d %d %d", &opcode, &inst.A, &inst.B, &inst.C);
    inst.opcode = realOpcodes[opcode];
    registers = inst.execute(registers);
  }

  return registers[0];
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay16problem12018(infile)
                                        : adventDay16problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day16/input16.txt";
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