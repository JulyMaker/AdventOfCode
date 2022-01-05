#include "../Day15/include/system.h"

bool intCodeProgram(std::vector<int64_t> integers, int64_t cin, const int x, const int y)
{
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
		  	integers[posMode3] = integers[posMode2] + integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 2:
		  	integers[posMode3] = integers[posMode2] * integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 3:
				cin = (cin == -1) ? x : y;
		  	integers[posMode1] = cin;
		  	currPos = currPos + 2;
		  	break;
		  
		  case 4:
		  	return integers[posMode1];
		  
		  case 5:
		  	currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 6:
		  	currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 7:
		  	integers[posMode3] = integers[posMode1] < integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 8:
		  	integers[posMode3] = integers[posMode1] == integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 9:
		  	relativeBase += integers[posMode1];
		  	currPos = currPos + 2;
		  	break;
		}
	}
}

uint64_t adventDay19problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	int64_t cin = -1;
	int pointsAffected = 0;

	for (int x = 0; x < 50; x++)
	{
		for (int y = 0; y < 50; y++)
		{
			if (intCodeProgram(integers, cin, x, y))
			{
				pointsAffected++;
			}
		}
	}

	return pointsAffected;
}


uint64_t adventDay19problem22019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	int64_t cin = -1;
	int x = 25, y = 20;

	while (true)
	{
		if ((!intCodeProgram(integers, cin, x, y)) || (!intCodeProgram(integers, cin, x, y + 99)))
		{
			x++;
			while (!intCodeProgram(integers, cin, x, y))
			{
				y++;
			}
			continue;
		}

		if (!intCodeProgram(integers, cin, x + 99, y))
		{
			y++;
			continue;
		}

		return x * 10000 + y;
	}

	return 0;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "19";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay19problem12019(inputFile); break;
    case 2: result = adventDay19problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}