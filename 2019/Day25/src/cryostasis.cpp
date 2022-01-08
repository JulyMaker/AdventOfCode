#include "../Day15/include/system.h"

#define INI "0"
#define POS "X"
#define ITM "#"
#define ERR "!"
#define PAT "_"

static bool allItems = false;

void addN(std::string& inst, std::vector<std::vector<std::string>>& map, std::pair<int, int>& pos)
{
	bool item = false;
	bool errorItem = false;
	std::pair<int, int> beforePos;

	if (allItems)
	{
		beforePos = pos;
	}

	switch (inst[0])
	{
	case 'n':
		inst = "north\n";
		pos.second -= 1;
		break;
	case 's':
		inst = "south\n";
		pos.second += 1;
		break;
	case 'e':
		inst = "east\n";
		pos.first += 1;
		break;
	case 'w':
		inst = "west\n";
		pos.first -= 1;
		break;
	case '0':
		inst += "\n";
		errorItem = true;
		break;
	case 'a':
		inst += "\n";
		allItems = true;
		break;
	default:
		inst += "\n";
		if (inst != "inv\n" && inst != "print\n")
			item = true;
		break;
	}

	if (allItems)
	{
		pos = beforePos;
	}

	if (map[pos.second][pos.first] != ITM && map[pos.second][pos.first] != ERR && map[pos.second][pos.first] != INI)
	{
		if (item)
			map[pos.second][pos.first] = ITM;
		else if (errorItem)
			map[pos.second][pos.first] = ERR;
		else
			map[pos.second][pos.first] = PAT;
	}
}

void initQueue(const std::string& s, std::queue<int64_t>& cin, std::vector<std::vector<std::string>>& map, std::pair<int, int>& pos)
{
	std::string aux = s;
	addN(aux, map, pos);

  for (int it = 0; it < aux.size(); it++)
  {
    cin.push((int64_t)aux[it]);
  }
}

void printMap(std::vector<std::vector<std::string>>& map, std::pair<int, int>& pos)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			if(j == pos.first && i == pos.second)
				std::cout << POS;
			else
				std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
		
}

void takeIt(std::vector<std::string> items, std::queue<int64_t>& cin, std::vector<std::vector<std::string>>& map, std::pair<int, int>& pos)
{
	for (auto& i : items)
		initQueue("take " + i, cin, map, pos);
}

void dropAll(std::vector<std::string> items, std::queue<int64_t>& cin, std::vector<std::vector<std::string>>& map, std::pair<int, int>& pos)
{
	for (auto& i : items)
		initQueue("drop " + i, cin, map, pos);
}
uint64_t adventDay25problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	std::queue<int64_t> cin;
	std::vector<std::string> items = {"mutex", "loom", "semiconductor", "ornament", "sand", "asterisk", "wreath", "dark matter"}; // Manual items found

	const int SIZE = 14;

	std::vector<std::vector<std::string>> map;
	map.resize(SIZE, std::vector<std::string>(SIZE, " "));
	map[SIZE / 2][SIZE / 2] = INI;

	std::pair<int, int> pos = std::make_pair(SIZE / 2, SIZE / 2);

// My map, manual way

initQueue("n", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("take mutex", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("0", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("take loom", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("take semiconductor", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("take ornament", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("0", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("0", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("0", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("take sand", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("0", cin, map, pos); // molten lava
initQueue("e", cin, map, pos);
initQueue("take asterisk", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("take wreath", cin, map, pos);
initQueue("s", cin, map, pos);
initQueue("w", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("n", cin, map, pos);
initQueue("take dark matter", cin, map, pos);
initQueue("e", cin, map, pos);
initQueue("a", cin, map, pos);
dropAll(items, cin, map, pos);
/*
initQueue("take mutex", cin, map, pos);
initQueue("take loom", cin, map, pos);
initQueue("take sand", cin, map, pos);
initQueue("take wreath", cin, map, pos);
*/

int64_t currPos = 0;
int64_t posMode1 = 0;
int64_t posMode2 = 0;
int64_t posMode3 = 0;
int64_t relativeBase = 0;

while (integers[currPos] != 99)
{
	setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3, integers[currPos] % 100);

	switch (integers[currPos] % 100)
	{
	  case 1:
	  	integers[posMode3] = integers[posMode2] + integers[posMode1];	currPos += 4;
	  	break;
	  
	  case 2:
	  	integers[posMode3] = integers[posMode2] * integers[posMode1];	currPos += 4;
	  	break;
	  
	  case 3:
	  	if (cin.empty())
	  	{
				//----- Automatic -----//
	  		std::vector<std::string> takeI;
	  		for (int a = 0; a < std::pow(2, items.size()); ++a) // a in range(2 * *len(items)) :
	  		{
	  			std::vector<std::string> takeI = {};
	  			for (int i = 0; i < items.size(); ++i) // i in range(len(items)) :
	  			{
	  				if (((a >> i) & 1) == 1)
	  				{
	  					takeI.push_back(items[i]);
	  				}	
	  			}		
	  		
	  			takeIt(takeI, cin, map, pos);
	  			initQueue("e", cin, map, pos);
	  			dropAll(takeI, cin, map, pos);
	  		}
	  			
				// ---- Manual ----- //
	  	  //std::string aux;
	  	  //std::cout << "$ ";
	  	  //std::getline(std::cin, aux);
	  	  //
	  	  //if (aux == "print")	printMap(map, pos);
	  	  //
	  	  //initQueue(aux, cin, map, pos);
	  	}
	  
	  		integers[posMode1] = cin.front(); cin.pop();             currPos += 2;
	  		break;
	  	
	  	case 4:
	  		std::cout << (char)integers[posMode1];		  	           currPos += 2;
	  		break;
	  	
	  	case 5:
	  		currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
	  		break;
	  	
	  	case 6:
	  		currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
	  		break;
	  	
	  	case 7:
	  		integers[posMode3] = integers[posMode1] < integers[posMode2]; currPos += 4;
	  		break;
	  	
	  	case 8:
	  		integers[posMode3] = integers[posMode1] == integers[posMode2];currPos += 4;
	  		break;
	  	
	  	case 9:
	  		relativeBase += integers[posMode1];                   		  	currPos += 2;
	  		break;
	  }
	}

	return 0;
}


uint64_t adventDay25problem22019(std::ifstream& input)
{
	std::cout << "Happy Advent of Code 2019!" << std::endl;
	return 0;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 1;
  std::string day = "25";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay25problem12019(inputFile); break;
    case 2: result = adventDay25problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}