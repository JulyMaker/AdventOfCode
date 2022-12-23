#ifndef CUBE_H_
#define CUBE_H_


using Coord = std::pair<int, int>;
const std::vector<char> directionArrows = { '>', 'V', '<', '^' };
const int DIRCOUNT = 4;
const int FACES = 6;

Coord operator+(const Coord& c1, const Coord& c2)
{
	auto [x1, y1] = c1;
	auto [x2, y2] = c2;

	return { x1 + x2, y1 + y2 };
}

void operator+=(Coord& c1, const Coord& c2)
{
	auto [x1, y1] = c1;
	auto [x2, y2] = c2;

	c1 = { x1 + x2, y1 + y2 };
}

void operator-=(Coord& c1, const Coord& c2)
{
	auto [x1, y1] = c1;
	auto [x2, y2] = c2;

	c1 = { x1 - x2, y1 - y2 };
}

void operator*=(Coord& c,int num)
{
	auto [x, y] = c;

	c = { x * num, y * num };
}

struct wormHole
{
	int destinationA;
	int directionA;
	int destinationB;
	int directionB;
};

struct CubeTools
{
	int const right = 0;
	int const down = 1;
	int const left = 2;
	int const up = 3;

	int wrap(int direction)
	{
		return (direction + DIRCOUNT) % DIRCOUNT;
	}

	int invert(int direction)
	{
		return wrap(direction + 2);
	}

	int getMaxLineSize(std::vector<std::string>& lines)
	{
		size_t max = 0;
		for (auto& line : lines)
		{
			max = std::max(max, line.size());
		}
		return max;
	}

	int detectResolution(std::vector<std::string>& lines)
	{
		// there are only two possible aspects for cube net: 4:3 and 5:2
		int sideA = getMaxLineSize(lines);
		int sideB = lines.size();
		int minSize = std::min(sideA, sideB);
		int maxSize = std::max(sideA, sideB);

		if (minSize * 4 == maxSize * 3)
			return maxSize / 4;
		else if (minSize * 5 == maxSize * 2)
			return maxSize / 5;

		return -1;
	}

	std::vector<std::string> filterMinimapLines(std::vector<std::string>& lines, int resolution)
	{
		std::vector<std::string> result;
		for (int i = 0; i < lines.size(); i += resolution)
		{
			auto line = lines[i];
			auto& output_line = result.emplace_back();
			for (int j = 0; j < line.size(); j += resolution)
			{
				output_line += line[j] == ' ' ? ' ' : '#';
			}
		}

		return result;
	}
};

struct MonkeyMap
{
	int width;
	int height;
	std::string data;
	std::vector<int> directionSteps;
	std::map<int, wormHole> wormholes;
	CubeTools tools = CubeTools();

	MonkeyMap(std::vector<std::string>& in, bool sentinel)
	{
		width = tools.getMaxLineSize(in);
		height = in.size();

		if (sentinel)
		{
			width += 2;
			height += 2;
		}

		width++; // for /n

		data.resize(width * height, ' ');

		int index = sentinel;
		for (auto& s : in)
			memcpy(&data[sentinel] + width * index++, &s[0], s.size());


		for (int i = 0; i < height; i++)
			data[width * (i + 1) - 1] = '\n';

		directionSteps = { 1, width, -1, -width };
	}

	int toIndex(Coord position)
	{
		return position.first + position.second * width;
	}

	Coord toPosition(int index)
	{
		return { index % width, index / width };
	}

	void addWormhole(int place, int destination, int direction)
	{
		auto it = wormholes.find(place);
		if (it == wormholes.end())
		{
			wormholes[place] = { destination, direction };
		}
		else
		{
			// alternative path
			it->second.destinationB = destination;
			it->second.directionB = direction;
		}
	}
};

struct Cursor
{
	int index = 0;
	int direction = 0;
	MonkeyMap& map;
	CubeTools tools = CubeTools();

	Cursor(MonkeyMap& map) : map{ map }
	{
		index = map.data.find_first_of('.');
	}

	void move(int count)
	{
		for (int i = 0; i < count; i++)
		{
			int step = map.directionSteps[direction];
			int nextIndex = index + step;
			int nextDir = direction;

			if (map.data[nextIndex] == ' ')
			{
				nextIndex = pacmanTeleport(nextIndex, step);
			}
			else if (map.data[nextIndex] == '@')
			{
				auto& wormhole = map.wormholes[nextIndex];
				if (wormhole.destinationA != index)
				{
					nextIndex = wormhole.destinationA;
					nextDir = wormhole.directionA;
				}
				else
				{
					nextIndex = wormhole.destinationB;
					nextDir = wormhole.directionB;
				}
			}

			if (map.data[nextIndex] == '#')	break;

			drawSelf();
			index = nextIndex;
			direction = nextDir;
		}

		drawSelf();
	}

	int pacmanTeleport(int index, const int step)
	{
		do
		{
			index -= step;
		} while (map.data[index] != ' ');

		return index + step;
	}

	void rotateDirection(int& direction, int rotation)
	{
		direction = tools.wrap(direction + rotation);
	}

	void rotate(int rotation)
	{
		rotateDirection(direction, rotation);
	}

	void drawSelf()
	{
		map.data[index] = directionArrows[direction];
	}
};

struct Face;

struct Link
{
	std::reference_wrapper<Face> target;
	int direction;

	Link() : target(reinterpret_cast<Face&>(*this)) , direction{ 0 } {} // garbage, will be overriden

	Link(std::reference_wrapper<Face> target, int direction) : target{ target }, direction{ direction } {}
};

struct Face
{
	int index = 0;
	std::vector<Link> links;

	int minimapIndex = 0;
	Coord netPosition;
	int netRotation = 0;
	std::vector<int> edgeAnchors;

	Face(){ links.resize(directionArrows.size()); }

	int getDirection(Face& face)
	{
		for (int direction = 0; direction < DIRCOUNT; direction++)
		{
			if (&links[direction].target.get() == &face)
			{
				return direction;
			}
		}

		return -1;
	}
};

/*
			+-----+
			|     |
			|  4  |
			|     |
+-----+-----+-----+-----+
|     |     |     |     |
|  0  |  1  |  2  |  3  |
|     |     |     |     |
+-----+-----+-----+-----+
			|     |
			|  5  |
			|     |
			+-----+
*/

struct Cube
{
	std::vector<Face> faces;
	CubeTools cT = CubeTools();

	Cube()
	{
		faces.resize(FACES);

		for (int i = 0; i < faces.size(); i++)
			faces[i].index = i;

		connectFaces(faces[0], faces[1], cT.right, cT.left);
		connectFaces(faces[1], faces[2], cT.right, cT.left);
		connectFaces(faces[2], faces[3], cT.right, cT.left);
		connectFaces(faces[3], faces[0], cT.right, cT.left);

		connectFaces(faces[0], faces[4], cT.up, cT.left);
		connectFaces(faces[1], faces[4], cT.up, cT.down);
		connectFaces(faces[2], faces[4], cT.up, cT.right);
		connectFaces(faces[3], faces[4], cT.up, cT.up);

		connectFaces(faces[0], faces[5], cT.down, cT.left);
		connectFaces(faces[1], faces[5], cT.down, cT.up);
		connectFaces(faces[2], faces[5], cT.down, cT.right);
		connectFaces(faces[3], faces[5], cT.down, cT.down);
	}

	void connectFaces(Face& faceA, Face& faceB, int forward, int backward)
	{
		faceA.links[forward] = Link(faceB, cT.invert(backward));
		faceB.links[backward] = Link(faceA, cT.invert(forward));
	}
};

void findNetLocations(Cube& cube, MonkeyMap& minimap, CubeTools& cT)
{
	int index = minimap.data.find_first_of('#');

	Face& startFace = cube.faces[0];
	startFace.minimapIndex = index;

	minimap.data[index] = startFace.index + '0';

	using FaceVector = std::vector<std::reference_wrapper<Face>>;
	FaceVector front{ startFace };

	while (!front.empty())
	{
		FaceVector newFaces;

		for (Face& curFace : front)
		{
			for (int netDir = 0; netDir < DIRCOUNT; netDir++)
			{
				auto step = minimap.directionSteps[netDir];
				int newIndex = curFace.minimapIndex + step;

				if (minimap.data[newIndex] == '#')
				{
					auto faceDir = cT.wrap(netDir - curFace.netRotation);
					auto& link = curFace.links[faceDir];

					Face& newFace = link.target;
					newFace.minimapIndex = newIndex;
					minimap.data[newIndex] = newFace.index + '0';

					auto backwardDir = newFace.getDirection(curFace);
					auto netBackwardDir = cT.invert(netDir);

					newFace.netRotation = cT.wrap(netBackwardDir - backwardDir);

					newFaces.push_back(newFace);
				}
			}
		}

		front.clear();
		std::swap(front, newFaces);
	}

	for (auto& face : cube.faces)
	{
		face.netPosition = minimap.toPosition(face.minimapIndex);
	}
}

void calculateEdgeAnchors(Cube& cube, MonkeyMap& map, int resolution)
{
	for (auto& face : cube.faces)
	{
		// convert positions from minimap to large map
		auto mapPosition = face.netPosition;
		mapPosition -= Coord(1, 1); // remove sentinel
		mapPosition *= resolution;
		mapPosition += Coord(1, 1); // add sentinel

		auto addAnchor = [&](int x, int y)
		{
			auto anchor_position = mapPosition + Coord{ x, y };
			face.edgeAnchors.push_back(map.toIndex(anchor_position));
		};

		addAnchor(resolution, 0);
		addAnchor(resolution - 1, resolution);
		addAnchor(-1, resolution - 1);
		addAnchor(0, -1);
	}
}

void setupWormholes(Cube& cube, MonkeyMap& map, int resolution, CubeTools& cT)
{
	for (auto& srcFace : cube.faces)
	{
		for (int srcNetEdge = 0; srcNetEdge < DIRCOUNT; srcNetEdge++)
		{
			auto& srcAnchor = srcFace.edgeAnchors[srcNetEdge];
			if (map.data[srcAnchor] == ' ' || map.data[srcAnchor] == '@')
			{
				auto srcLocalDir = cT.wrap(srcNetEdge - srcFace.netRotation);
				auto& link = srcFace.links[srcLocalDir];
				Face& dstFace = link.target;

				auto dstNetEdge = cT.wrap(dstFace.netRotation + cT.invert(link.direction));

				auto srcStep = map.directionSteps[cT.wrap(srcNetEdge + 1)];
				auto dstStep = map.directionSteps[cT.wrap(dstNetEdge + 1)];

				auto dstAnchor = dstFace.edgeAnchors[dstNetEdge];
				dstAnchor += (resolution - 1) * dstStep;

				auto dstNetDir = cT.invert(dstNetEdge);
				dstAnchor += map.directionSteps[dstNetDir];

				for (int i = 0; i < resolution; i++)
				{
					auto srcIndex = srcAnchor + i * srcStep;
					auto dstIndex = dstAnchor - i * dstStep;
					map.data[srcIndex] = '@';
					map.addWormhole(srcIndex, dstIndex, dstNetDir);
				}
			}
		}
	}
}


#endif /* CUBE_H_ */