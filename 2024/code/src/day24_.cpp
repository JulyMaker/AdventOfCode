#include <days.h>
#include <Eigen/Dense>

template<typename T>
struct Coord3D
{
    constexpr Coord3D(T X = 0, T Y = 0, T Z = 0) : x(X), y(Y), z(Z) {}
    
    constexpr bool operator ==  (const Coord3D& p) const 
    {
        return x == p.x && y == p.y;
    }

    T x, y, z;
};

using Coord = Coord3D<int64_t>;
using Veloc = Coord3D<int64_t>;

struct Particle
{
    Coord position = { 0, 0, 0 };
    Veloc velocity = { 0, 0, 0 };

    Particle() {}
    Particle(const Coord& p, const Veloc& v) : position(p), velocity(v) {}
};

bool intersection(Particle& a, Particle& b, std::pair<int64_t, int64_t>& coord)
{
    float t = (b.velocity.y * (b.position.x - a.position.x) - b.velocity.x * (b.position.y - a.position.y));
    t = t / ((a.velocity.x * b.velocity.y) - (b.velocity.x * a.velocity.y));
    if (t < 0)
    {
        return false;
    }

    
    coord = { a.position.x + (a.velocity.x * t) , a.position.y + (a.velocity.y * t) };
    float s = (coord.first - b.position.x) / b.velocity.x;
    if (s < 0)
    {
        return false;
    }

    return true;
}

bool inRange(const std::pair<int64_t, int64_t>& p)
{
    uint64_t TESTX = 200000000000000, TESTY = 400000000000000;
    //uint64_t TESTX = 7, TESTY = 27;

    if (p.first >= TESTX && p.second >= TESTX && p.first <= TESTY && p.second <= TESTY)
            return true;

    return false;
}

uint64_t adventDay24P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in= parseInputReg(input, "(.*) @ (.*)");

    std::vector<Particle> particles;
    for (int i = 0; i < in.size(); i += 3)
    {
        auto p = splitUInt64(in[i + 1], ",");
        auto v = splitUInt64(in[i + 2], ",");

        Particle parti = { {p[0], p[1], p[2]}, {v[0], v[1], v[2]} };

        particles.push_back(parti);
    }

    for (int i = 0; i < particles.size(); i++)
    {
        Particle& p = particles[i];
        for (int j = i + 1; j < particles.size(); j++)
        {
            Particle& b = particles[j];
            if (p.velocity == b.velocity && p.position == b.position) continue;

            std::pair<int64_t, int64_t> intersect;

            if (intersection(p, b, intersect) && inRange(intersect))
                score++;
        }
    }

    return score;
}

// The current position of a particle can be described by P(t) = P_0 + V * t
// where P(t) is its position at time t, P_0 is the initial position, V is
// its velocity.
//
// Therefore, for each particle i and there is a solution particle Px(t)
// such that Px(t_i) = Pi(t_i)
// => Px_0 + Vx * t_i = Pi_0 + Vi * t_i
// => Px_0 - Pi_0 = (Vi - Vx) * t_i
// Therefore since t_i is scalar the vectors on either side are parallel and
// so their cross product is zero
//
// => (Px_0 - Pi_0) x (Vx - Vi) = 0 for all i
// => (Px_0 x Vx) + (Pi_0 x Vi) - (Px_0 x Vi) - (Pi_0 x Vx) = 0
//
// Now we can eliminate the (Px_0 x Vx) term by choosing another point Pj
// and subtracting the two equations from each other. After some rearranging
//
// (Pi_0 x Vi) - (Pj_0 x Vj) = (Pi_0 - Pj_0) x Vx + (Vj - Vi) Px_0
//
// There are six unknowns in this equation (the start pos and velocity are
// 3d) so we need to make another equation using at least one more point
// and then form a matrix equation. We get a matrix of the form
//
// C = AX
//
// where X = [Px_0, Vx]^T. Therefore the solution is simply
//
// X = A^{-1} C

struct Hailstone
{
    Eigen::Vector3d pos;
    Eigen::Vector3d vel;
};

Eigen::Matrix3d getCoeffMat(const Eigen::Vector3d& v) {
    Eigen::Matrix3d coeffMat;
    coeffMat << 0, -v[2], v[1], v[2], 0, -v[0], -v[1], v[0], 0;
    return coeffMat;
}

uint64_t adventDay24P22024(std::ifstream& input)
{
    uint64_t score = 0;

   std::vector<std::string> in = parseInputReg(input, "(.*) @ (.*)");

   std::vector<Hailstone> hails;
   for (int i = 0; i < in.size(); i += 3)
   {
       auto p = splitDouble(in[i + 1], ",");
       auto v = splitDouble(in[i + 2], ",");
   
       Hailstone parti = { {p[0], p[1], p[2]}, {v[0], v[1], v[2]} };
   
       hails.push_back(parti);
   }

    std::unordered_map<int64_t, int> freqs;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, hails.size() - 1);

    for (int i = 0; i < 100; ++i) 
    {
        int p0{ distr(gen) };
        int p1{ distr(gen) };
        int p2{ distr(gen) };
        int p3{ distr(gen) };

        if (p0 == p1 || p0 == p2 || p0 == p3 || p1 == p2 || p1 == p3 || p2 == p3)
            continue;

        Eigen::MatrixXd equations(6, 6);
        Eigen::VectorXd rhs(6);

        rhs.segment<3>(0) = hails[p0].pos.cross(hails[p0].vel) - hails[p1].pos.cross(hails[p1].vel);
        rhs.segment<3>(3) = hails[p2].pos.cross(hails[p2].vel) - hails[p3].pos.cross(hails[p3].vel);

        equations.block<3, 3>(0, 0) = getCoeffMat(hails[p1].vel - hails[p0].vel);
        equations.block<3, 3>(3, 0) = getCoeffMat(hails[p3].vel - hails[p2].vel);
        equations.block<3, 3>(0, 3) = getCoeffMat(hails[p0].pos - hails[p1].pos);
        equations.block<3, 3>(3, 3) = getCoeffMat(hails[p2].pos - hails[p3].pos);

        Eigen::VectorXd result = equations.inverse() * rhs;

        int64_t sum{ 0 };
        for (int j = 0; j < 3; ++j)
            sum += std::roundl(result[j]);

        freqs[sum]++;
    }

    int maxFreq= 0;
    for (const auto& [k, v] : freqs) {
        if (v > maxFreq) {
            maxFreq = v;
            score = k;
        }
    }

    return score;
}