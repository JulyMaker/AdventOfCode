#include <days.h>
#include <glpk.h>

constexpr auto maxSize = 16;
using Container = std::bitset<maxSize>;

struct MachineConfiguration
{
	Container targetState;
	std::vector<Container> switchers;
};

constexpr auto solveSingle(const MachineConfiguration& input)
{
    std::vector<Container> validCandidates;
    const size_t numberOfOptions = (1 << input.switchers.size()) - 1;

    for (size_t candidateNum = 0; candidateNum <= numberOfOptions; candidateNum++)
    {
        Container candidate(candidateNum);
        Container currentState;

        for (size_t i = 0; i < input.switchers.size(); i++)
            if (candidate[i])
                currentState ^= input.switchers[i];

        if (currentState == input.targetState)
            validCandidates.push_back(candidate);
    }

    return validCandidates;
}

constexpr auto solve(const std::vector<MachineConfiguration>& input)
{
    size_t totalResult = 0;

    for (const auto& config : input)
    {
        auto validCandidates = solveSingle(config);

        if (!validCandidates.empty())
        {
            size_t minCount = std::numeric_limits<size_t>::max();

            for (const auto& candidate : validCandidates)
            {
                size_t currentCount = candidate.count();
                if (currentCount < minCount)
                    minCount = currentCount;
            }

            totalResult += minCount;
        }
    }

    return totalResult;
}


constexpr auto deserializeState(const std::string& str)
{
    Container result;
    for (size_t i = 0; i < str.size() && i < maxSize; i++)
        result.set(i, str[i] == '#');

    return result;
}

constexpr auto deserializeSwitcher(std::ranges::range auto config)
{
    Container result;
    for (const auto num : config)
        result.set(num);
    return result;
}

constexpr MachineConfiguration deserializeConfig(std::string target,
    std::span<const Container> switchers)
{
    return {
        .targetState = deserializeState(target),
        .switchers{std::begin(switchers), std::end(switchers)},
    };
}

MachineConfiguration createConfig(const std::string& targetStr,
    const std::vector<std::string>& switcherStrs)
{
    MachineConfiguration config;
    config.targetState = deserializeState(targetStr);

    for (const auto& switcherStr : switcherStrs)
    {
        config.switchers.push_back(deserializeState(switcherStr));
    }

    return config;
}

uint64_t adventDay10P12025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::vector<MachineConfiguration> configurations;
    for (auto& line : in)
    {
        std::vector<std::string> inStr = parseInputReg(line, R"(^\[([\.#]+)\]\s+(.*?)\s+\{(.*)\}$)");
        auto mask = inStr[1];
        auto buttons = inStr[2];
        
        std::regex switcher_pattern(R"(\(([0-9,]+)\))");
        std::sregex_iterator it(buttons.begin(), buttons.end(), switcher_pattern);
        std::sregex_iterator end;

        std::vector<Container> switchers;

        for (; it != end; ++it) 
        {
            std::string switcher_str = (*it)[1];

            std::vector<int> numbers;
            std::regex number_pattern(R"(\d+)");
            std::sregex_iterator num_it(switcher_str.begin(), switcher_str.end(), number_pattern);
            std::sregex_iterator num_end;

            for (; num_it != num_end; ++num_it)
                numbers.push_back(std::stoi((*num_it)[0]));

            switchers.push_back(deserializeSwitcher(numbers));
        }

        configurations.push_back(deserializeConfig(mask, switchers));
    }

    score = solve(configurations);

    return score;
}

struct Machine 
{
    std::string pattern;
    std::vector<std::vector<uint64_t>> buttons;
    std::vector<int> joltages;

    Machine(std::string p, std::vector<std::vector<uint64_t>> b,
        std::vector<int> j) : pattern(p), buttons(b), joltages(j) {}
};

uint64_t adventDay10P22025(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInput(input, '\n');

    std::vector<Machine> factory;
    for (auto& line : in)
    {
        std::vector<std::string> inStr = parseInputReg(line, R"(^\[([\.#]+)\]\s+(.*?)\s+\{(.*)\}$)");
        auto mask = inStr[1];
        auto buttonsStr = inStr[2];
        std::vector<int> joltages = splitI(inStr[3], ",");

        std::regex switcher_pattern(R"(\(([0-9,]+)\))");
        std::sregex_iterator it(buttonsStr.begin(), buttonsStr.end(), switcher_pattern);
        std::sregex_iterator end;

        std::vector<std::vector<uint64_t>> buttons;

        for (; it != end; ++it)
        {
            std::string switcher_str = (*it)[1];

            std::vector<uint64_t > button;
            std::regex number_pattern(R"(\d+)");
            std::sregex_iterator num_it(switcher_str.begin(), switcher_str.end(), number_pattern);
            std::sregex_iterator num_end;

            for (; num_it != num_end; ++num_it)
                button.push_back(std::stoi((*num_it)[0]));

            buttons.push_back(button);
        }

        factory.push_back(Machine(mask, buttons, joltages));
    }

    for (const auto& machine : factory) 
    {
        long long total = 0;
    
        const int n_buttons = machine.buttons.size();
        const int n_counters = machine.pattern.length();
    
        std::vector<std::vector<int>> A(n_counters, std::vector<int>(n_buttons, 0));
        for (int j = 0; j < n_buttons; j++) {
            for (int idx : machine.buttons[j]) {
                if (idx >= 0 && idx < n_counters) {
                    A[idx][j] = 1;
                }
            }
        }
    
        glp_prob* lp = glp_create_prob();
        glp_set_prob_name(lp, "day10");
        glp_set_obj_dir(lp, GLP_MIN);
    
        glp_add_rows(lp, n_counters);
        for (int i = 0; i < n_counters; i++) {
            glp_set_row_bnds(lp, i + 1, GLP_FX, machine.joltages[i], machine.joltages[i]);
        }
    
        glp_add_cols(lp, n_buttons);
        for (int j = 0; j < n_buttons; j++) {
            glp_set_col_bnds(lp, j + 1, GLP_LO, 0.0, 0.0);
            glp_set_col_kind(lp, j + 1, GLP_IV);
            glp_set_obj_coef(lp, j + 1, 1);
        }
    
        int nz = n_buttons * n_counters;
        std::vector<int> ia(nz + 1), ja(nz + 1);
        std::vector<double> ar(nz + 1);
    
        int k = 1;
        for (int i = 0; i < n_counters; i++) {
            for (int j = 0; j < n_buttons; j++) {
                ia[k] = i + 1;
                ja[k] = j + 1;
                ar[k] = A[i][j];
                k++;
            }
        }
    
        glp_load_matrix(lp, nz, ia.data(), ja.data(), ar.data());
    
        glp_iocp parm;
        glp_init_iocp(&parm);
        parm.presolve = GLP_ON;
        parm.msg_lev = GLP_MSG_OFF;
    
        int err = glp_intopt(lp, &parm);
    
        if (err != 0) {
            std::cout << "GLPK failed to solve the problem.\n";
            return 1;
        }
    
        int status = glp_mip_status(lp);
        if (status == GLP_OPT || status == GLP_FEAS) {
            for (int j = 0; j < n_buttons; j++) {
                long long val = glp_mip_col_val(lp, j + 1);
                total += val;
            }
        }
        else {
            std::cout << "No feasible integer solution.\n";
        }
    
        glp_delete_prob(lp);
    
        score += total;
    }

    return score;
}