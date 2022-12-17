#include <utils.h>

bool stoneFit(int stone, int shift, int bottom, const std::vector<int> stones[5], std::vector<int>& field)
{
	for (int rock = 0; rock < stones[stone].size(); rock++)
	{
		int shiftV = (shift > 0) ? stones[stone][rock] >> shift : stones[stone][rock] << -shift;
		if ((bottom + rock < field.size()) && (field[bottom + rock] & shiftV))
			return false;
	}

	return true;
};

uint64_t adventDay17problem12022(std::ifstream& input)
{
  uint64_t score = 0;

	const int ROCKS = 2022;

  std::string wind = parseLine(input);

  const std::vector<int> stones[5] = { // Rocks in hexa
    {0x1E}, {0x08, 0x1C, 0x08}, {0x1C, 0x04, 0x04},
    {0x10, 0x10, 0x10, 0x10}, {0x18, 0x18}
  };

  int side[5][2] = { {-2, 1}, {-2, 2}, {-2, 2}, {-2, 4}, {-2, 3} };

  std::vector<int> field;
  int sIt = 0, wIt = 0;

  field.push_back(0x7F);


	while (sIt != ROCKS)
	{
		int bottom = field.size() + 3;
		int shift = 0;
		bool drop = true;

		do
		{
			// wind
			switch (wind[wIt])
			{
			  case '<':
			  	if (shift != side[sIt % 5][0] && stoneFit(sIt % 5, shift - 1, bottom, stones, field))
			  		--shift;
			  	break;
			  case '>':
			  	if (shift != side[sIt % 5][1] && stoneFit(sIt % 5, shift + 1, bottom, stones, field))
			  		++shift;
			  	break;
			}

			wIt = (wIt + 1) % wind.size();

			drop = stoneFit(sIt % 5, shift, bottom - 1, stones, field);
			if (drop) --bottom;

		} while (drop);

		int top = bottom + stones[sIt % 5].size();
		if (field.size() < top) field.resize(top);

		for (int rock = 0; rock < stones[sIt % 5].size(); rock++)
		{
			int shiftV = (shift > 0) ? stones[sIt % 5][rock] >> shift : stones[sIt % 5][rock] << -shift;
			field[bottom + rock] |= shiftV;
		}
		++sIt;
	}

	score = field.size() - 1;

  return score;
}


uint64_t adventDay17problem22022(std::ifstream& input)
{
  uint64_t score = 0;
  
	const int64_t TURNS = 1'000'000'000'000;

	std::string wind = parseLine(input);

	std::vector<int> stones[5] = {
		{0x1E}, {0x08, 0x1C, 0x08}, {0x1C, 0x04, 0x04},
		{0x10, 0x10, 0x10, 0x10}, {0x18, 0x18}
	};

	int side[5][2] = { {-2, 1}, {-2, 2}, {-2, 2}, {-2, 4}, {-2, 3} };

	std::vector<int> field;
	int sIt = 0, wIt = 0;

	field.push_back(0x7F);


	std::vector<int> heights;
	std::map<std::pair<int, int>, std::vector<int>> drops;
	std::map<int, int> loopCount;

	while (true)
	{
		int bottom = field.size() + 3;
		int shift = 0;
		bool drop = true;

		do
		{
			switch (wind[wIt])
			{
			  case '<':
			  	if (shift != side[sIt % 5][0] && stoneFit(sIt % 5, shift - 1, bottom, stones, field))
			  		--shift;
			  	break;
			  case '>':
			  	if (shift != side[sIt % 5][1] && stoneFit(sIt % 5, shift + 1, bottom, stones, field))
			  		++shift;
			  	break;
			}

			wIt = (wIt + 1) % wind.size();

			drop = stoneFit(sIt % 5, shift, bottom - 1, stones, field);
			if (drop) --bottom;

		} while (drop);

		int top = bottom + stones[sIt % 5].size();
		if (field.size() < top) field.resize(top);

		for (int r = 0; r < stones[sIt % 5].size(); r++)
		{
			int sv = shift > 0 ? stones[sIt % 5][r] >> shift : stones[sIt % 5][r] << -shift;
			field[bottom + r] |= sv;
		}
		++sIt;
		heights.push_back(field.size() - 1);

		auto check = std::make_pair((sIt - 1) % 5, (wIt - 1 + wind.size()) % wind.size());
		if (drops[check].size() != 0)
		{
			for (int x : drops[check])
			{
				int d = (sIt - 1) - x;
				loopCount[d]++;
				if (loopCount[d] >= 20)
				{
					int hd = heights[sIt - 1] - heights[x];
					int64_t loops = (TURNS - x) / d;
					int64_t inLoop = TURNS - loops * d;

					score = heights[inLoop] + hd * loops - 1;
					return score;
				}
			}
		}
		drops[check].push_back(sIt - 1);
	}
   
  return score;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "17";
  const bool EXAMPLE = false;

  std::string fileName = (EXAMPLE) ? DAY_EXAMPLE_PATH(day) : DAY_PATH(day);

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay17problem12022(inputFile); break;
    case 2: result = adventDay17problem22022(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}