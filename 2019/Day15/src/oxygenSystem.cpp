#include <system.h>


uint64_t adventDay15problem12019(std::ifstream& input)
{
  std::vector<int64_t> integers = parseInputInt64(input,',');

  std::vector<std::vector<char>> map(5000, std::vector<char>(5000, '-'));
  Coordinate coord = findOxygenSystem(integers, map);

	return BFS(map, coord);
}

uint64_t adventDay15problem22019(std::ifstream& input)
{
  std::vector<int64_t> integers = parseInputInt64(input, ',');

  std::vector<std::vector<char>> map(5000, std::vector<char>(5000, '-'));
  Coordinate coord = findOxygenSystem(integers, map);

  return BFS2(map, coord);
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "15";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay15problem12019(inputFile); break;
    case 2: result = adventDay15problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}