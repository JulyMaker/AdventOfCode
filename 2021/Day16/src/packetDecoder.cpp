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
#include <deque>
#include <stack>
#include <queue>
#include <packet.h>


std::vector<bool> parseHexadecimal(std::ifstream& infile)
{
  std::string line;
  std::vector<bool> binary;

  std::getline(infile, line);

  for (char c : line) 
  {
    uint8_t val = 0;
    if (c >= '0' && c <= '9') {
      val = c - '0';
    }
    else if (c >= 'A' && c <= 'F') 
    {
      val = c - 'A' + 10;
    }
    else if (c == '\n') {
      continue;
    }

    binary.push_back((val & 8) != 0);
    binary.push_back((val & 4) != 0);
    binary.push_back((val & 2) != 0);
    binary.push_back((val & 1) != 0);
  }

  return binary;
}


uint64_t parseBits(std::vector<bool>::const_iterator begin, std::vector<bool>::const_iterator end) 
{
  uint64_t result = 0;
  for (; begin != end; ++begin) 
  {
    result <<= 1;
    if (*begin) result |= 1;
  }
  return result;
}

std::pair<uint64_t, std::vector<bool>::const_iterator> parseGroup(std::vector<bool>::const_iterator begin, std::vector<bool>::const_iterator end) 
{
  uint64_t value = 0;
  while(true) //for (;;) 
  {
    const bool terminate = !*(begin++);
    value = (value << 4) | parseBits(begin, begin + 4);
    begin += 4;

    if (terminate) 
      return { value, begin };
  }
}

PacketAndIterator parseGeneral(std::vector<bool>::const_iterator begin, std::vector<bool>::const_iterator end) 
{
  PacketAndIterator result;
  result.packet = std::make_unique<Packet>();

  result.packet->version_ = parseBits(begin, begin + 3);
  begin += 3;
  result.packet->type_    = parseBits(begin, begin + 3);
  begin += 3;

  if (result.packet->type_ == 4) 
  {
    auto [literal, after_literal] = parseGroup(begin, end);
    result.packet->contents_.emplace<uint64_t>(literal);
    begin = after_literal;
  }
  else 
  {
    std::vector<std::unique_ptr<Packet>> subpackets;

    const bool length_subs = *(begin++);
    if (!length_subs) 
    {
      const uint64_t subpack_bits = parseBits(begin, begin + 15);
      begin += 15;

      const std::vector<bool>::const_iterator end_subpackets = begin + subpack_bits;

      while (begin != end_subpackets) 
      {
        PacketAndIterator subpack_result = parseGeneral(begin, end_subpackets);
        subpackets.emplace_back(std::move(subpack_result.packet));
        begin = subpack_result.after;
      }
    }
    else 
    {
      const uint64_t num_subpackets = parseBits(begin, begin + 11);
      begin += 11;

      for (uint64_t subpNum = 0; subpNum < num_subpackets; ++subpNum)
      {
        PacketAndIterator subpacket_result = parseGeneral(begin, end);
        subpackets.emplace_back(std::move(subpacket_result.packet));
        begin = subpacket_result.after;
      }
    }

    result.packet->contents_.emplace<std::vector<std::unique_ptr<Packet>>>( std::move(subpackets) );
  }
  result.after = begin;

  return result;
}


uint64_t adventDay16problem12021(std::ifstream& infile)
{
  std::vector<bool> binary = parseHexadecimal(infile);

  PacketAndIterator result = parseGeneral(binary.begin(), binary.end());

  return result.packet->addVersions();
}

uint64_t adventDay16problem22021(std::ifstream& infile)
{
  std::vector<bool> binary = parseHexadecimal(infile);

  PacketAndIterator result = parseGeneral(binary.begin(), binary.end());

  return result.packet->calculateValue();
}

uint64_t readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  uint64_t result = (problNumber == 1) ? adventDay16problem12021(infile)
                                       : adventDay16problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day16/input01.txt";
  int problem = 2;

  if (argc == 2)
  {
    if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2))
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
    if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
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