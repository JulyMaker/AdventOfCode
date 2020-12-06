#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>

int adventDay6problem1(std::vector<std::string>& groupForm)
{
  std::set<char> yesanswers;

  for (int i = 0; i < groupForm.size(); ++i)
  {
    for (int j = 0; j < groupForm[i].size(); ++j)
    {
      yesanswers.insert(groupForm[i][j]);
    }
  }

  return yesanswers.size();
}


int adventDay6problem2(std::vector<std::string>& groupForm)
{

  std::set<char> yesIntersection;
  std::set<char> yesanswers1;
  std::set<char> yesanswers2;

  for (int i = 0; i < groupForm.size(); ++i)
  {
    for (int j = 0; j < groupForm[i].size(); ++j)
    {
      if (i == 0)
      {
        yesanswers1.insert(groupForm[i][j]);
      }
      else
      {
        if (j == 0) yesanswers2.clear();
        yesanswers2.insert(groupForm[i][j]);
      }
    }

    if (i != 0)
    {
      yesIntersection.clear();

      std::set_intersection(yesanswers1.begin(), yesanswers1.end(),
        yesanswers2.begin(), yesanswers2.end(),
        std::inserter(yesIntersection, yesIntersection.end()));

      yesanswers1.clear();
      yesanswers1 = yesIntersection;
      yesanswers2.clear();
    }
  }
  
  return yesanswers1.size();
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  int count = 0;

  std::vector<std::string> groupForm;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "")
    {
      count += (problNumber == 1) ? adventDay6problem1(groupForm)
        : adventDay6problem2(groupForm);
      groupForm.clear();

    }
    else
    {
      groupForm.push_back(line);
    }
  }
  infile.close();

  return count;
}

int main(int argc, char *argv[])
{
  // argv contain inputDeclarationForm.txt path
  if (argc < 3)
  {
    std::cout << "ERROR: inputDeclarationForm.txt path or problem number missing" << std::endl;
    return -1;
  }
  else if ((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2))
  {
    std::cout << "Problem 1 or 2" << std::endl;
    return -1;
  }

  long long int result = 0;
  switch (std::stoi(argv[2]))
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