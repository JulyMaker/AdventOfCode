#include <utils.h>

int runProgram(std::vector<int> cleanData, int noun, int verb)
{
	cleanData[1] = noun;
	cleanData[2] = verb;
	
	int opCode = 0;
	const int a= 1;
	const int b= 2;
	const int c= 3;

	const int INC= 4;

	for (size_t index= 0; index < cleanData.size(); index+= INC)
	{
		opCode = cleanData.at(index);
		if (opCode == 1)
			cleanData[cleanData[index+c]] = cleanData[cleanData[index + a]] + cleanData[cleanData[index + b]];
		else if (opCode == 2)
			cleanData[cleanData[index+c]] = cleanData[cleanData[index + a]] * cleanData[cleanData[index + b]];
		else if (opCode == 99)
			break;
	}

	return cleanData[0];
}

uint64_t adventDay02problem12019(std::ifstream& input)
{
  int noun =12;
  int verb = 2;
  std::vector<int> inputData = parseInputInt(input, ',');
  
  return runProgram(inputData, noun, verb);
}

uint64_t adventDay02problem22019(std::ifstream& input)
{
	const uint64_t NUMSTOP= 19690720;
	std::vector<int> inputData = parseInputInt(input, ',');

	int x= 0;
	for (unsigned i= 0; i <= 99; i++)
	{
		for (unsigned j= 0; j <= 99; j++)
		{
			x = runProgram(inputData, i, j);
			if (x == NUMSTOP)
				return i * 100 + j;
		}
	}

  return  0;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "02";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay02problem12019(inputFile); break;
    case 2: result = adventDay02problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}