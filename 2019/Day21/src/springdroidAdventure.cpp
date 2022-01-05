#include "../Day15/include/system.h"

std::vector<int> intCodeProgram(std::vector<int64_t>& integers, std::queue<int64_t>& input)
{
	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;
	std::vector<int> cout;

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
		  	integers[posMode1] = input.front();
		  	input.pop();
		  	currPos = currPos + 2;
		  	break;
		  
		  case 4:
		  	if (integers[posMode1] > 127)
		  	{
					cout.push_back(integers[posMode1]);
		  	}
		  	currPos = currPos + 2;
		  	break;
		  
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

	return cout;
}


void initQueue(const std::string& s, std::queue<int64_t>& input)
{
	for (int it = 0; it < s.size(); it++)
		input.push((int64_t)s[it]);
}

uint64_t adventDay21problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	std::queue<int64_t> cin;

	// (!A || !B || !C) && D
	// If we have a hole (one tile away or two tiles away or three tiles away) and the forth tile where
	// we will land after jumping is ground then we jump
	initQueue("NOT A T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("NOT B T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("NOT C T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("AND D J\n", cin);

	initQueue("WALK\n", cin);

	std::vector<int> result = intCodeProgram(integers, cin);

	return vectorToInt(result);
}


uint64_t adventDay21problem22019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	std::queue<int64_t> cin;

	// ((!A || !B || !C) && D) && (H || E)
	// If I can jump again or walk forward one tile after jumping then jump
	initQueue("NOT A T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("NOT B T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("NOT C T\n", cin);
	initQueue("OR T J\n", cin);
	initQueue("AND D J\n", cin);

	initQueue("NOT H T\n", cin);
	initQueue("NOT T T\n", cin);
	initQueue("OR E T\n", cin);
	initQueue("AND T J\n", cin);

	initQueue("RUN\n", cin);

	std::vector<int> result = intCodeProgram(integers, cin);


	return vectorToInt(result);
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "21";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay21problem12019(inputFile); break;
    case 2: result = adventDay21problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}