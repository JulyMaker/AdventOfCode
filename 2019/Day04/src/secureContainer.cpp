#include <utils.h>

struct number
{
	number(int n)
	{
		d[0] = n % 10;
		d[1] = (n / 10) % 10;
		d[2] = (n / 100) % 10;
		d[3] = (n / 1000) % 10;
		d[4] = (n / 10000) % 10;
		d[5] = (n / 100000) % 10;
	}

	constexpr int operator[](std::size_t n) const { return d[n]; }

	void operator++()
	{
		for (int i = 0; i < 6; ++i)
		{
			d[i] += 1;
			if (d[i] == 10)
				d[i] = 0;
			else
				break;
		}
	}

	bool increasing()
	{
		number x = *this;
		return x[5] <= x[4] && x[4] <= x[3] && x[3] <= x[2] && x[2] <= x[1] && x[1] <= x[0];
	}

	std::array<int, 6> d;
};

std::pair<bool, bool> isValid(number x)
{
	const bool twoAdjacent = x[5] == x[4] || x[4] == x[3] || x[3] == x[2] || x[2] == x[1] || x[1] == x[0];

	if (!twoAdjacent)
		return { false, false };

	if (x[5] == x[4] && x[4] == x[3])
		return { true, x[3] != x[2] && (x[2] == x[1] || x[1] == x[0]) };
	else if (x[4] == x[3] && x[3] == x[2])
		return { true, x[2] != x[1] && x[1] == x[0] };
	else if (x[3] == x[2] && x[2] == x[1])
		return { true, x[3] != x[4] && x[4] == x[5] };
	else if (x[2] == x[1] && x[1] == x[0])
		return { true, x[2] != x[3] && (x[3] == x[4] || x[4] == x[5]) };

	return { true, true };
}

uint64_t adventDay04problem12019(std::ifstream& input)
{
	std::vector<int>inputInt = parseInputInt(input, '-');
	const int start = inputInt[0];
	const int end   = inputInt[1];
	const int iterations = end - start;

	uint64_t result=0;
	number x= start;

	for (int i = 0; i < iterations; ++i, ++x)
	{
		if (x.increasing())
		{
			auto [v1, v2] = isValid(x);
			result += v1 ? 1 : 0;
		}
	}

	return result;
}

uint64_t adventDay04problem22019(std::ifstream& input)
{
	std::vector<int>inputInt = parseInputInt(input, '-');
	const int start = inputInt[0];
	const int end = inputInt[1];
	const int iterations = end - start;

	uint64_t result = 0;
	number x = start;

	for (int i = 0; i < iterations; ++i, ++x)
	{
		if (x.increasing())
		{
			auto [v1, v2] = isValid(x);
			result += v2 ? 1 : 0;
		}
	}

	return result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "04";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay04problem12019(inputFile); break;
    case 2: result = adventDay04problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}