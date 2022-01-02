#include <utils.h>


uint64_t adventDay08problem12019(std::ifstream& input)
{
  const int WIDE = 25;
  const int TALL = 6;
  uint64_t result = 0;

  std::string layer(TALL * WIDE, ' ');
  auto minZeroes = layer.size();

  while (input.read(layer.data(), TALL * WIDE))
  {
    if (auto z = std::count(layer.begin(), layer.end(), '0'); z < minZeroes) 
    {
      minZeroes = z;
      result = std::count(layer.begin(), layer.end(), '1') * std::count(layer.begin(), layer.end(), '2');
    }
  }

	return result;
}

uint64_t adventDay08problem22019(std::ifstream& input)
{
  const int WIDE = 25;
  const int TALL = 6;

  std::string layer(TALL * WIDE, ' ');
  std::string result(TALL * WIDE, '2');

  while (input.read(layer.data(), 6 * 25)) 
  {
    for (auto i = 0ul; i < result.size(); ++i)
      if (result[i] == '2')
        result[i] = layer[i];
  }

  for (int i = 0; i < result.size(); ++i)
    std::cout << ((i % WIDE == 0) ? '\n' : ' ') << (result[i] == '0' ? ' ' : '*');
  
  std::cout << std::endl;
  std::cout << std::endl;

  /*
         
         * *     *     *   * * *       * *     *       *
       *     *   *     *   *     *   *     *   *       *
       *     *   *     *   *     *   *           *   *
       * * * *   *     *   * * *     *             *
       *     *   *     *   *   *     *     *       *
       *     *     * *     *     *     * *         *
  */

  return 0;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "08";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay08problem12019(inputFile); break;
    case 2: result = adventDay08problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}