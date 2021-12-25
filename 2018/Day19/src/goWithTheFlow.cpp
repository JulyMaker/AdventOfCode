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

enum Ins { ADDR, ADDI, MULR, MULI, BANR, BANI, BORR, BORI, SETR, SETI, GTIR, GTRI, GTRR, EQIR, EQRI, EQRR };
static std::unordered_map<std::string, Ins> const table =
{ {"addr", ADDR}, {"addi", ADDI}, {"mulr", MULR}, {"muli", MULI}, {"banr", BANR}, {"bani", BANI},
  {"borr", BORR}, {"bori", BORI}, {"setr", SETR}, {"seti", SETI}, {"gtir", GTIR}, {"gtri", GTRI},
  {"gtrr", GTRR}, {"eqir", EQIR}, {"eqri", EQRI}, {"eqrr", EQRR}
};

std::vector<std::string> parseLines(std::ifstream& input, int& ipRegister)
{
  std::string line;
  getline(input, line);
  
  const std::regex pat{ "#ip (\\d+)" };
  std::smatch match;
  std::regex_search(line, match, pat);
  ipRegister = std::stoi(match[1].str());

  std::vector<std::string> instructions;
  while(!input.eof())
  {
    getline(input, line);
    if (line != "")
      instructions.push_back(line);
  }

  return instructions;
}


int64_t insProcess(const std::string& ins, const int a, const int b, const std::vector<int64_t>& r)
{
  auto it = table.find(ins);

  switch(it->second)
  {
    case ADDR: 
      return r[a] + r[b];
    case ADDI: 
      return r[a] + b;
    case MULR: 
      return r[a] * r[b];
    case MULI: 
      return r[a] * b;
    case BANR: 
      return r[a] & r[b];
    case BANI:
      return r[a] & b;
    case BORR: 
      return r[a] | r[b];
    case BORI: 
      return r[a] | b;
    case SETR: 
      return r[a];
    case SETI: 
      return a;
    case GTIR: 
      return (a > r[b])? 1 : 0;
    case GTRI: 
      return (r[a] > b) ? 1 : 0;
    case GTRR: 
      return (r[a] > r[b]) ? 1 : 0;
    case EQIR: 
      return (a == r[b]) ? 1 : 0;
    case EQRI: 
      return (r[a] == b) ? 1 : 0;
    case EQRR:
      return (r[a] == r[b]) ? 1 : 0;
    default:
      std::cout<< "No valid" <<std::endl;
  }
}


std::vector<int64_t> runProgram(const int ipRegister, std::vector<std::string>& program, std::vector<int64_t>& reg)
{
  while (reg[ipRegister] >=0 && reg[ipRegister] < program.size())
  {
    const std::regex pat{ "(\\w+) (\\d+) (\\d+) (\\d+)" };
    std::smatch match;
  
    std::regex_search(program[reg[ipRegister]], match, pat);
     
    //reg[c] = insProcess(inst, a, b, reg);
    reg[std::stoi(match[4].str())] = insProcess(match[1].str(), std::stoi(match[2].str()), std::stoi(match[3].str()), reg);
    reg[ipRegister]++;
  }
     
  return reg;
}
 

int64_t adventDay19problem12018(std::ifstream& input)
{
  int ipRegister = 0;
  std::vector<std::string> program;
  program = parseLines(input, ipRegister);

  std::vector<int64_t> reg = {0, 0, 0, 0, 0, 0};
  
  return runProgram(ipRegister, program, reg)[0];
}

std::vector<int64_t> runProgram2(int ipRegister, std::vector<std::string>& program, std::vector<int64_t>& reg, const int maxCycles)
{
  int ip = 0;
  int cycles = 0;

  while (ip >= 0 && ip < program.size() && (cycles < maxCycles))
  {
    reg[ipRegister] = ip;

    const std::regex pat{ "(\\w+) (\\d+) (\\d+) (\\d+)" };
    std::smatch match;

    std::regex_search(program[ip], match, pat);

    //reg[c] = insProcess(inst, a, b, reg);
    reg[std::stoi(match[4].str())] = insProcess(match[1].str(), std::stoi(match[2].str()), std::stoi(match[3].str()), reg);
    ip = reg[ipRegister] + 1;

    cycles++;
  }

  return reg;
}

int64_t adventDay19problem22018(std::ifstream& input)
{
  int ipRegister = 0;
  std::vector<std::string> program;
  program = parseLines(input, ipRegister);

  std::vector<int64_t> reg = { 1, 0, 0, 0, 0, 0 };

  std::vector<int64_t> values = runProgram2(ipRegister, program, reg, 1000);
  int64_t n = *std::max_element(values.begin(), values.end());

  // manually disassembled code ... (too slow)
  //
  // f = 1  # 1
  // while f <= d:  # 13 - 15
  //     b = 1  # 2
  //     while b <= d:  # 9 - 11
  //       if (f * b) == d:  # 3 - 6
  //             a += f  # 7
  //         b += 1  # 8
  //     f += 1  # 12
  //
  // optimized inner loop, that checks for factors faster

  int64_t total = 0;
  for (int i = 1; i <= n + 1; i++)
    if (n % i == 0)
      total += i;

  return total;
}

int64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay19problem12018(infile)
                                        : adventDay19problem22018(infile);

  return result;
}

int main(int argc, char* argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day19/input19.txt";
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