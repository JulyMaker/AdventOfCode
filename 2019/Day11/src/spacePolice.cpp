#include <program.h>

uint64_t adventDay11problem12019(std::ifstream& input)
{
  std::vector<int64_t> inputInt = parseInputInt64(input, ',');

  program_t program{ inputInt };
  auto panels = countPanels(program);
 
	return panels.size();
}

uint64_t adventDay11problem22019(std::ifstream& input)
{
  std::vector<int64_t> inputInt = parseInputInt64(input, ',');

  program_t program{ inputInt };
  auto panels = countPanels(program, 1);
  paint(panels);

  return 0;

  /*
       #  #  ##  #### #  #   ## #  # #  # ####
       #  # #  # #    #  #    # #  # #  #    #
       #### #    ###  ####    # #### #  #   #
       #  # # ## #    #  #    # #  # #  #  #
       #  # #  # #    #  # #  # #  # #  # #
       #  #  ### #### #  #  ##  #  #  ##  ####
  */
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "11";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay11problem12019(inputFile); break;
    case 2: result = adventDay11problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}