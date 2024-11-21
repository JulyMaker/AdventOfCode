#include <days.h>


#define ALLc(x) (x).cbegin(),(x).cend()
using PARSETWO = std::pair<std::vector<std::string>, std::vector<std::string>>;

constexpr std::array<char, 4> ruleIndex{ 'x','m','a','s' };

struct Rule
{
	int index, value;
	bool less;
	std::string target;

	bool evaluate(const std::array<int, 4>& variables) const { return less ? variables[index] < value : variables[index] > value; }
};

struct WorkFlow
{
	std::vector<Rule> rules;
	std::string finishState;

	void processRules(const std::vector<std::string> rulesVector)
	{
		for(auto ruleV : rulesVector)
		{
			std::vector<std::string> ruleS = parseInputReg(ruleV, "(\\w+)([<|>])(\\d+):(.*)");
			if (ruleS.size() == 0)
			{
				finishState = ruleV;
				break;
			}

			Rule rule;
			rule.target = ruleS[4];
			rule.index = std::distance(ruleIndex.cbegin(), std::find(ALLc(ruleIndex), ruleS[1][0]));
			rule.less = ruleS[2][0] == '<';
			rule.value = std::stoi(ruleS[3]);

			rules.push_back(rule);
		}
	}

	const std::string& getNext(const std::array<int, 4>& variables) const
	{
		for (const auto& rule : rules)
			if (rule.evaluate(variables))
				return rule.target;

		return finishState;
	}
};

uint64_t adventDay19P12024(std::ifstream& input)
{
    uint64_t score = 0;

    PARSETWO in = parseInputReg(input, "(.*)\\{(.*)\\}", "\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");
	
	std::map<std::string, WorkFlow> workflows;
	for (int i = 0; i < in.first.size(); i += 3)
	{
		WorkFlow workFlow;
		std::string name = in.first[i + 1];
		workFlow.processRules( splitS(in.first[i + 2], ",") );
		workflows[name] = workFlow;
	}

	for (int j = 0; j < in.second.size(); j+= 5)
	{
		std::array<int, 4> variables;
		for(int h=1; h < 5; h++)
		    variables[h - 1] = std::stoi(in.second[j + h]);

		std::string name = "in";
		while (name != "A" && name != "R")
			name= workflows[name].getNext(variables);

		if (name == "A")
			score+= std::accumulate(ALLc(variables), 0);
	}

    return score;
}

using VariablesArray = std::array<std::pair<int64_t, int64_t>, 4>;

int64_t getCombinations(std::map<std::string, WorkFlow>& workflows, const std::string& name, VariablesArray variablesArray)
{
	if (name == "R")
		return 0;
	if (name == "A")
		return std::accumulate(ALLc(variablesArray), 1ll, [](int64_t acummulated, const std::pair<int64_t, int64_t>& var) {return acummulated * (var.second - var.first + 1); });
	
	int64_t result = 0;
	const WorkFlow& workflow = workflows[name];
	
	for (const Rule& rule : workflow.rules)
	{
		VariablesArray split = variablesArray;
		if (rule.less)
		{
			split[rule.index].second = rule.value - 1;
			variablesArray[rule.index].first = rule.value;
			result+= getCombinations(workflows, rule.target, split);
		}
		else
		{
			split[rule.index].first = rule.value + 1;
			variablesArray[rule.index].second = rule.value;
			result+= getCombinations(workflows, rule.target, split);
		}
	}
	
	return result + getCombinations(workflows, workflow.finishState, variablesArray);
}


uint64_t adventDay19P22024(std::ifstream& input)
{
    uint64_t score = 0;

	PARSETWO in = parseInputReg(input, "(.*)\\{(.*)\\}", "\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");

	std::map<std::string, WorkFlow> workflows;
	for (int i = 0; i < in.first.size(); i += 3)
	{
		WorkFlow workFlow;
		std::string name = in.first[i + 1];
		workFlow.processRules(splitS(in.first[i + 2], ","));
		workflows[name] = workFlow;
	}

	constexpr VariablesArray initial = { std::make_pair(1, 4000), std::make_pair(1, 4000), std::make_pair(1, 4000), std::make_pair(1, 4000) };
	score= getCombinations(workflows, "in", initial);

    return score;
}