#include "proboscideaVolcanium.h"

const int STEPS = 30;
const int DISCONST = 60;

struct Valve
{
  int rate;
  std::vector<std::string> tunnels;
};

bool compare(std::pair<std::string, int>& a, std::pair<std::string, int>& b)
{
  return a.second > b.second;
}

// bit is 1 if valve is opened, and 0 otherwise
int findMaxPressure(int time, int pos, std::string opened, int distance[DISCONST][DISCONST],
  const std::vector<Valve>& valves, const std::vector<int>& usefulValveIds,
  std::map<std::string, int> mem[STEPS])
{
  if (mem[time].count(opened) == 1)
  {
    return mem[time][opened];
  }
  
  int maxPressure = 0;
  int nextId = 0;
  int nextTime = 0;
  int nextPressure = 0;

  for (int next = 0; next < usefulValveIds.size(); next++)
  {
    if (opened[next] == '1')
    {
      continue;
    }

    nextId = usefulValveIds[next];
    nextTime = time + distance[pos][nextId] + 1;
    if (nextTime >= STEPS)
    {
      continue;
    }
  
    Valve next_valve = valves[nextId];
    nextPressure = (STEPS - nextTime) * next_valve.rate;

    std::string nextOpened = opened;
    nextOpened[next] = '1';

    // recursively compute max pressure
    nextPressure += findMaxPressure(nextTime, nextId, nextOpened, distance, valves, usefulValveIds, mem);

    maxPressure = std::max(maxPressure, nextPressure);
  }

  // memize result and return
  mem[time][opened] = maxPressure;
  return maxPressure;
}

uint64_t adventDay16problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::map<std::string, int> mem[STEPS];

  std::vector<Valve> valves;
  std::map<std::string, int> valveIds;
  std::vector<int> usefulValveIds;

  int distance[DISCONST][DISCONST] = { 0 };

  std::vector<std::string> in = parseInputReg(input, "Valve (\\w+) has flow rate=(\\d+); tunnels? leads? to valves? (.*)");
  int valveId = 0;
  for (int i=0; i < in.size() - 3; i+=4)
  {
    std::string vName = in[i + 1];
    Valve currValve = { stoi(in[i + 2]), splitS(in[i + 3], ", ")};

    // store the current valve
    valveIds[vName] = valveId;
    valves.push_back(currValve);

    // call the current valve "useful" if it has a positive rate
    if (currValve.rate > 0)
    {
      usefulValveIds.push_back(valveId);
    }

    valveId++;
  }
  
  const int n_valves = valveId;

  // init distance array with a large value, and set initial distances between adjacent valves to 1
  for (int row = 0; row < n_valves; row++)
  {
    for (int col = 0; col < n_valves; col++)
      distance[row][col] = n_valves + 100;

    for (std::string vname : valves[row].tunnels)
    {
      int vid = valveIds[vname];
      distance[row][vid] = 1;
      distance[vid][row] = 1;
    }
  }

  // use Floyd-Warshall to find all-pairs shortest path between all valves
  for (int k = 0; k < n_valves; k++)
    for (int i = 0; i < n_valves; i++)
      for (int j = 0; j < n_valves; j++)
        distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);


  std::string init = "";
  for (int x = 0; x < usefulValveIds.size(); x++) // get zero bitstring corresponding to # useful vaults
  {
    init += "0";
  }

  // find max pressure
  score = findMaxPressure(0, valveIds["AA"], init, distance, valves, usefulValveIds, mem);

  return score;
}

int64_t maxReleased(const dists& distances, const flowRates& rates, int start, int maxMinutes, bool elephant) 
{
  std::vector<bool> open(rates.size(), false);
  std::unordered_map<int64_t, int64_t> memo;

  explorer e{ .valve = start, .remaining = 0, .free = true };

  return maxReleased(distances, rates, { e, e }, 1, maxMinutes, open, memo, elephant);
}

uint64_t adventDay16problem22022(std::ifstream& input)
{
  uint64_t score = 0;

  // WARNING: 6 min to calculate input, no example

  flowRatesMap rates;
  connectionsMap conns;

  std::vector<std::string> in = parseInputReg(input, "Valve (\\w+) has flow rate=(\\d+); tunnels? leads? to valves? (.*)");
  for (int i = 0; i < in.size() - 3; i += 4)
  {
    const std::string vName = in[i + 1];
    rates[vName] = stoi(in[i + 2]);
    conns[vName] = splitS(in[i + 3], ", ");
  }

  auto edges = shortestDists(rates, conns);
  auto [flowRates, distances, start] = prune(rates, edges);

  std::cout << maxReleased(distances, flowRates, start, 26, true) << std::endl;

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "16";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay16problem12022(inputFile); break;
    case 2: result = adventDay16problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}