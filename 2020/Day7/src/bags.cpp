#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>

#define MYBAG "shiny gold"

void processLine(std::vector<std::pair<std::string, std::vector<std::string>>>& bags,
  std::map<std::string, bool>& bagMaps, std::vector<std::string>& lines)
{
  //light salmon bags contain 5 dark brown bags, 2 dotted coral bags, 5 mirrored turquoise bags.
  const std::string noBags = "no other";
  std::smatch sm;
  std::regex regExp1("(.*) bags contain (\\d+)* (.*) bag(s)*");
  std::regex regExp2("\\d+ (.*) bag(s)*(.)*");

  std::string colorName = "";
  std::vector<std::string> containBags;

  if (regex_search(lines[0], sm, regExp1))
  {
    colorName = sm[1].str();

    if (sm[3].str() != noBags)
    {
      containBags.push_back(sm[3].str());
    }

    if (sm[3].str() == MYBAG)bagMaps[colorName]=true;
  }

  for(int i=1; i< lines.size();++i)
  {
    if (regex_search(lines[i], sm, regExp2))
    {
      containBags.push_back(sm[1].str());
      if (sm[1].str() == MYBAG)bagMaps[colorName] = true;
    }
  }

  if (containBags.size() > 0) bags.push_back(std::make_pair(colorName, containBags));
}

void processLine(std::map<std::string, std::vector<std::pair<std::string,int>>>& bags, std::vector<std::string>& lines)
{
  //light salmon bags contain 5 dark brown bags, 2 dotted coral bags, 5 mirrored turquoise bags.
  const std::string noBags = "no other";
  std::smatch sm;
  std::regex regExp1("(.*) bags contain (\\d+)* (.*) bag(s)*");
  std::regex regExp2("(\\d+) (.*) bag(s)*(.)*");

  std::string colorName = "";
  std::vector<std::pair<std::string, int>> containBags;

  if (regex_search(lines[0], sm, regExp1))
  {
    colorName = sm[1].str();

    if (sm[3].str() != noBags)
    {
      containBags.push_back(std::make_pair(sm[3].str(), std::stoi(sm[2].str())));
    }
  }

  for (int i = 1; i < lines.size(); ++i)
  {
    if (regex_search(lines[i], sm, regExp2))
    {
      containBags.push_back(std::make_pair(sm[2].str(), std::stoi(sm[1].str()))); 
    }
  }

  bags[colorName] = containBags;
}

int adventDay7problem1(std::vector<std::pair<std::string, std::vector<std::string>>>& bags, std::map<std::string, bool>& bagMaps)
{
  int countTotal = 0;
  int count = 1;

  do
  {
    countTotal = count;
    count = 0;
    for (int i = 0; i < bags.size(); ++i)
    {
      for (int j = 0; j < bags[i].second.size(); ++j)
      {
        if (bagMaps[bags[i].second[j]] == true)
        {
          bagMaps[bags[i].first] = true;
          break;
        }
      }
    }

    for (const auto &x : bagMaps)
      count += x.second;

  } while ((countTotal != count));
  

  return countTotal;
}


int adventDay7problem2(std::string colorName, std::map<std::string, std::vector<std::pair<std::string, int>>>& bags)
{
  long long int count = 0;

  if (bags[colorName].size() == 0) return 0;

  for(int i =0; i < bags[colorName].size(); ++i)
  {
    int num = bags[colorName][i].second;
    std::string name = bags[colorName][i].first;

    count += num + num* adventDay7problem2(name, bags);
  }
   
  return count;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;

  std::vector<std::pair<std::string,std::vector<std::string>>> bags;
  std::map<std::string, std::vector<std::pair<std::string, int>>> bags2;
  std::map<std::string,bool> bagMaps;
  std::vector<std::string> lines;

  while (!infile.eof())
  {
    std::getline(infile, line);

    if (line == "") continue;
    std::stringstream lineAux(line);
    std::string saux;

    while (getline(lineAux, saux, ','))
    {
      lines.push_back(saux);
    }   

    (problNumber == 1) ? processLine(bags, bagMaps, lines)
                       : processLine(bags2, lines);

    lines.clear();
  }
  infile.close();

  return (problNumber == 1) ? adventDay7problem1(bags, bagMaps)
                            : adventDay7problem2(MYBAG, bags2);
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