#include "donut.h"


uint64_t adventDay20problem12019(std::ifstream& input)
{
  std::vector<std::vector<char>> map = parseInputChars(input);

  std::map<std::string, std::pair<Coordinate, Coordinate>> portals;
  Coordinate start, end;

  findPortals(map, portals, start, end);

	return steps(map, portals, start, end);
}


uint64_t adventDay20problem22019(std::ifstream& input)
{
  std::vector<std::vector<char>> map = parseInputChars(input);

  std::map<std::string, std::pair<Coordinate2, Coordinate2>> portals;
  Coordinate2 start, end;

  findPortals2(map, portals, start, end);

	return steps2(map, portals, start, end);
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "20";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay20problem12019(inputFile); break;
    case 2: result = adventDay20problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}