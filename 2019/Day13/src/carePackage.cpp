#include <utils.h>

void setPosModes(std::vector<int64_t>& integers, int64_t currPos, int64_t relativeBase, int64_t& posMode1, int64_t& posMode2, int64_t& posMode3, int64_t opcode)
{
	if (currPos + 3 >= integers.size())
	{
		integers.resize(currPos + 4);
	}

	switch (integers[currPos] / 100 % 10)
	{
	  case 0:
	  	posMode1 = integers[currPos + 1];
	  	break;
	  
	  case 1:
	  	posMode1 = currPos + 1;
	  	break;
	  
	  case 2:
	  	posMode1 = relativeBase + integers[currPos + 1];
	  	break;
	}

	switch (integers[currPos] / 1000 % 10)
	{
	  case 0:
	  	posMode2 = integers[currPos + 2];
	  	break;
	  
	  case 1:
	  	posMode2 = currPos + 2;
	  	break;
	  
	  case 2:
	  	posMode2 = relativeBase + integers[currPos + 2];
	  	break;
	}

	switch (integers[currPos] / 10000 % 10)
	{
	  case 0:
	  	posMode3 = integers[currPos + 3];
	  	break;
	  
	  case 1:
	  	posMode3 = currPos + 3;
	  	break;
	  
	  case 2:
	  	posMode3 = relativeBase + integers[currPos + 3];
	  	break;
	}

	if (posMode1 >= integers.size())
		integers.resize(posMode1 + 1);

	if (posMode2 >= integers.size() && ((opcode == 1) || (opcode == 2) || (opcode == 5) || (opcode == 6) || (opcode == 7) || (opcode == 8)))
		integers.resize(posMode2 + 1);

	if ((posMode3 >= integers.size()) && ((opcode == 1) || (opcode == 2) || (opcode == 7) || (opcode == 8)))
		integers.resize(posMode3 + 1);
}


uint64_t adventDay13problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');

	std::vector<std::vector<int>>map(200, std::vector<int>(200, -1));
	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;

	const int cin = 1;
	int left = 0, top = 0, itOutput = 0;

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
			integers[posMode1] = cin;
			currPos = currPos + 2;
			break;

		case 4:
			if (itOutput == 0)
			{
				left = integers[posMode1];
			}
			else
			{
				if (itOutput == 1)
				{
					top = integers[posMode1];
				}
				else
				{
					map[top][left] = integers[posMode1];
				}
			}
			itOutput = (itOutput + 1) % 3;
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

	int64_t countBlocks = 0;

	for (int l = 0; l < 200; l++)
		for (int c = 0; c < 200; c++)
			if (map[l][c] == 2)
				countBlocks++;

	return countBlocks;
}

uint64_t adventDay13problem22019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	integers[0] = 2;

	std::vector<std::vector<int>>map(2000, std::vector<int>(2000, -1));
	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;

	int64_t cin = 0;
	int left = 0, top = 0, itOutput = 0;
	int horizPaddlePos = 0, ballPos = 0;
	int score = 0;
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
		  	cin = (horizPaddlePos == ballPos) ? 0 : (horizPaddlePos < ballPos) ? 1 : -1;
		  	integers[posMode1] = cin;
		  	currPos = currPos + 2;
		  	break;
		  
		  case 4:
		  	if (itOutput == 0)
		  	{
		  		left = integers[posMode1];
		  	}
		  	else
		  	{
		  		if (itOutput == 1)
		  		{
		  			top = integers[posMode1];
		  		}
		  		else
		  		{
		  			if ((left == -1) && (top == 0))
		  			{
		  				score = integers[posMode1];
		  			}
		  			else
		  			{
		  				map[top][left] = integers[posMode1];
		  				if (integers[posMode1] == 3)
		  				{
		  					horizPaddlePos = left;
		  				}
		  				else
		  				{
		  					if (integers[posMode1] == 4)
		  					{
		  						ballPos = left;
		  					}
		  				}
		  			}
		  		}
		  	}
		  	itOutput = (itOutput + 1) % 3;
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

  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "13";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay13problem12019(inputFile); break;
    case 2: result = adventDay13problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}