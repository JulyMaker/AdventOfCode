#include "../Day15/include/system.h"

void intCodeProg(std::vector<int64_t>& integers, const int64_t input,	std::vector<std::vector<char>>& map)
{
	std::vector<char> line;
	int64_t currPos = 0;
	int64_t posMode1 = 0;
	int64_t posMode2 = 0;
	int64_t posMode3 = 0;
	int64_t relativeBase = 0;

	while (integers[currPos] != 99)
	{
		setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3, integers[currPos] % 100);

		switch (integers[currPos] % 100)
		{
		  case 1:
		  	integers[posMode3] = integers[posMode2] + integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 2:
		  	integers[posMode3] = integers[posMode2] * integers[posMode1];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 3:
		  	integers[posMode1] = input;
		  	currPos = currPos + 2;
		  	break;
		  
		  case 4:
		  	switch (integers[posMode1])
		  	{
		  	  case 10:
		  	  	map.push_back(line);
		  	  	line.clear();
		  	  	break;
		  	  
		  	  default:
		  	  	line.push_back((char)integers[posMode1]);
		  	  	break;
		  	}
		  	currPos = currPos + 2;
		  	break;
		  
		  case 5:
		  	currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 6:
		  	currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
		  	break;
		  
		  case 7:
		  	integers[posMode3] = integers[posMode1] < integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 8:
		  	integers[posMode3] = integers[posMode1] == integers[posMode2];
		  	currPos = currPos + 4;
		  	break;
		  
		  case 9:
		  	relativeBase += integers[posMode1];
		  	currPos = currPos + 2;
		  	break;
		}
	}
}


int findSumScaffoldIntersections(const std::vector<std::vector<char>>& map)
{
	int lines = map.size() - 1, columns = map[0].size();
	int sum = 0;

	for (int x = 1; x < lines - 1; x++)
		for (int y = 1; y < columns - 1; y++)
			if ((map[x][y] == '#') && (map[x + 1][y] == '#') && (map[x - 1][y] == '#') && (map[x][y + 1] == '#') && (map[x][y - 1] == '#'))
				sum += x * y;

	return sum;
}

uint64_t adventDay17problem12019(std::ifstream& input)
{
	std::vector<int64_t> integers = parseInputInt64(input, ',');

	std::vector<std::vector<char>> map;
	int64_t cin = 1;

	intCodeProg(integers, cin, map);

	return findSumScaffoldIntersections(map);
}


constexpr int LIMIT = 20;
constexpr int MLIMIT = 10;

struct pt 
{
	int x, y;
	pt() : x(), y() { }
	pt(int x, int y) : x(x), y(y) { }
};

struct sol_t 
{
	std::vector<int> M;
	std::vector<int> P[3];
	sol_t() : M(), P() { }
};


static bool solve(sol_t& S, const std::vector<int8_t>& P, int idx, int used) 
{
	if (idx == P.size()) return true;
	if (S.M.size() == MLIMIT) return false;

	// Recycle existing program
	for (int i = 0; i < used; i++) 
	{
		auto& prog = S.P[i];
		if (idx + prog.size() > P.size()) 
			continue;

		bool nope = false;
		for (int j = 0; j < prog.size(); j++) {
			if (P[idx + j] != prog[j]) {
				nope = true;
				break;
			}
		}
		if (nope) continue;

		S.M.push_back(i);
		if (solve(S, P, idx + prog.size(), used)) 
			return true;

		S.M.pop_back();
	}

	if (used == 3) return false;

	// Write new program
	auto& prog = S.P[used];
	S.M.push_back(used);
	for (int cost = -1; idx < P.size(); idx++) 
	{
		cost += 4 + ((P[idx] & 0x7f) > 9);
		if (cost > LIMIT) 
			break;

		prog.push_back(P[idx]);
		if (solve(S, P, idx + 1, used + 1)) 
		{
			return true;
		}
	}
	prog.clear();
	S.M.pop_back();

	return false;
}

struct cpu_t 
{
	std::vector<int64_t> V;
	int64_t output = 0, * input = NULL;
	int i = 0, r = 0;

	enum { S_HLT, S_IN, S_OUT };

	cpu_t(const std::vector<int64_t>& V, size_t extra_mem = 16) : V(V) 
	{
		this->V.resize(V.size() + extra_mem);
	}

	// Potentially unsafe memory access, use only with official inputs
	int run() 
	{
		for (;;) {
			auto& a = V[i + 1], & b = V[i + 2], & c = V[i + 3];
			switch (V[i]) {
			case     1: V[c] = V[a] + V[b];    i += 4; break;
			case   101: V[c] = a + V[b];    i += 4; break;
			case   201: V[c] = V[r + a] + V[b];    i += 4; break;
			case  1001: V[c] = V[a] + b;    i += 4; break;
			case  1101: V[c] = a + b;    i += 4; break;
			case  1201: V[c] = V[r + a] + b;    i += 4; break;
			case  2001: V[c] = V[a] + V[r + b];    i += 4; break;
			case  2101: V[c] = a + V[r + b];    i += 4; break;
			case  2201: V[c] = V[r + a] + V[r + b];    i += 4; break;
			case 20001: V[r + c] = V[a] + V[b];    i += 4; break;
			case 21001: V[r + c] = V[a] + b;    i += 4; break;
			case 20101: V[r + c] = a + V[b];    i += 4; break;
			case 21101: V[r + c] = a + b;    i += 4; break;
			case 21201: V[r + c] = V[r + a] + b;    i += 4; break;
			case 22001: V[r + c] = V[a] + V[r + b];    i += 4; break;
			case 22101: V[r + c] = a + V[r + b];    i += 4; break;
			case 22201: V[r + c] = V[r + a] + V[r + b];    i += 4; break;
			case     2: V[c] = V[a] * V[b];    i += 4; break;
			case   102: V[c] = a * V[b];    i += 4; break;
			case  1002: V[c] = V[a] * b;    i += 4; break;
			case  1102: V[c] = a * b;    i += 4; break;
			case  1202: V[c] = V[r + a] * b;    i += 4; break;
			case  2102: V[c] = a * V[r + b];    i += 4; break;
			case  2202: V[c] = V[r + a] * V[r + b];    i += 4; break;
			case 20002: V[r + c] = V[a] * V[b];    i += 4; break;
			case 20102: V[r + c] = a * V[b];    i += 4; break;
			case 21002: V[r + c] = V[a] * b;    i += 4; break;
			case 21102: V[r + c] = a * b;    i += 4; break;
			case 21202: V[r + c] = V[r + a] * b;    i += 4; break;
			case 22002: V[r + c] = V[a] * V[r + b];    i += 4; break;
			case 22102: V[r + c] = a * V[r + b];    i += 4; break;
			case 22202: V[r + c] = V[r + a] * V[r + b];    i += 4; break;
			case     3: input = &V[a];             i += 2; return S_IN;
			case   203: input = &V[r + a];             i += 2; return S_IN;
			case     4: output = V[a];             i += 2; return S_OUT;
			case   104: output = a;             i += 2; return S_OUT;
			case   204: output = V[r + a];             i += 2; return S_OUT;
			case   105: i = a ? V[b] : i + 3;         break;
			case  1005: i = V[a] ? b : i + 3;         break;
			case  1105: i = a ? b : i + 3;         break;
			case  1205: i = V[r + a] ? b : i + 3;         break;
			case  2105: i = a ? V[r + b] : i + 3;         break;
			case   106: i = a ? i + 3 : V[b];         break;
			case  1006: i = V[a] ? i + 3 : b;         break;
			case  1106: i = a ? i + 3 : b;         break;
			case  1206: i = V[r + a] ? i + 3 : b;         break;
			case  2106: i = a ? i + 3 : V[r + b];         break;
			case     7: V[c] = (V[a] < V[b]); i += 4; break;
			case   107: V[c] = (a < V[b]); i += 4; break;
			case  1007: V[c] = (V[a] < b); i += 4; break;
			case  1107: V[c] = (a < b); i += 4; break;
			case  1207: V[c] = (V[r + a] < b); i += 4; break;
			case  2107: V[c] = (a < V[r + b]); i += 4; break;
			case  2207: V[c] = (V[r + a] < V[r + b]); i += 4; break;
			case 20107: V[r + c] = (a < V[b]); i += 4; break;
			case 20207: V[r + c] = (V[r + a] < V[b]); i += 4; break;
			case 21007: V[r + c] = (V[a] < b); i += 4; break;
			case 21107: V[r + c] = (a < b); i += 4; break;
			case 21207: V[r + c] = (V[r + a] < b); i += 4; break;
			case 22007: V[r + c] = (V[a] < V[r + b]); i += 4; break;
			case 22107: V[r + c] = (a < V[r + b]); i += 4; break;
			case 22207: V[r + c] = (V[r + a] < V[r + b]); i += 4; break;
			case     8: V[c] = (V[a] == V[b]); i += 4; break;
			case   108: V[c] = (a == V[b]); i += 4; break;
			case   208: V[c] = (V[r + a] == V[b]); i += 4; break;
			case  1008: V[c] = (V[a] == b); i += 4; break;
			case  1108: V[c] = (a == b); i += 4; break;
			case  1208: V[c] = (V[r + a] == b); i += 4; break;
			case  2108: V[c] = (a == V[r + b]); i += 4; break;
			case  2208: V[c] = (V[r + a] == V[r + b]); i += 4; break;
			case 20008: V[r + c] = (V[a] == V[b]); i += 4; break;
			case 20208: V[r + c] = (V[r + a] == V[b]); i += 4; break;
			case 21008: V[r + c] = (V[a] == b); i += 4; break;
			case 21108: V[r + c] = (a == b); i += 4; break;
			case 21208: V[r + c] = (V[r + a] == b); i += 4; break;
			case 22208: V[r + c] = (V[r + a] == V[r + b]); i += 4; break;
			case     9: r += V[a];                 i += 2; break;
			case   109: r += a;                 i += 2; break;
			case   209: r += V[r + a];                 i += 2; break;
			case    99: i = r = 0;                           return S_HLT;
			default: printf("Unimplemented: %ld\n", V[i]); abort();
			}
		}
	}
};


uint64_t adventDay17problem22019(std::ifstream& input)
{
	// The Intcode program needs extra memory
	constexpr int EXTRA_MEM = 8192;

	auto V = parseInputInt64(input, ',');

	constexpr int DIM = 100;
	char G[DIM][DIM] = { };

	pt robot;

	int  maxx = 0, run = 0;

	cpu_t C1(V, EXTRA_MEM);
	for (pt p{ 1,1 }; C1.run() != cpu_t::S_HLT; p.x++) 
	{
		if (p.x < 1 || p.x >= DIM) abort();
		if (p.y < 1 || p.y >= DIM) abort();
		switch (C1.output) 
		{
		  case '^': robot = p;
		  case '#': G[p.x][p.y] = 1;
		  	maxx = std::max(maxx, p.x + 1);
		  	break;
		  case '\n': p.x = 0, p.y++;
		}
		// Check for intersection
		run = (run + (C1.output == '#')) & -(C1.output == '#');
	}

	// Split the path into segments by greedily moving as
	// far as possible before turning
	std::vector<int8_t> I;
	int dx = 0, dy = -1, steps = 0;
	for (pt p = robot; ; p = { p.x + dx, p.y + dy }) 
	{
		if (G[p.x + dx][p.y + dy]) {
			// ahead
			steps++;
		}
		else if (G[p.x + dy][p.y - dx]) 
		{
			// left
			if (steps) I.back() |= steps;
			I.push_back(0x80);
			dx = std::exchange(dy, -dx);
			steps = 1;
		}
		else if (G[p.x - dy][p.y + dx]) 
		{
			// right
			if (steps) I.back() |= steps;
			I.push_back(0x00);
			dy = std::exchange(dx, -dy);
			steps = 1;
		}
		else 
		{
			// goal
			break;
		}
	}
	I.back() |= steps;

	// Find a program that solves the maze
	sol_t S;
	if (!solve(S, I, 0, 0)) abort();

	// Convert the program to text
	std::string s;
	for (int i = 0; i < S.M.size(); i++)
	{
		if (i) s.push_back(',');
		s.push_back(S.M[i] + 'A');
	}

	s.push_back('\n');
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < S.P[i].size(); j++) 
		{
			if (j) s.push_back(',');
			int k = S.P[i][j];
			s.push_back((k & 0x80) ? 'L' : 'R');
			k &= 0x7f;
			s.push_back(',');
			if (k > 9) 
			{
				s.push_back('1');
				k -= 10;
			}
			s.push_back(k + '0');
		}
		s.push_back('\n');
	}
	s.push_back('n');
	s.push_back('\n');

	
	V[0] = 2;
	cpu_t C2(V, EXTRA_MEM);
	for (auto c : s) 
	{
		while (C2.run() != cpu_t::S_IN) {}
		*C2.input = c;
	}

	int result = 0;
	while (C2.run() == cpu_t::S_OUT) 
	{
		result = C2.output;
	}

	return result;
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "17";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay17problem12019(inputFile); break;
    case 2: result = adventDay17problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}