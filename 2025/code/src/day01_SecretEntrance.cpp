#include <days.h>

int cicle(int num) // 0-99 
{
  return ((num % 100) + 100) % 100;
}

uint64_t adventDay01P12025(std::ifstream& input)
{
    uint64_t score = 0;

    int init = 50;
    std::string op;

    while (input >> op) 
    {
        const int value = std::stoi(op.substr(1));
        if (op[0] == 'L')
         init= cicle(init - value);
        else
         init= cicle(init + value);

        if(init==0) score++;
    }

    return score;
}

uint64_t adventDay01P22025(std::ifstream& input)
{
    uint64_t score = 0;

    int init = 50;
    std::string op;

    while (input >> op)
    {
        const int value = std::stoi(op.substr(1));
        if (op[0] == 'L')
        {
            int vueltas = value / 100;
            int resto = value % 100;

            if (init == 0)
            {
              if (99 - (resto - 1) < 0)
                vueltas++;
            }
            else if (init - resto <= 0)
                vueltas++;

            score += vueltas;
            init = cicle(init - value);
        }
        else
        {
            int vueltas = value / 100;
            int resto = value % 100;

            if (init + resto >= 100)
                vueltas++;

            score += vueltas;
            init = cicle(init + value);
        }
    }

    return score;
}