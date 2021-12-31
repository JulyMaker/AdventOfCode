#include <utils.h>

#define ADD 1
#define MULTIPLY 2
#define INPUT 3
#define OUTPUT 4

#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUAL 8

int getOpcode(int num)
{
  return num % 100;
}

std::string getPaddedString(int num, int Opcode)
{
  std::string aux = std::to_string(num);
  int size = 0;

  switch (Opcode)
  {
    case ADD:
    case MULTIPLY:
      size = 5; break;
    case INPUT:
    case OUTPUT:
      size = 3; break;
  }

  while (aux.length() < size)
    aux = "0" + aux;

  return aux;
}

uint64_t adventDay05problem12019(std::ifstream& input)
{
	std::vector<int> basecodes = parseInputInt(input, ',');

  uint64_t index = 0;
  uint64_t Opcode = 0;
  uint64_t calc1 = 0;
  uint64_t calc2 = 0;
  std::string paddedString;

  uint64_t result = 0;
  constexpr int cin = 1;

  while (Opcode != 99)
  {
    switch (Opcode)
    {
      case ADD:
        paddedString = getPaddedString(basecodes[index], ADD);
      
        calc1 = (paddedString[2] == '1')? basecodes[index + 1] : basecodes[basecodes[index + 1]]; //Param 1
        calc2 = (paddedString[1] == '1')? basecodes[index + 2] : basecodes[basecodes[index + 2]]; //Param 2
        
        basecodes[basecodes[index + 3]] = calc1 + calc2; //Param 3, can't be immediate
      
        index += 4; //IP incrementing
        break;
      
      case MULTIPLY:
        paddedString = getPaddedString(basecodes[index], MULTIPLY);
        
        calc1 = (paddedString[2] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]]; //Param 1
        calc2 = (paddedString[1] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]]; //Param 2
      
        basecodes[basecodes[index + 3]] = calc1 * calc2; //Param 3, can't be immediate 
        index += 4; //IP incrementing
        break;
      
      case INPUT:
        paddedString = getPaddedString(basecodes[index], INPUT);
      
        basecodes[basecodes[index + 1]] = cin;
        index += 2;
        break;
      
      case OUTPUT:
        paddedString = getPaddedString(basecodes[index], OUTPUT);

        result = (paddedString[0] == '0') ? basecodes[basecodes[index + 1]] : basecodes[index + 1];
        index += 2;
        break;
      
      default:
        break;
    }

    Opcode = getOpcode(basecodes[index]);
  }

	return result;
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

uint64_t adventDay05problem22019(std::ifstream& input)
{
  std::vector<int> basecodes = parseInputInt(input, ',');

  uint64_t index = 0;
  uint64_t Opcode = 0;
  uint64_t calc1 = 0;
  uint64_t calc2 = 0;
  std::string paddedString;

  uint64_t result = 0;
  constexpr int cin = 5;

  while (Opcode != 99)
  {
    switch (Opcode)
    {
    case ADD:
      paddedString = getPaddedStringExtra(basecodes[index], ADD);

      calc1 = (paddedString[2] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]]; //Param 1
      calc2 = (paddedString[1] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]]; //Param 2

      basecodes[basecodes[index + 3]] = calc1 + calc2; //Param 3, can't be immediate

      index += 4; //IP incrementing
      break;

    case MULTIPLY:
      paddedString = getPaddedStringExtra(basecodes[index], MULTIPLY);

      calc1 = (paddedString[2] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]]; //Param 1
      calc2 = (paddedString[1] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]]; //Param 2

      basecodes[basecodes[index + 3]] = calc1 * calc2; //Param 3, can't be immediate 
      index += 4; //IP incrementing
      break;

    case INPUT:
      paddedString = getPaddedStringExtra(basecodes[index], INPUT);

      basecodes[basecodes[index + 1]] = cin;
      index += 2;
      break;

    case OUTPUT:
      paddedString = getPaddedStringExtra(basecodes[index], OUTPUT);

      result = (paddedString[0] == '0') ? basecodes[basecodes[index + 1]] : basecodes[index + 1];
      index += 2;
      break;

    case JUMP_IF_TRUE:
      paddedString = getPaddedStringExtra(basecodes[index], JUMP_IF_TRUE);

      calc1 = (paddedString[1] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]];
      calc2 = (paddedString[0] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]];
       
      index = (calc1 == 0) ? index + 3: calc2;
      break;

    case JUMP_IF_FALSE:
      paddedString = getPaddedStringExtra(basecodes[index], JUMP_IF_FALSE);

      calc1 = (paddedString[1] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]];   
      calc2 = (paddedString[0] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]];
      
      index = (calc1 != 0) ? index + 3: calc2;
      break;

    case LESS_THAN: //LESS
      paddedString = getPaddedStringExtra(basecodes[index], LESS_THAN);

      calc1 = (paddedString[2] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]];
      calc2 = (paddedString[1] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]];

      basecodes[basecodes[index + 3]] = (calc1 < calc2) ? 1 : 0;
      index += 4;
      break;

    case EQUAL: //EQUALS
      paddedString = getPaddedStringExtra(basecodes[index], EQUAL);

      calc1 = (paddedString[2] == '1') ? basecodes[index + 1] : basecodes[basecodes[index + 1]];
      calc2 = (paddedString[1] == '1') ? basecodes[index + 2] : basecodes[basecodes[index + 2]];
       
      basecodes[basecodes[index + 3]] = (calc1 == calc2) ? 1 : 0;
      index += 4;
      break;

    }

    Opcode = getOpcode(basecodes[index]);
  }

  return result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "05";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay05problem12019(inputFile); break;
    case 2: result = adventDay05problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}