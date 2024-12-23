#include <utils.h>

/* Parser input methods */

std::string parseLine(std::ifstream& input)
{
    std::string line;

    std::getline(input, line);
    input.close();

    return line;
}

std::vector<std::string> parseInput(std::ifstream& input, const char c)
{
    std::vector<std::string> output;
    std::string line;

    while (!input.eof())
    {
        std::getline(input, line, c);
        if (line != "")
        {
            output.push_back(line);
        }
    }
    input.close();

    return output;
}

std::vector<std::vector<char>> parseInputChars(std::ifstream& input)
{
    std::string line;
    std::vector<std::vector<char>> map;
    std::vector<char> aux;

    while (std::getline(input, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            aux.push_back(line[i]);
        }
        map.push_back(aux);
        aux.clear();
    }

    return map;
}

std::vector<int> parseInputInt(std::ifstream& input, const char c)
{
    std::vector<int> output;
    std::string line;

    while (!input.eof())
    {
        std::getline(input, line, c);
        if (line != "")
        {
            output.push_back(stoi(line));
        }
    }
    input.close();

    return output;
}

std::vector<int> parseCharToChar(std::ifstream& input)
{
    std::string number;
    std::vector<int> sequence;

    input >> number;
    for (int i = 0; i < number.size(); i++)
    {
        sequence.push_back(number[i] - '0');
    }

    return sequence;
}

std::vector<int64_t> parseInputInt64(std::ifstream& input, const char c)
{
    std::vector<int64_t> output;
    std::string line;

    while (!input.eof())
    {
        std::getline(input, line, c);
        if (line != "")
        {
            output.push_back(stoll(line));
        }
    }
    input.close();

    return output;
}

std::vector<std::vector<int>> parseInputGrid(std::ifstream& input)
{
    std::string line;
    std::vector<std::vector<int>> map;
    std::vector<int> aux;

    while (std::getline(input, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            aux.push_back(line[i] - '0');
        }
        map.push_back(aux);
        aux.clear();
    }

    return map;
}


/* Parser input with reg */

std::vector<std::string> parseInputReg(std::ifstream& infile, std::string rex)
{
    //std::regex pattern = std::regex{ "^pos=<([-]?\\d+),([-]?\\d+),([-]?\\d+)>, r=(\\d+)$" };
    std::regex pattern = std::regex{ rex };
    std::vector<std::string> output;

    for (std::string line; getline(infile, line); )
    {
        std::smatch m;
        regex_match(line, m, pattern);
        for (auto& i : m)
            output.push_back(i);
    }

    return output;
}

std::vector<std::string> parseInputReg(std::string& s, std::string rex)
{
    //std::regex pattern = std::regex{ "^pos=<([-]?\\d+),([-]?\\d+),([-]?\\d+)>, r=(\\d+)$" };
    std::regex pattern = std::regex{ rex };
    std::vector<std::string> output;

    std::smatch m;
    regex_match(s, m, pattern);
    for (auto& i : m)
        output.push_back(i);

    return output;
}

std::vector<std::string> searchInputReg(std::ifstream& infile, std::string rex)
{
    std::regex pattern = std::regex{ rex };
    std::vector<std::string> output;

    for (std::string line; getline(infile, line); )
    {
        std::sregex_iterator begin(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (auto it = begin; it != end; ++it)
            output.push_back(it->str());
    }

    return output;
}

std::pair<std::vector<std::string>, std::vector<std::string>> parseInputReg(std::ifstream& infile, std::string rex1, std::string rex2)
{
    std::regex pattern1 = std::regex{ rex1 };
    std::regex pattern2 = std::regex{ rex2 };
    std::vector<std::string> output1;
    std::vector<std::string> output2;

    bool firstPart = true;
    for (std::string line; getline(infile, line); )
    {
        if (line == "") firstPart = false;
        std::smatch m;

        (firstPart)? regex_match(line, m, pattern1): regex_match(line, m, pattern2);
        for (auto& i : m)
            (firstPart) ? output1.push_back(i) : output2.push_back(i);
    }

    return { output1, output2 };
}

/* Split Methods */

std::vector<int> splitI(const std::string& text, const std::string& delims)
{
    std::vector<int> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(std::stoi(text.substr(start, end - start)));
        start = text.find_first_not_of(delims, end);
    }
    if (start != std::string::npos)
        tokens.push_back(std::stoi(text.substr(start)));

    return tokens;
}

std::vector<uint64_t> splitUInt(const std::string& text, const std::string& delims)
{
    std::vector<uint64_t> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(std::stoll(text.substr(start, end - start)));
        start = text.find_first_not_of(delims, end);
    }
    if (start != std::string::npos)
        tokens.push_back(std::stoll(text.substr(start)));

    return tokens;
}

std::vector<int64_t> splitUInt64(const std::string& text, const std::string& delims)
{
    std::vector<int64_t> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(std::stoll(text.substr(start, end - start)));
        start = text.find_first_not_of(delims, end);
    }
    if (start != std::string::npos)
        tokens.push_back(std::stoll(text.substr(start)));

    return tokens;
}

std::vector<double> splitDouble(const std::string& text, const std::string& delims)
{
    std::vector<double> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(std::stod(text.substr(start, end - start)));
        start = text.find_first_not_of(delims, end);
    }
    if (start != std::string::npos)
        tokens.push_back(std::stod(text.substr(start)));

    return tokens;
}

std::vector<std::string> splitS(const std::string& text, const std::string& delims)
{
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while ((end = text.find_first_of(delims, start)) != std::string::npos) {
        if (end != start)
            tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if (start != std::string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}


/* Control Methods */

bool mainControl(int argc, char* argv[], std::string& fileName, std::string& day, int& problem, bool& example)
{
    if (argc == 2)
    {
        if ((std::stoi(argv[1]) == 1) || (std::stoi(argv[1]) == 2)) // Problem number
            problem = std::stoi(argv[1]);
        else
        {
            std::cout << "Problem 1 or 2" << std::endl;
            return false;
        }
    }
    else if (argc == 3)
    {
        if (1 <= std::stoi(argv[1]) && std::stoi(argv[1]) <= 25)
        {
            day = argv[1];
        }
        else
        {
            std::cout << "Day between 1 to 25" << std::endl;
            return false;
        }

        if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
            problem = std::stoi(argv[2]);
        else
        {
            std::cout << "Problem 1 or 2" << std::endl;
            return false;
        }
    }
    else if (argc == 4)
    {
        if (1 <= std::stoi(argv[1]) && std::stoi(argv[1]) <= 25)
        {
            day = argv[1];
        }
        else
        {
            std::cout << "Day between 1 to 25" << std::endl;
            return false;
        }

        if ((std::stoi(argv[2]) == 1) || (std::stoi(argv[2]) == 2))
            problem = std::stoi(argv[2]);
        else
        {
            std::cout << "Problem 1 or 2" << std::endl;
            return false;
        }

        if (strcmp(argv[3], "true") == 0) example = true;
        else example = false;
    }
    else if (argc == 5)
    {
        fileName = argv[1];

        if (1 <= std::stoi(argv[2]) && std::stoi(argv[2]) <= 25)
        {
            day = argv[2];
        }
        else
        {
            std::cout << "Day between 1 to 25" << std::endl;
            return false;
        }

        if ((std::stoi(argv[3]) == 1) || (std::stoi(argv[3]) == 2))
            problem = std::stoi(argv[3]);
        else
        {
            std::cout << "Problem 1 or 2" << std::endl;
            return false;
        }

        if (strcmp(argv[4], "true") == 0) example = true;
        else example = false;
    }
    else if (argc != 1)
    {
        std::cout << "ERROR: problem number missing" << std::endl;
        return false;
    }

    return true;
}

bool inputControl(const std::string& day, const std::string& year, std::string& fileName)
{
    std::ifstream cookieFile(COOKIE_PATH());
    const std::string COOKIE = parseLine(cookieFile);

    std::filesystem::path inputFile(fileName);
    std::string urlAOC = "https://adventofcode.com/" + year + "/day/" + std::to_string(std::stoi(day)) + "/input";

    if (!std::filesystem::exists(inputFile))
    {
        // Llama al script de Python usando el comando del sistema
        // py script url inputFile cookieFile
        std::string pythonScript = "py " + (std::string)SCRIPT_PATH() + " " + urlAOC + " " + fileName + " " + COOKIE;
        int resultado = std::system(pythonScript.c_str());

        // Verifica si la llamada al sistema fue exitosa
        if (resultado == 0)
        {
            std::cout << "Input added." << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Error " + std::to_string(resultado) + " in Python script." << std::endl;
            return false;
        }
    }

    return true;
}


/* auxiliar Methods */

int64_t vectorToInt(std::vector<int>& vector, int offset1 = 0, int offset2 = 0)
{
    if (offset2 == 0) offset2 = vector.size();

    auto result = std::accumulate(vector.begin() + offset1, vector.begin() + offset2, 0, [](int l, int r) {
        return l * 10 + r;
        });

    return result;
}


/* 2024 Year */


/* Other Years */

struct monckey
{
    int id;
    std::vector<int> items;
    std::vector<std::string> op;
    std::vector<int> test = { 0, 0, 0 };
    uint64_t inspects = 0;

    //static bool monckeySort(monckey const& m1, monckey const& m2)
    //{
    //  return m1.inspects > m2.inspects;
    //}
};

void readInput05_2022(std::ifstream& infile, std::vector<std::stack<char>>& crane, std::vector<std::vector<int>>& moves)
{
    std::vector<std::vector<char>> stackAux;
    //std::regex pattern1 = std::regex{ "[\\[(\\w))\\]\\s|\\s\\s\\s\\s]+\\[(\\w)\\]|\\s\\s\\s" };
    std::regex pattern1 = std::regex{ "\\[(\\w)\\]" };
    std::regex pattern2 = std::regex{ "move (\\d+) from (\\d+) to (\\d+)" };
    std::smatch m;
    bool firstTime = true;

    for (std::string line; getline(infile, line); )
    {
        if (line == "") break;

        int j = 0;
        do {
            if (firstTime)
            {
                std::stack<char> nstack = std::stack<char>();
                crane.push_back(nstack);
                std::vector<char> nvector = std::vector<char>();
                stackAux.push_back(nvector);
            }

            std::string subStr = line.substr(j, 3);
            if (regex_match(subStr, m, pattern1))
                stackAux[j / 4].push_back(m[1].str()[0]);
            else
                stackAux[j / 4].push_back(' ');

            j += 4;
        } while (j <= line.size() - 3);

        firstTime = false;
    }

    // Fill stack
    for (int pos = 0; pos < stackAux.size(); pos++)
        for (int v = stackAux[pos].size() - 2; v >= 0; v--)
        {
            if (stackAux[pos][v] != ' ')
                crane[pos].push(stackAux[pos][v]);
        }

    // Fill moves
    for (std::string line; getline(infile, line); )
    {
        regex_match(line, m, pattern2);
        std::vector<int> nvector = std::vector<int>();
        moves.push_back(nvector);

        for (int i = 1; i < m.size(); i++)
        {
            moves[moves.size() - 1].push_back(std::stoi(m[i]));
        }
    }
}

void readInput11_2022(std::ifstream& infile, std::vector<monckey>& monkeys)
{
    std::vector<std::vector<char>> stackAux;
    std::regex pattern1 = std::regex{ "Monkey (\\d+):" };
    std::regex pattern2 = std::regex{ "  Starting items: (.*)" };
    std::regex pattern3 = std::regex{ "  Operation: new = old (\\*|\\+) (\\d+|old)" };
    std::regex pattern4 = std::regex{ "  Test: divisible by (\\d+)" };
    std::regex pattern5 = std::regex{ "    If true: throw to monkey (\\d+)" };
    std::regex pattern6 = std::regex{ "    If false: throw to monkey (\\d+)" };
    std::smatch m;

    int monckeyId = -1;

    for (std::string line; getline(infile, line); )
    {
        if (line == " ") continue;

        if (regex_match(line, m, pattern1)) // Id
        {
            monckey mon;
            mon.id = stoi(m[1]);

            monkeys.push_back(mon);
            monckeyId++;
        }

        if (regex_match(line, m, pattern2)) // Items
        {
            monkeys[monckeyId].items = splitI(m[1].str(), ", ");
        }

        if (regex_match(line, m, pattern3)) // Items
        {
            monkeys[monckeyId].op.push_back(m[1].str());
            monkeys[monckeyId].op.push_back(m[2].str());
        }

        if (regex_match(line, m, pattern4)) // test
        {
            monkeys[monckeyId].test[0] = stoi(m[1]);;
        }

        if (regex_match(line, m, pattern5)) // If true
        {
            monkeys[monckeyId].test[1] = stoi(m[1]);;
        }

        if (regex_match(line, m, pattern6)) // If false
        {
            monkeys[monckeyId].test[2] = stoi(m[1]);;
        }
    }
}

void readInput05_2023(std::ifstream& infile, std::vector<uint64_t>& seeds, std::vector<std::vector<std::tuple<uint64_t, uint64_t, uint64_t>>>& maps)
{
    std::regex pattern = std::regex{ "seeds: (.*)" };
    std::smatch m;

    std::string line; 
    getline(infile, line);
    if (regex_match(line, m, pattern))
        seeds = splitUInt(m[1], " ");
    getline(infile, line); // Space line
    getline(infile, line); // Title map

    int index = 0;
    std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> map;
    std::tuple<uint64_t, uint64_t, uint64_t> numbers;
    for (std::string line; getline(infile, line);)
    {
        if (line == "") {
            maps.push_back(map);
            map.clear();
            getline(infile, line);
            continue;
        }

        std::istringstream iss(line);
        iss >> std::get<0>(numbers) >> std::get<1>(numbers) >> std::get<2>(numbers);
        map.push_back(numbers);
    }

    maps.push_back(map);
}

void readInput13_2023(std::ifstream& infile, std::vector<std::vector<std::string>>& mirrors)
{
    std::vector<std::string> output;
    std::string line;

    while (!infile.eof())
    {
        std::getline(infile, line);
        if (line == "")
        {
            mirrors.push_back(output);
            output.clear();
            continue;
        }
        output.push_back(line);
    }

    if(output.size() > 0) mirrors.push_back(output);

    infile.close();
}