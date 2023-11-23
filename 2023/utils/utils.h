#include <includes.h>
#include <paths.h>


std::vector<std::string> parseInput(std::ifstream& input, const char c);

std::vector<std::vector<char>> parseInputChars(std::ifstream& input);

std::vector<std::vector<int>> parseInputGrid(std::ifstream& input);

std::vector<int> parseInputInt(std::ifstream& input, const char c);

std::string parseLine(std::ifstream& input);

std::vector<int> parseCharToChar(std::ifstream& input);

std::vector<int64_t> parseInputInt64(std::ifstream& input, const char c);

template<class T>
std::vector<T> parseInput(std::ifstream& is);

std::vector<std::string> parseInputReg(std::ifstream& infile, std::string rex);

std::vector<std::string> parseInputReg(std::string& s, std::string rex);

std::vector<int> splitI(const std::string& text, const std::string& delims);

std::vector<std::string> splitS(const std::string& text, const std::string& delims);

int64_t vectorToInt(std::vector<int>& vector, int offset1, int offset2);

bool mainControl(int argc, char* argv[], int& problem, std::string& fileName);

void readInput05(std::ifstream& infile, std::vector<std::stack<char>>& crane, std::vector<std::vector<int>>& moves);

struct monckey;

void readInput11(std::ifstream& infile, std::vector<monckey>& monkeys);

template <typename T1, typename T2>
struct PointHash;