#include <days.h>

#define ALL(x) (x).begin(),(x).end()
#define ALLc(x) (x).cbegin(),(x).cend()

template<typename T>
struct Coord3D
{
    constexpr Coord3D(T X = 0, T Y = 0, T Z = 0) : x(X), y(Y), z(Z) {}
    constexpr bool operator <  (const Coord3D& p) const { 
        if (z < p.z) return true; if (p.z < z) return false;
        if (x < p.x) return true; if (p.x < x) return false; 
        return y < p.y; 
    } // z is more important for ordering

    T x, y, z;
};

using Coord = Coord3D<int>;

struct Brick
{
    Coord a, b;
    std::set<int> supportedBy, supports;

    Brick(const Coord& c1, const Coord& c2)
    {
        if (c1 < c2) 
        {
            a = c1;
            b = c2; 
        }
        else {
            a = c2; 
            b = c1; 
        }
    }

    void drop(int by) {
        a.z -= by; 
        b.z -= by; 
    }

    constexpr bool operator <(const Brick& l) { 
        if (a < l.a) return true;
        if (l.a < a) return false;
        return b < l.b; 
    }

    constexpr bool intersects(const Brick& brick) const { 
        return !(brick.b.x < a.x || brick.a.x > b.x || brick.b.y < a.y || brick.a.y > b.y);
    }
};

uint64_t adventDay22P12023(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInputReg(input, "(.*)~(.*)");
    std::vector<Brick> brickes;
    for (int i = 0; i < in.size(); i+= 3)
    {
        auto v1 = splitI(in[i + 1], ",");
        auto v2 = splitI(in[i + 2], ",");

        brickes.emplace_back(Coord(v1[0], v1[1], v1[2]), Coord(v2[0], v2[1], v2[2]));
    }

    std::sort(ALL(brickes));

    std::vector<Brick> settled;
    std::vector<int> safes;
    for (auto& bricke : brickes)
    {
        int highestZ = 0;
        std::set<int> support;
        for (int i = 0; i < settled.size(); ++i)
        {
            if (settled[i].intersects(bricke))
            {
                if (settled[i].b.z > highestZ)
                {
                    highestZ = settled[i].b.z;
                    support = { i };
                }
                else if (settled[i].b.z == highestZ)
                    support.insert(i);
            }
        }
       
        bricke.drop( bricke.a.z - highestZ - 1 );
        for (int i : support)
            settled[i].supports.insert(settled.size());

        bricke.supportedBy = support;
        settled.push_back(bricke);
        safes.push_back(1);
    }

    for (int i = 0; i < settled.size(); ++i)
        if (settled[i].supportedBy.size() == 1)
            safes[*settled[i].supportedBy.cbegin()] = 0;

    score = std::accumulate(ALLc(safes), 0);

    return score;
}

uint64_t adventDay22P22023(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInputReg(input, "(.*)~(.*)");
    std::vector<Brick> brickes;
    for (int i = 0; i < in.size(); i += 3)
    {
        auto v1 = splitI(in[i + 1], ",");
        auto v2 = splitI(in[i + 2], ",");

        brickes.emplace_back(Coord(v1[0], v1[1], v1[2]), Coord(v2[0], v2[1], v2[2]));
    }

    std::sort(ALL(brickes));

    std::vector<Brick> settled;
    for (auto& bricke : brickes)
    {
        int highestZ = 0;
        std::set<int> support;
        for (int i = 0; i < settled.size(); ++i)
        {
            if (settled[i].intersects(bricke))
            {
                if (settled[i].b.z > highestZ)
                {
                    highestZ = settled[i].b.z;
                    support = { i };
                }
                else if (settled[i].b.z == highestZ)
                    support.insert(i);
            }
        }

        int delta = bricke.a.z - highestZ - 1;

        bricke.drop(delta);
        for (int i : support)
            settled[i].supports.insert(settled.size());

        bricke.supportedBy = support;
        settled.push_back(bricke);
    }


    for (int i = 0; i < settled.size(); ++i)
    {
        std::set<int> falling = { i }, toEvaluate = settled[i].supports;
        int toRemove = -1;

        do
        {
            toRemove = -1;

            for (int j : toEvaluate)
            {
                if (int count = std::count_if(ALLc(settled[j].supportedBy), [&falling](int a) { return falling.find(a) != falling.cend(); });
                    count == settled[j].supportedBy.size())
                {
                    toRemove = j;
                    break;
                }
            } 

            if (toRemove >= 0)
            {
                toEvaluate.erase(toRemove);
                falling.insert(toRemove);
                for (int j : settled[toRemove].supports)
                    toEvaluate.insert(j);
            }
            
        } while (toRemove >= 0);

        score+= falling.size() - 1;
    }

    return score;
}