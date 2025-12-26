#include <days.h>

struct Point
{
    uint64_t x, y, z;
    int circuit;

    Point() : x(0), y(0), z(0), circuit(-1) {}
    Point(int x, int y, int z) : x(x), y(y), z(z), circuit(-1) {}
};

struct Distance 
{
    int i, j;
    double dist;

    Distance() = default;
    Distance(int i, int j, double dist) : i(i), j(j), dist(dist) {}

    bool operator<(const Distance& other) const 
    {
        return dist < other.dist;
    }
};

double calculateDistance(const Point& p1, const Point& p2) 
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) +
        std::pow(p1.y - p2.y, 2) +
        std::pow(p1.z - p2.z, 2));
}

uint64_t process(std::vector<Point> points, const int maxConnections = -1) 
{
    std::vector<Distance> distances;
    
    for (size_t i = 0; i < points.size(); ++i) 
    {
        for (size_t j = i + 1; j < points.size(); ++j) 
        {
            double dist = calculateDistance(points[i], points[j]);
            distances.emplace_back(i, j, dist);
        }
    }
    
    std::sort(distances.begin(), distances.end());
    
    if (maxConnections > 0 && maxConnections < static_cast<int>(distances.size()))
        distances.resize(maxConnections);
    
    int nextCircuit = 0;
    
    for (const auto& d : distances) 
    {
      int circuit_1 = points[d.i].circuit;
      int circuit_2 = points[d.j].circuit;
    
      if (circuit_1 == -1 && circuit_2 == -1) 
      {
        points[d.i].circuit = nextCircuit;
        points[d.j].circuit = nextCircuit;
        nextCircuit++;
      }
      else if (circuit_2 == -1) 
      {
        points[d.j].circuit = circuit_1;
      }
      else if (circuit_1 == -1) 
      {
        points[d.i].circuit = circuit_2;
      }
      else if (circuit_1 != circuit_2) 
      {       
        int targetCircuit = circuit_1;
        int circuitToReplace = circuit_2;
    
        for (auto& p : points) 
          if (p.circuit == circuitToReplace)
            p.circuit = targetCircuit;
            
      }
    
      if (maxConnections == -1) 
      {
          bool all_in_same_circuit = true;
          int first_circuit = points[0].circuit;

          for (size_t k = 1; k < points.size() && all_in_same_circuit; ++k)
             if (points[k].circuit != first_circuit)
                 all_in_same_circuit = false;

          if (all_in_same_circuit)
            return points[d.i].x * points[d.j].x;
      }
    }

    std::unordered_map<uint64_t, uint64_t> circuitCounts;
    for (const auto& p : points)
      if (p.circuit >= 0)
        circuitCounts[p.circuit]++;


    std::vector<uint64_t> counts;
    for (const auto& pair : circuitCounts)
        counts.push_back(pair.second);

    std::sort(counts.begin(), counts.end(), std::greater<int>());


    uint64_t result = 1;
    for (size_t i = 0; i < std::min(static_cast<size_t>(3), counts.size()); ++i)
        result *= counts[i];

    return result;
}


uint64_t adventDay08P12025(std::ifstream& input)
{
    uint64_t score = 0;

    //const int PAIRS = 10;  //Example
    const int PAIRS = 1000;  //No Example

    std::vector<std::string> in = parseInput(input,'\n');

    std::vector<Point> points;
    for (auto& line : in)
    {
        std::vector<uint64_t> coords = splitUInt(line, ",");
        points.emplace_back(coords[0], coords[1], coords[2]);
    }

    score = process(points, PAIRS);

    return score;
}

struct Junction 
{
    int x, y, z;

    Junction(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator==(const Junction& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    struct Hash {
        size_t operator()(const Junction& j) const {
            return std::hash<int>()(j.x) ^ std::hash<int>()(j.y) ^ std::hash<int>()(j.z);
        }
    };
};

class Union 
{
private:
    std::unordered_set<Junction, Junction::Hash> members;

public:
    Union(const std::unordered_set<Junction, Junction::Hash>& members) : members(members) {}

    Union unionWith(const Union& other) const 
    {
        std::unordered_set<Junction, Junction::Hash> newMembers = this->members;
        newMembers.insert(other.members.begin(), other.members.end());
        return Union(newMembers);
    }

    const std::unordered_set<Junction, Junction::Hash>& getMembers() const 
    {
        return members;
    }

    size_t size() const 
    {
        return members.size();
    }

    bool operator==(const Union& other) const 
    {
        return this == &other;
    }
};

double calculateDistance(const Junction& p1, const Junction& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) +
        std::pow(p1.y - p2.y, 2) +
        std::pow(p1.z - p2.z, 2));
}


uint64_t adventDay08P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::unordered_map<Junction, Union*, Junction::Hash> union_map;
    std::vector<Junction> junctions;
    for (auto& line : in)
    {
        std::vector<uint64_t> coords = splitUInt(line, ",");
        junctions.emplace_back(coords[0], coords[1], coords[2]);
    }

    for (const auto& j : junctions) 
    {
        std::unordered_set<Junction, Junction::Hash> single_set = { j };
        Union* u = new Union(single_set);
        union_map[j] = u;
    }

    std::vector<std::pair<Junction, Junction>> all_pairs;
    for (size_t i = 0; i < junctions.size(); ++i) 
      for (size_t j = i + 1; j < junctions.size(); ++j) 
        all_pairs.emplace_back(junctions[i], junctions[j]);

    std::sort(all_pairs.begin(), all_pairs.end(),
        [](const std::pair<Junction, Junction>& a,
            const std::pair<Junction, Junction>& b) {
                return calculateDistance(a.first, a.second) < calculateDistance(b.first, b.second);
        });

    for (size_t i = 0; i < all_pairs.size(); ++i) 
    {
        const Junction& p = all_pairs[i].first;
        const Junction& q = all_pairs[i].second;

        if (union_map[p] == union_map[q])
            continue;

        Union new_union = union_map[p]->unionWith(*union_map[q]);
        Union* new_union_ptr = new Union(new_union.getMembers());

        for (const auto& member : new_union.getMembers()) 
            union_map[member] = new_union_ptr;

        if (new_union_ptr->size() == junctions.size()) 
        {
            score= p.x * q.x;
            break;
        }
    }

    return score;
}