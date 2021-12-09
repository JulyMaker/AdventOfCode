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


std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != std::string::npos) {
    if (end != start)
      tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != std::string::npos)
    tokens.push_back(text.substr(start));
  return tokens;
}

long long adventDay08problem12021(std::ifstream& is)
{
  std::string line;
  long long total = 0;

  while (!is.eof())
  {
    std::getline(is, line);
    if (line != "")
    {  
      line = line.substr(line.find("|") + 1);
      std::vector<std::string> nums = split(line, " ");
      for (auto& n : nums)
      {
        int siz = n.size();
        total += (siz == 2 || siz == 3 || siz == 4 || siz == 7) ? 1 : 0;
      }
    }  
  }
  is.close();
  
  return total;
}

void numberCode()
{
  

}


void numberDecode(std::vector<std::string>& numCode, std::vector<std::string>& code)
{
  // 6 segm [0,6,9] (nine contain FOUR no 0 no 6, 0 contain SEVEN no 6 no 9 )
  // 5 segm [2,3,5] (three contain ONE no 2 no 5, 5 contain 4 - 1seg no 2)

  std::vector<std::string> seg5, seg6;
  std::string one = "";
  std::string four = "";
  std::string seven = "";

  for (auto& numString : numCode)
  {
    int size = numString.size();
    switch (size)
    {
      case 2:
        code[1] = numString;
        one = numString;
        break;
      case 3:
        code[7] = numString;
        seven = numString;
        break;
      case 4:
        code[4] = numString;
        four = numString;
        break;
      case 7:
        code[8] = numString;
        break;
      case 5:
        seg5.push_back(numString);
        break;
      case 6:
        seg6.push_back(numString);
        break;
      default:
        break;
    }
  }
  
  // Seg5
  for (auto& seg : seg5)
  {
    bool found = true;
    for (auto& s : one)
    {
      if (seg.find(s) == std::string::npos)
      {
        found = false;
        break;
      }
    }
    if (found) { code[3] = seg; continue; }

    int count = 0;
    for (auto& s : four)
    {
      if (seg.find(s) != std::string::npos)
        count++;
    }
    if (count == 3)
      code[5] = seg;
    else
      code[2] = seg;
  }

  // Seg6
  for (auto& seg : seg6)
  {
    bool found = true;
    for (auto& s : four)
    {
      if (seg.find(s) == std::string::npos)
      {
        found = false;
        break;
      }      
    }
    if (found) { code[9] = seg; continue; }

    found = true;
    for (auto& s : seven)
    {
      if (seg.find(s) == std::string::npos)
      {
        found = false;
        break;
      }
    }
    if(found)
      code[0] = seg;
    else
      code[6] = seg;
  }
}

bool contain(std::string a1, std::string a2)
{
  bool found = true;

  for (auto& s : a2)
  {
    if (a1.find(s) == std::string::npos)
    {
      found = false;
      break;
    }
  }

  return found;
}

int decodeResult(const std::string numString, std::vector<std::string>& code)
{
  int size = numString.size();
  switch (size)
  {
    case 2:
      return 1;
      break;
    case 3:
      return 7;
      break;
    case 4:
      return 4;
      break;
    case 7:
      return 8;
      break;
    case 5:
      return (contain(numString, code[2])) ? 2 : ((contain(numString, code[5])) ? 5 : 3);
      break;
    case 6:
      return (contain(numString, code[0])) ? 0 : ((contain(numString, code[6])) ? 6 : 9);
      break;
    default:
      break;
  }
}

long long adventDay08problem22021(std::ifstream& is)
{
  std::string line;
  std::string subsrtring;
  long long total = 0;

  while (!is.eof())
  {
    std::getline(is, line);
    if (line != "")
    {
      // Number code
      subsrtring = line.substr(0, line.find("|") - 1);
      std::vector<std::string> numCode = split(subsrtring, " ");
      std::vector<std::string> code (10);

      numberDecode(numCode, code);

      // Decode result
      subsrtring = line.substr(line.find("|") + 1);
      std::vector<std::string> nums = split(subsrtring, " ");
      
      long lineResult = 0;
      for (auto& numString : nums)
      {   
        lineResult = lineResult*10 + decodeResult(numString, code);
      }

      total += lineResult;
    }
  }
  is.close();

  return total;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);

  long long result = (problNumber == 1) ? adventDay08problem12021(infile)
                                        : adventDay08problem22021(infile);

  return result;
}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
  std::string fileName = "../../Day08/input01.txt";
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