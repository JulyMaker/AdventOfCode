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



long long adventDay25problem1(std::pair<int, int> public_keys, const int value)
{
  long long loopSize1 = 0;
  long long loopSize2 = 0;

  long long number = 7;
  long long subjectNum = 1;
  while(subjectNum != public_keys.first && ++loopSize1)
  {
    subjectNum *= number;
    subjectNum %= value;
  }

  number = 7;
  subjectNum = 1;
  while (subjectNum != public_keys.second && ++loopSize2)
  {
    subjectNum *= number;
    subjectNum %= value;
  }

  number = 1;
  subjectNum = public_keys.second;
  for(int i=0; i< loopSize1; ++i)
  {
    number *= subjectNum;
    number %= value;
  }

  return number;
}

long long adventDay25problem2(std::pair<int, int> public_keys, const int value)
{
  return 0;
}

long long int readFile(std::string file, int problNumber)
{
  //std::ifstream infile(file);
  //std::string line;

  int result=0;
  std::pair<int, int> public_keys{ 8987316 , 14681524 };
  //std::pair<int, int> public_keys{ 5764801 , 17807724 };
  
  const int value = 20201227;

  //while (!infile.eof())
  //{
  //  std::getline(infile, line);
  //  if (line == "") continue;
  //
  //  adventDay24problem1(line, v, result);                    
  //}
  //infile.close();

  return (problNumber == 1)? adventDay25problem1(public_keys, value)
                           : adventDay25problem2(public_keys, value);

}

int main(int argc, char *argv[])
{
  // argv contain *.txt path
 if (argc < 2)
 {
   std::cout << "ERROR: problem number missing" << std::endl;
   return -1;
 }
 else if ((std::stoi(argv[1]) < 1) || (std::stoi(argv[1]) > 2))
 {
   std::cout << "Problem 1 or 2" << std::endl;
   return -1;
 }

 long long int result = 0;
 switch (std::stoi(argv[1]))
 {
 case 1:
   result = readFile(argv[1], 1);
   break;
 case 2:
   result = readFile(argv[1], 2);
   break;
 default:
   std::cout << "The number problem isn't right" << result << std::endl;
 }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}