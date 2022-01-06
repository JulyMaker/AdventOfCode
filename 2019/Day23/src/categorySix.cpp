#include "../Day15/include/system.h"

class NIC
{
public:
  NIC(std::vector<int64_t> integers = {}, int64_t currPos = 0) : integers(integers), currPos(currPos) {}

public:
  std::vector<int64_t> integers;
  std::queue<int64_t> q;
  int64_t currPos;
};

uint64_t adventDay23problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	int64_t cin = -1;

	std::vector<NIC> NIC(50, NIC(integers, 0));

	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;

	int64_t outputAddress = 0;
	int nextInstruction = 0;

	for (int i = 0; i < 50; i++)
		NIC[i].q.push(i);


	while (true)
	{
		for (int i = 0; i < 50; i++)
		{
			currPos = NIC[i].currPos;
			integers = NIC[i].integers;

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
				  	if (NIC[i].q.empty())
				  	{
				  		// The incoming packet queue is empty
				  		cin = -1;
				  		integers[posMode1] = cin;
				  		currPos = currPos + 2;
				  		// Save the state of the NIC computer
				  		NIC[i].currPos = currPos;
				  		NIC[i].integers = integers;
				  		// Move to the next computer
				  		integers[currPos] = 99;
				  		break;
				  	}
				  	else
				  	{
				  		cin = NIC[i].q.front();
				  		NIC[i].q.pop();
				  	}
				  
				  	integers[posMode1] = cin;
				  	currPos = currPos + 2;
				  	break;
				  
				  case 4:
				  	if (nextInstruction == 0)
				  	{
				  		outputAddress = integers[posMode1];
				  		nextInstruction++;
				  	}
				  	else
				  	{
				  		if (outputAddress < 50)
				  		{
				  			NIC[outputAddress].q.push(integers[posMode1]);
				  		}
				  		else
				  		{
				  			if (nextInstruction == 2)
				  			{
				  				return integers[posMode1];
				  			}
				  		}
				  
				  		nextInstruction = (nextInstruction + 1) % 3;
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
		}
	}

	return 0;
}


uint64_t adventDay23problem22019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');
	int64_t cin = -1;

	std::vector<NIC> NIC(50, NIC(integers, 0));

	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;

	int64_t outputAddress = 0;
	int nextInstruction = 0;
	std::vector<int> NAT;
	int64_t lastNATq = 0;
	bool stateIdle = false;

	for (int i = 0; i < 50; i++)
		NIC[i].q.push(i);

	while (true)
	{
		for (int i = 0; i < 50; i++)
		{
			currPos = NIC[i].currPos;
			integers = NIC[i].integers;

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
					if (NIC[i].q.empty())
					{
						// The incoming packet queue is empty
						cin = -1;
						integers[posMode1] = cin;
						currPos = currPos + 2;
						// Save the state of the NIC computer
						NIC[i].currPos = currPos;
						NIC[i].integers = integers;
						// Move to the next computer
						integers[currPos] = 99;
						break;
					}
					else
					{
						cin = NIC[i].q.front();
						NIC[i].q.pop();
					}

					integers[posMode1] = cin;
					currPos = currPos + 2;
					break;

				case 4:
					if (nextInstruction == 0)
					{
						outputAddress = integers[posMode1];
						nextInstruction++;
					}
					else
					{
						if (outputAddress < 50)
						{
							NIC[outputAddress].q.push(integers[posMode1]);
						}
						else
						{
							if (NAT.size() == 2)
								NAT.clear();

							NAT.push_back(integers[posMode1]);
						}

						nextInstruction = (nextInstruction + 1) % 3;
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
		}

		stateIdle = true;
		for (int i = 0; i < 50; i++)
		{
			if (!NIC[i].q.empty())
			{
				stateIdle = false;
				break;
			}
		}

		if ((stateIdle) && (!NAT.empty()))
		{
			if (lastNATq == NAT[1])
				return NAT[1];

			NIC[0].q.push(NAT[0]);
			NIC[0].q.push(NAT[1]);
			lastNATq = NAT[1];
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "23";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay23problem12019(inputFile); break;
    case 2: result = adventDay23problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}