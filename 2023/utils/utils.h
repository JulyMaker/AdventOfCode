#include <includes.h>
#include <paths.h>

/* Parser input methods */
std::string parseLine(std::ifstream& input);
std::vector<std::string> parseInput(std::ifstream& input, const char c);
std::vector<std::vector<char>> parseInputChars(std::ifstream& input);
std::vector<int> parseInputInt(std::ifstream& input, const char c);
std::vector<int> parseCharToChar(std::ifstream& input);
std::vector<int64_t> parseInputInt64(std::ifstream& input, const char c);
std::vector<std::vector<int>> parseInputGrid(std::ifstream& input);

template<class T>
std::vector<T> parseInput(std::ifstream& is);


/* Parser input with reg */
std::vector<std::string> parseInputReg(std::ifstream& infile, std::string rex);
std::vector<std::string> parseInputReg(std::string& s, std::string rex);


/* Split Methods */
std::vector<int> splitI(const std::string& text, const std::string& delims);
std::vector<std::string> splitS(const std::string& text, const std::string& delims);


/* Control Methods */
bool mainControl(int argc, char* argv[], int& problem, std::string& fileName);
bool inputControl(const std::string& day, const std::string& year, std::string& fileName);


/* auxiliar Methods */
int64_t vectorToInt(std::vector<int>& vector, int offset1, int offset2);


/* Hash Auxiliar */
template <typename T1, typename T2>
struct PointHash;


/* Other Years */
struct monckey;
void readInput05_2022(std::ifstream& infile, std::vector<std::stack<char>>& crane, std::vector<std::vector<int>>& moves);
void readInput11_2022(std::ifstream& infile, std::vector<monckey>& monkeys);



