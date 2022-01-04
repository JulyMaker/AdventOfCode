#include <utils.h>

void FFTAlgorithm(std::vector<int>& sequence, const std::vector<int>& basePattern)
{
	std::vector<int> newSequence(sequence.size());
	std::vector<int> pattern;
	int it = 1, sum = 0;

	for (int phase = 0; phase < 100; phase++)
	{
		for (int digit = 0; digit < sequence.size(); digit++)
		{
			// Calculate pattern for current phase
			pattern.clear();
			for (const auto& currBasePattern : basePattern)
				for (int iterator = 0; iterator <= digit; iterator++)
					pattern.push_back(currBasePattern);

			// Calculate the new sequence for the next phase
			sum = 0;
			for (int currDigit = digit; currDigit < sequence.size(); currDigit++)
			{
				it = (currDigit + 1) % pattern.size();
				sum += sequence[currDigit] * pattern[it++];
			}
			newSequence[digit] = abs(sum) % 10;
		}
		sequence = newSequence;
	}
}

uint64_t adventDay16problem12019(std::ifstream& input)
{
	std::vector<int> sequence = parseCharToChar(input);
	std::vector<int> basePattern{ 0,1,0,-1 };

	FFTAlgorithm(sequence, basePattern);

	auto result = std::accumulate(sequence.begin(), sequence.begin() + 8, 0, [](int l, int r) {
		return l * 10 + r;
		});

	return result;
}

void readNewASequenceInput(std::ifstream& input, std::vector<int>& sequence, int& messageOffset)
{
	std::string number;

	input >> number;
	for (int i = 0; i < number.size(); i++)
	{
		sequence.push_back(number[i] - '0');
	}

	for (int i = 1; i < 10000; i++)
	{
		for (int it = 0; it < number.size(); it++)
		{
			sequence.push_back(sequence[it]);
		}
	}

	for (int i = 0; i < 7; i++)
	{
		messageOffset = messageOffset * 10 + sequence[i];
	}
}


void calcSecondHalfOfOutput(std::vector<int>& sequence)
{
	const int PHASES = 100;
	std::vector<int> newSequence(sequence.size());
	int sizeSequence = sequence.size();
	int sum = 0;
	int phase = 0;

	while (phase < PHASES)
	{
		// We can observe that all the digits from the second half of the sequence
		// are calculated as (the sum of digits from the last digit to the current digit) % 10
		sum = 0;
		for (int it = sizeSequence - 1; it >= sizeSequence / 2; it--)
		{
			sum += sequence[it];
			newSequence[it] = sum % 10;
		}
		sequence = newSequence;
		phase++;
	}
}

uint64_t adventDay16problem22019(std::ifstream& input)
{
	std::vector<int> sequence;
	int messageOffset = 0;

	readNewASequenceInput(input, sequence, messageOffset);
	calcSecondHalfOfOutput(sequence);

	auto result = std::accumulate(sequence.begin() + messageOffset, sequence.begin() + messageOffset + 8, 0, [](int l, int r) {
		return l * 10 + r;
		});

	return result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "16";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay16problem12019(inputFile); break;
    case 2: result = adventDay16problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}