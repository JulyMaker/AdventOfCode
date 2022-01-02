#include <incode.h>


uint64_t adventDay07problem12019(std::ifstream& input)
{
	std::vector<int> numbers = parseInputInt(input, ',');

	std::vector<std::vector<int>> sequences;
	std::vector<int> baseSequence = { 0, 1, 2, 3, 4 };

	do 
	{
		sequences.push_back(baseSequence);
	} while (std::next_permutation(baseSequence.begin(), baseSequence.end()));

	std::vector<int> inputCache(5), outputCache;
	std::vector<IntcodeComputer> virtualMachines(5);

	IntcodeComputer::setImmutableSequentially(virtualMachines, numbers);
	

	for (std::vector<int> sequence : sequences)
	{
		std::fill(inputCache.begin(), inputCache.begin() + 5, 0);

		IntcodeComputer::resetMutableSequentially(virtualMachines);
		IntcodeComputer::addInputSequentially(virtualMachines, sequence);

		for (int i = 0; !virtualMachines[4].hasFinished(); ++i) 
		{
			virtualMachines[i].addInput({ i == 0 ? 0 : inputCache[i - 1] });
			virtualMachines[i].runMutable();
			inputCache[i] = virtualMachines[i].getOutput();
		}

		outputCache.push_back(inputCache[4]);
	}

	
	return *std::max_element(outputCache.begin(), outputCache.end());
}

uint64_t adventDay07problem22019(std::ifstream& inputStream)
{
  std::vector<int> numbers = parseInputInt(inputStream, ',');

  int input = 0;
  std::vector<int> results;
  std::vector<std::vector<int>> codeArray; // stores the memory state of each machine

  bool exitCondition = false;
  bool phaseSet = false;
  int index[5] = { 0 };
  int id = 0;
  bool machineDone[5] = { false };

  std::vector<int> thrusterInput = { 5, 6, 7, 8, 9 };

  do
  {
    exitCondition = false;
    codeArray.clear(); //resetting code array for each quintet of inputs

    for (int i = 0; i < 5; i++)
    {
      codeArray.push_back(numbers);
      index[i] = 0;
      machineDone[i] = false;
    }
    phaseSet = false;

    input = 0;
    while (true)
    {
      id = 0;
      for (int i : thrusterInput)
      {
        if (!machineDone[id])
        {
          codeArray[id] = RunComputer(codeArray[id], i, input, &exitCondition, phaseSet, index[id], &machineDone[id]);
          index[id] = codeArray[id].back();       // getting the IP from codeArray at id into the IPArray at id
          codeArray[id].pop_back();               // throwing the IP out
          if (!machineDone[id])                   // mistake at first, need to actually halt the damn machine, and not just pop random values out of the codearray if it's not an output, but just a halt
          {
            input = codeArray[id].back();         // getting the output which in turn becomes the next input
            codeArray[id].pop_back();             // throwing the output out
          } 
        }
        id++;
      }

      phaseSet = true;
      if (exitCondition)
        break;
    }

    results.push_back(input);

  } while (std::next_permutation(thrusterInput.begin(), thrusterInput.end()));

  return *std::max_element(results.begin(), results.end());
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "07";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay07problem12019(inputFile); break;
    case 2: result = adventDay07problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}