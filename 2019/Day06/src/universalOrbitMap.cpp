#include <utils.h>


uint64_t adventDay06problem12019(std::ifstream& input)
{
	std::vector<std::string> lines = parseInput<std::string>(input);

	std::unordered_map<std::string, std::string> orbitMap;
	for (auto& l : lines)
	{
		std::vector<std::string> split =  splitS(l, ")");
		orbitMap[split[1]] = split[0];
	}
		
	const auto traverse = [&orbitMap]
	(std::string Start, std::function<void(std::string&)> Proc) -> void
	{
		for (std::string CurPlanet = Start; orbitMap.count(CurPlanet); CurPlanet = orbitMap.at(CurPlanet)) 
			Proc(CurPlanet);
	};

	std::size_t orbitTransfers = 0;
	for (const auto& Orbit : orbitMap) 
		traverse(Orbit.first, [&](std::string&) {++orbitTransfers; });

	
	return orbitTransfers;
}

uint64_t adventDay06problem22019(std::ifstream& input)
{
	std::vector<std::string> lines = parseInput<std::string>(input);

	std::unordered_map<std::string, std::string> orbitMap;
	for (auto& l : lines)
	{
		std::vector<std::string> split = splitS(l, ")");
		orbitMap[split[1]] = split[0];
	}

	const auto traverse = [&orbitMap]
	(std::string Start, std::function<void(std::string&)> Proc) -> void
	{
		for (std::string CurPlanet = Start; orbitMap.count(CurPlanet); CurPlanet = orbitMap.at(CurPlanet))
			Proc(CurPlanet);
	};

	std::set<std::string> YouGraph;
	std::set<std::string> SanGraph;
	traverse("YOU", [&](std::string& CurPlanet) { YouGraph.insert(CurPlanet); });
	traverse("SAN", [&](std::string& CurPlanet) { SanGraph.insert(CurPlanet); });

	std::set<std::string>xor;
	std::set_symmetric_difference(
		YouGraph.begin(), YouGraph.end(), SanGraph.begin(), SanGraph.end(), std::inserter(xor, xor.end()));

  return xor.size() - 2;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "06";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay06problem12019(inputFile); break;
    case 2: result = adventDay06problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}