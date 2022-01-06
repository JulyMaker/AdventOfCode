#include "utils.h"

constexpr int64_t NUMCARDS = 10007;
constexpr int64_t STARTPOS = 2019;

void cut(std::vector<int>& deck, int cut)
{
  cut = (deck.size() + cut) % deck.size();
  std::rotate(deck.begin(), deck.begin() + cut, deck.end());
}

void increment(std::vector<int>& deck, const int incr)
{
  std::vector<int> newDeck(deck.size());
  int pos = 0;

  for (int i = 0; i < deck.size(); i++)
  {
    newDeck[pos] = deck[i];
    pos = (pos + incr) % deck.size();
  }

  deck = newDeck;
}

uint64_t adventDay22problem12019(std::ifstream& input)
{
	std::vector<int> cout;

	std::vector<int> deck(NUMCARDS);
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i] = i;
	}

	std::string op;
	int number{ 0 };

	while (input >> op)
	{
		if (op == "cut")
		{
			input >> number;
			cut(deck, number);
		}
		else
		{
			input >> op >> op;
			if (op == "increment")
			{
				input >> number;
				increment(deck, number);
			}
			else
			{
				input >> op;
				std::reverse(deck.begin(), deck.end());
			}
		}
	}

	for (int pos = 0; pos < deck.size(); pos++)
	{
		if (deck[pos] == STARTPOS)
		{
			cout.push_back(pos);
		}
	}

	return vectorToInt(cout);
}


// Returns (a * b) % mod
// If b is even then a * b = (2 * a) * (b / 2)
// If b is odd  then a * b = a + (a * (b - 1))
int64_t moduloMultiplication(int64_t a, int64_t b, int64_t mod)
{
	int64_t result = 0;

	a = a % mod;
	while (b)
	{
		// If b is odd, add a with result 
		if (b & 1)
			result = (result + a) % mod;

		// Here we assume that doing 2*a 
		// doesn't cause overflow 
		a = (2 * a) % mod;
		b >>= 1; // b = b / 2 
	}

	return result;
}


// Returns (a ^ b) % mod
// If b is even then a * b = (a * a) ^ (b / 2)
// If b is odd  then a * b = a * (a ^ (b - 1))
int64_t pow(int64_t a, int64_t b, int64_t mod)
{
	int64_t result = 1;

	a = a % mod;
	while (b)
	{
		// If b is odd, multiply a with result 
		if (b & 1)
			result = moduloMultiplication(result, a, mod);

		a = moduloMultiplication(a, a, mod);;
		b = b >> 1; // b = b/2 
	}

	return result;
}


// Returns modulo inverse of input with respect 
// to modulo using extended Euclid Algorithm 
// Assumption: input and modulo are coprimes
int64_t modInverse(int64_t cin, int64_t modulo)
{
	int64_t original = modulo;
	int64_t y = 0, x = 1;
	int64_t q = 0, t = 0;

	if (modulo == 1)
		return 0;

	while (cin > 1)
	{
		// q is quotient 
		q = cin / modulo;
		t = modulo;

		// modulo is remainder now 
		// process same as Euclid's algorithm
		modulo = cin % modulo;
		cin = t;
		t = y;

		// Update y and x
		y = x - q * y;
		x = t;
	}

	if (x < 0)
		x += original;

	return x;
}

uint64_t adventDay22problem22019(std::ifstream& input)
{
	std::vector<std::pair<std::string, int64_t>> shuffleProcess;
	readInput22(input, shuffleProcess);

	int64_t a = 1, b = 0, aux = 0;
	int64_t n = 119315717514047;
	int64_t times = 101741582076661;

	for (int i = shuffleProcess.size() - 1; i >= 0; i--)
	{
		if (shuffleProcess[i].first == "cut")
		{
			b = b + shuffleProcess[i].second;
		}
		else
		{
			if (shuffleProcess[i].first == "new")
			{
				a *= -1;
				b = -b - 1;
			}
			else
			{
				aux = modInverse(shuffleProcess[i].second, n);

				a = moduloMultiplication(a, aux, n);
				b = moduloMultiplication(b, aux, n);
			}
		}

		a = (a + n) % n;
		b = (b + n) % n;
	}

	// f(x) = a * x + b    x = 2020
	// f(f(f(x))) = a*(a*(a*x+b)+b)+b = a ^ 3 * x + a ^ 2 * b + a * b + b
	// f^n(x) = a^n*x + a^(n-1)*b + a^(n-2)*b + ... + b = a ^ n * x + (a ^ n - 1) / (a - 1) * b
	// f^n(x) = ((pow(a, times, n)*2020 + (pow(a, times, n)-1) * modInverse(a-1, n) * b) % n)
	int64_t first = moduloMultiplication(pow(a, times, n), 2020, n);
	int64_t second = (pow(a, times, n) + n - 1) % n;
	int64_t third = moduloMultiplication(b, second, n);
	int64_t fourth = pow(a - 1, n - 2, n);
	int64_t result = (first + moduloMultiplication(third, fourth, n)) % n;

	return  result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "22";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay22problem12019(inputFile); break;
    case 2: result = adventDay22problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}