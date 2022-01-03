#include <utils.h>

struct moon 
{
	int x, y, z, vx, vy, vz;
};

void updateVelocity(moon& m1, moon& m2) 
{
	if (m1.x > m2.x) { m1.vx -= 1; m2.vx += 1; }
	else if (m1.x < m2.x) { m1.vx += 1; m2.vx -= 1; }

	if (m1.y > m2.y) { m1.vy -= 1; m2.vy += 1; }
	else if (m1.y < m2.y) { m1.vy += 1; m2.vy -= 1; }

	if (m1.z > m2.z) { m1.vz -= 1; m2.vz += 1; }
	else if (m1.z < m2.z) { m1.vz += 1; m2.vz -= 1; }
}

void updateVelocitys(std::vector<moon>& moons) 
{
	for (int i = 0; i < moons.size(); i++) 
		for (int j = i; j < moons.size(); j++) 
			updateVelocity((moons[i]), (moons[j]));
}

void updatePositions(std::vector<moon>& moons) 
{
	for (auto& moon : moons) 
	{
		moon.x += moon.vx;
		moon.y += moon.vy;
		moon.z += moon.vz;
	}
}

std::array<int, 4> getAxis(std::vector<moon> moons, char c) 
{
	if (c == 'x') return { moons[0].x, moons[1].x, moons[2].x, moons[3].x };
	else if (c == 'y') return { moons[0].y, moons[1].y, moons[2].y, moons[3].y };
	else if (c == 'z') return { moons[0].z, moons[1].z, moons[2].z, moons[3].z };
}

uint64_t adventDay12problem12019(std::ifstream& input)
{
	const int STEPS = 1000;
	std::vector<std::string> parseInput = parseInputReg(input,"<x=([-]?\\d+), y=([-]?\\d+), z=([-]?\\d+)>");

	std::vector<moon> moons;
	for (int i = 0; i < parseInput.size(); i++)
	{
		moons.push_back({ std::stoi(parseInput[i + 1]), std::stoi(parseInput[i + 2]), std::stoi(parseInput[i + 3]), 0,0,0 });
		i += 3;
	}

	for (int i = 0; i < STEPS; i++)
	{
		updateVelocitys(moons);
		updatePositions(moons);
	}

	double energy = std::accumulate(moons.begin(), moons.end(), 0, [](double a, moon b) {
		return a + (abs(b.x) + abs(b.y) + abs(b.z)) * (abs(b.vx) + abs(b.vy) + abs(b.vz));
		});	
 
	return energy;
}

uint64_t adventDay12problem22019(std::ifstream& input)
{
	std::vector<std::string> parseInput = parseInputReg(input, "<x=([-]?\\d+), y=([-]?\\d+), z=([-]?\\d+)>");

	std::vector<moon> moons;
	for (int i = 0; i < parseInput.size(); i++)
	{
		moons.push_back({ std::stoi(parseInput[i + 1]), std::stoi(parseInput[i + 2]), std::stoi(parseInput[i + 3]), 0,0,0 });
		i += 3;
	}

	uint64_t x_repeat = 0, y_repeat = 0, z_repeat = 0, step = 0;

	std::array<int, 4> x_axis_initial = { moons[0].x, moons[1].x,moons[2].x,moons[3].x };
	std::array<int, 4> y_axis_initial = { moons[0].y, moons[1].y,moons[2].y,moons[3].y };
	std::array<int, 4> z_axis_initial = { moons[0].z, moons[1].z,moons[2].z,moons[3].z };

	while (x_repeat == 0 || y_repeat == 0 || z_repeat == 0) 
	{
		step += 1;
		updateVelocitys(moons);
		updatePositions(moons);
		if (x_repeat == 0 && x_axis_initial == getAxis(moons, 'x')) x_repeat = step;
		if (y_repeat == 0 && y_axis_initial == getAxis(moons, 'y')) y_repeat = step;
		if (z_repeat == 0 && z_axis_initial == getAxis(moons, 'z')) z_repeat = step;
	}

  return std::lcm(x_repeat + 1, std::lcm(y_repeat + 1, z_repeat + 1));
}


int main(int argc, char *argv[])
{
  // argv contain *.txt path
  int problem = 2;
  std::string day = "12";

  std::string fileName = "../../Day"+day+"/input.txt";
  //fileName = "../../Day" + day + "/inputExample.txt";

  if (!mainControl(argc, argv, problem, fileName)) return -1;

  std::ifstream inputFile(fileName);
  uint64_t result = 0;
  switch (problem)
  {
    case 1: result = adventDay12problem12019(inputFile); break;
    case 2: result = adventDay12problem22019(inputFile); break;
    default:
      std::cout << "The number problem isn't right" << result << std::endl;
  }

  std::cout << "Answer is: " << result << std::endl;
  return 0;
}