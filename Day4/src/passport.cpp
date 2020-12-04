#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <map>

int adventDay4problem1(std::vector<std::string>& passport)
{
    // byr(Birth Year)       iyr(Issue Year)
    // eyr(Expiration Year)  hgt(Height)
    // hcl(Hair Color)       ecl(Eye Color)
    // pid(Passport ID)      cid(Country ID)
  //std::vector<std::string> passp{ "byr" ,"iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
  std::map<std::string, unsigned int> map{ {"byr", 1}, {"iyr", 2}, {"eyr", 4}, {"hgt", 8},
                                  {"hcl", 16}, {"ecl", 32}, {"pid", 64} };
  
  std::smatch sm;
  std::regex regExp("(\\w+):(.*)");
  
  unsigned int passportCode = 0000000;

  for(int i=0; i< passport.size(); ++i)
  {
    if(regex_search(passport[i], sm, regExp))
    {     
      passportCode |= map[sm[1].str()];
    }
  }

  return passportCode == 127;
}

bool validPass(unsigned int code, std::string validation)
{
    //byr(Birth Year) - four digits; at least 1920 and at most 2002.
    //iyr(Issue Year) - four digits; at least 2010 and at most 2020.
    //eyr(Expiration Year) - four digits; at least 2020 and at most 2030.
    //hgt(Height) - a number followed by either cm or in:
    //      If cm, the number must be at least 150 and at most 193.
    //      If in, the number must be at least 59 and at most 76.
    //hcl(Hair Color) - a # followed by exactly six characters 0 - 9 or a - f.
    //ecl(Eye Color) - exactly one of : amb blu brn gry grn hzl oth.
    //pid(Passport ID) - a nine - digit number, including leading zeroes.
    //cid(Country ID) - ignored, missing or not.

  std::smatch sm;
  std::regex regExp1("(\\d+)cm");
  std::regex regExp2("(\\d+)in");
  std::regex regExp3("#[0-9a-z]{6}");
  std::regex regExp4("[0-9]{9}$");
  int year = 0;
  int height = 0;

  switch (code)
  {
    case 0:
      return true;
    break;
    case 1:
        year = std::stoi(validation);
        return (year >= 1920 && year <= 2002) ?  true : false;
      break;
    case 2:
        year = std::stoi(validation);
        return (year >= 2010 && year <= 2020) ? true : false;
      break;
    case 4:
        if (validation.size() != 4) return false;
        year = std::stoi(validation);
        return (year >= 2020 && year <= 2030) ? true : false;
      break;
    case 8:
        return ((regex_search(validation, sm, regExp1))? 
               (std::stoi(sm[1].str()) >= 150 && std::stoi(sm[1].str()) <= 193) : false) ||
               ((regex_search(validation, sm, regExp2))? 
               (std::stoi(sm[1].str()) >= 59 && std::stoi(sm[1].str()) <= 76) : false);
      break;
    case 16:
        return regex_match(validation, sm, regExp3) ? true: false;
      break;
    case 32:
        return (validation=="amb" || validation=="blu" || 
                validation=="brn" || validation=="gry" || 
                validation=="grn" || validation=="hzl" || validation== "oth") ? true : false;
      break;
    case 64:
      return regex_match(validation, sm, regExp4) ? true : false;
      break;
    default:
      return false;

  }
}

int adventDay4problem2(std::vector<std::string>& passport)
{
  std::map<std::string, unsigned int> map{ {"cid", 0}, {"byr", 1}, {"iyr", 2}, {"eyr", 4}, 
                                           {"hgt", 8}, {"hcl", 16}, {"ecl", 32}, {"pid", 64} };

  std::smatch sm;
  std::regex regExp("(\\w+):(.*)");

  unsigned int passportCode = 0000000;

  for (int i = 0; i < passport.size(); ++i)
  {
    if (regex_search(passport[i], sm, regExp))
    {
      if (validPass(map[sm[1].str()], sm[2].str()))
        passportCode |= map[sm[1].str()];
      else
        break;
    }
  }

  return passportCode == 127;
}

long long int readFile(std::string file, int problNumber)
{
  std::ifstream infile(file);
  std::string line;
  std::string saux;

  std::vector<std::string> passport;
  unsigned int count = 0;

  while (!infile.eof()) 
  {
    std::getline(infile, line);

    if (line == "")
    {
      count += (problNumber == 1) ? adventDay4problem1(passport)
                                  : adventDay4problem2(passport);
      passport.clear();
     }    
     else
    {
      std::stringstream lineAux(line);
      while (getline(lineAux, saux, ' '))
      {
        passport.push_back(saux);
      }
    }
  }
  infile.close();

  return count;
}

int main(int argc, char *argv[])
{
  // argv contain inputTobogan.txt path
  if(argc < 3)
  {
    std::cout << "ERROR: inputTobogan.txt path or problem number missing" << std::endl;
    return -1;
  }else if((std::stoi(argv[2]) < 1) || (std::stoi(argv[2]) > 2) )
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