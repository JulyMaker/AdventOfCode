#include <utils.h>

#define ADD 1
#define MULTIPLY 2
#define INPUT 3
#define OUTPUT 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUAL 8
#define HALT 99

class IntcodeComputer 
{
private:
	int pointer = 0;
  int cin = 0;
	bool hasHalted;
  bool phaseSet;
	std::vector<int> inputData, outputData;
	std::vector<int> instImmutable, instMutable;

public:
	
	void clearInput() { inputData.clear(); }
	void clearOutput() { outputData.clear(); }
	bool hasInput() { return !inputData.empty(); }
	bool hasOutput() { return !outputData.empty();	}
	void addInput(std::vector<int> input)	{	inputData.insert(inputData.end(), input.begin(), input.end()); }
	void addOutput(std::vector<int> output) { outputData.insert(outputData.end(), output.begin(), output.end()); }
	bool hasFinished() { return hasHalted; }
	void setImmutable(std::vector<int> instructions) { instImmutable = instructions; }

	int getInput()
	{
		if (hasInput())
		{
			int input = inputData.front();
			inputData.erase(inputData.begin());
			return input;
		}
	}

  int getOutput() 
  {
		if (hasOutput()) 
    {
      int output = outputData.front();
			outputData.erase(outputData.begin());
			return output;
		}
	}

	void resetMutable() 
	{
		pointer = 0;
    cin = 0;
		hasHalted = false;
    phaseSet = false;
		instMutable = instImmutable;
	}

  void setCin(int newCin)
  {
    cin = newCin;
  }
  
  std::string getPaddedStringExtra(int num, int Opcode)
  {
    std::string aux = std::to_string(num);
    int size = 0;

    switch (Opcode)
    {
    case ADD:
    case MULTIPLY:
    case LESS_THAN:
    case EQUAL:
      size = 5; break;
    case INPUT:
    case OUTPUT:
      size = 3; break;
    case JUMP_IF_TRUE:
    case JUMP_IF_FALSE:
      size = 4; break;
    }

    while (aux.length() < size)
      aux = "0" + aux;

    return aux;
  }

  int getOpcode(int num)
  {
    return num % 100;
  }

	void runMutable() 
	{
    int64_t index = 0;
    int64_t Opcode = 0;
    int64_t calc1 = 0;
    int64_t calc2 = 0;
    std::string paddedString;

    int result = 0;
    while (Opcode != 99)
    {
      switch (Opcode)
      {
        case ADD:
          paddedString = getPaddedStringExtra(instMutable[index], ADD);
        
          calc1 = (paddedString[2] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]]; //Param 1
          calc2 = (paddedString[1] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]]; //Param 2
        
          instMutable[instMutable[index + 3]] = calc1 + calc2; //Param 3, can't be immediate
        
          index += 4; //IP incrementing
          break;
        
        case MULTIPLY:
          paddedString = getPaddedStringExtra(instMutable[index], MULTIPLY);
        
          calc1 = (paddedString[2] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]]; //Param 1
          calc2 = (paddedString[1] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]]; //Param 2
        
          instMutable[instMutable[index + 3]] = calc1 * calc2; //Param 3, can't be immediate 
          index += 4; //IP incrementing
          break;
        
        case INPUT:
          paddedString = getPaddedStringExtra(instMutable[index], INPUT);

          instMutable[instMutable[index + 1]] = getInput();

          index += 2;
          break;
        
        case OUTPUT:
          paddedString = getPaddedStringExtra(instMutable[index], OUTPUT);
        
          result = (paddedString[0] == '0') ? instMutable[instMutable[index + 1]] : instMutable[index + 1];
          addOutput({ result });

          index += 2;
          break;
        
        case JUMP_IF_TRUE:
          paddedString = getPaddedStringExtra(instMutable[index], JUMP_IF_TRUE);
        
          calc1 = (paddedString[1] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]];
          calc2 = (paddedString[0] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]];
        
          index = (calc1 == 0) ? index + 3 : calc2;
          break;
        
        case JUMP_IF_FALSE:
          paddedString = getPaddedStringExtra(instMutable[index], JUMP_IF_FALSE);
        
          calc1 = (paddedString[1] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]];
          calc2 = (paddedString[0] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]];
        
          index = (calc1 != 0) ? index + 3 : calc2;
          break;
        
        case LESS_THAN: //LESS
          paddedString = getPaddedStringExtra(instMutable[index], LESS_THAN);
        
          calc1 = (paddedString[2] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]];
          calc2 = (paddedString[1] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]];
        
          instMutable[instMutable[index + 3]] = (calc1 < calc2) ? 1 : 0;
          index += 4;
          break;
        
        case EQUAL: //EQUALS
          paddedString = getPaddedStringExtra(instMutable[index], EQUAL);
        
          calc1 = (paddedString[2] == '1') ? instMutable[index + 1] : instMutable[instMutable[index + 1]];
          calc2 = (paddedString[1] == '1') ? instMutable[index + 2] : instMutable[instMutable[index + 2]];
        
          instMutable[instMutable[index + 3]] = (calc1 == calc2) ? 1 : 0;
          index += 4;
          break;
        
        case HALT:
          hasHalted = true;
          return;
      }

      Opcode = getOpcode(instMutable[index]);
    }
	}

	static void addInputSequentially(std::vector<IntcodeComputer>& intcodeComputers, std::vector<int> sequences)
	{
		for (int i = 0; i < intcodeComputers.size() && i < sequences.size(); ++i) 
		{
			intcodeComputers[i].addInput({ sequences[i] });
		}
	}

	static void setImmutableSequentially(std::vector<IntcodeComputer>& intcodeComputers, std::vector<int> instMutable)
	{
		for (int i = 0; i < intcodeComputers.size(); ++i) 
		{
			intcodeComputers[i].setImmutable({ instMutable });
		}
	}

	static void resetMutableSequentially(std::vector<IntcodeComputer>& intcodeComputers) 
	{
		for (int i = 0; i < intcodeComputers.size(); ++i) 
		{
			intcodeComputers[i].resetMutable();
		}
	}
};


std::string getPaddedStringExtra(int num, int Opcode)
{
  std::string aux = std::to_string(num);
  int size = 0;

  switch (Opcode)
  {
  case ADD:
  case MULTIPLY:
  case LESS_THAN:
  case EQUAL:
    size = 5; break;
  case INPUT:
  case OUTPUT:
    size = 3; break;
  case JUMP_IF_TRUE:
  case JUMP_IF_FALSE:
    size = 4; break;
  }

  while (aux.length() < size)
    aux = "0" + aux;

  return aux;
}

int GetOpcode(int num)
{
  return num % 100;
}

std::vector<int> RunComputer(std::vector<int> numbers, int phaseSetting, int input, bool* exitCondition, bool phaseSet, int index, bool* MachineDone)
{
  long long int Opcode = 0;
  long long int calc1 = 0;
  long long int calc2 = 0;
  int Output = 0;
  std::string paddedString;

  while (Opcode != 99)
  {
    switch (Opcode)
    {
      case ADD:
        paddedString = getPaddedStringExtra(numbers[index], ADD);
      
        calc1 = (paddedString[2] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[1] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
        
        numbers[numbers[index + 3]] = calc1 + calc2;
      
        index += 4;
        break;
      
      case MULTIPLY:
        paddedString = getPaddedStringExtra(numbers[index], MULTIPLY);
      
        calc1 = (paddedString[2] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[1] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
      
        numbers[numbers[index + 3]] = calc1 * calc2;
      
        index += 4; //IP incrementing
        break;
      
      case INPUT:
        paddedString = getPaddedStringExtra(numbers[index], INPUT);
        
        numbers[numbers[index + 1]] = (!phaseSet) ? phaseSetting : input;
        phaseSet = true;
      
        index += 2;
        break;
      
      case OUTPUT:
        paddedString = getPaddedStringExtra(numbers[index], OUTPUT);
      
        (paddedString[0] == '0') ? numbers.push_back(numbers[numbers[index + 1]]) : numbers.push_back(numbers[index + 1]);
        
        index += 2;
        numbers.push_back(index);
        
        return numbers;
        break;
      
      case JUMP_IF_TRUE:
        paddedString = getPaddedStringExtra(numbers[index], JUMP_IF_TRUE);
      
        calc1 = (paddedString[1] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[0] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
      
        index = (calc1 == 0) ? index + 3 : calc2;
        break;
      
      case JUMP_IF_FALSE:
        paddedString = getPaddedStringExtra(numbers[index], JUMP_IF_FALSE);
      
        calc1 = (paddedString[1] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[0] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
      
        index = (calc1 != 0) ? index + 3 : calc2;
        break;
      
      case LESS_THAN:
        paddedString = getPaddedStringExtra(numbers[index], LESS_THAN);
      
        calc1 = (paddedString[2] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[1] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
      
        numbers[numbers[index + 3]] = (calc1 < calc2) ? 1: 0;
        
        index += 4;
        break;
      
      case EQUAL:
        paddedString = getPaddedStringExtra(numbers[index], EQUAL);
      
        calc1 = (paddedString[2] == '1') ? numbers[index + 1] : numbers[numbers[index + 1]];
        calc2 = (paddedString[1] == '1') ? numbers[index + 2] : numbers[numbers[index + 2]];
      
        numbers[numbers[index + 3]] = (calc1 == calc2) ? 1 : 0;
      
        index += 4;
        break;
      
      default:
        break;
    }

    Opcode = GetOpcode(numbers[index]);
  }
  *exitCondition = true;
  *MachineDone = true;
  //std::cout << "Exit condition reached" << std::endl;
  return numbers;
}