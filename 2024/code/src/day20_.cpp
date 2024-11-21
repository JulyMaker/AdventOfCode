#include <days.h>

#define ALL(x) (x).begin(),(x).end()
#define ALLc(x) (x).cbegin(),(x).cend()

enum class ModuleType{ None, FlipFlop, Conjunction };

struct Module
{
	ModuleType type = ModuleType::None;

	bool flipflopOn= false;
	std::vector<std::string> destinations;
	std::map<std::string, bool> inputs;
};

struct Pulse
{
	std::string from, to;
	bool high;
};

void pushButton(std::deque<Pulse>& pulseQueue, std::map<std::string, Module>& modules, 
	            uint64_t& highs, uint64_t& lows, const int pulseCount)
{
	pulseQueue.emplace_back("button", "broadcaster", false); // false low, true high
	while (!pulseQueue.empty())
	{
		Pulse& pulse = pulseQueue.front();

		if (pulse.high) ++highs;
		else ++lows;

		Module& module = modules[pulse.to];
		switch (module.type)
		{
		  case ModuleType::None:
		  	 for (auto& dest : module.destinations)
		  		 pulseQueue.emplace_back(pulse.to, dest, pulse.high);
		  	 break;
		  case ModuleType::FlipFlop:
		  	 if (!pulse.high)
		  	 {
		  		module.flipflopOn = !module.flipflopOn;
		  		for (auto& dest : module.destinations)
		  			pulseQueue.emplace_back(pulse.to, dest, module.flipflopOn);
		  	 } 
		  	 break;
		  default:
		  {
			module.inputs[pulse.from] = pulse.high;

			bool allHigh = true;
			for (auto& [_, high] : module.inputs)
				allHigh= allHigh && high;

			for (auto& dest : module.destinations)
				pulseQueue.emplace_back(pulse.to, dest, !allHigh);
		  }
		}

		pulseQueue.pop_front();
	}
};

uint64_t adventDay20P12024(std::ifstream& input)
{
    uint64_t score = 0;

    std::vector<std::string> in = parseInputReg(input, "(.*) -> (.*)");
	std::map<std::string, Module> modules;
	std::vector<std::string> conjuctions;
	std::string name;
	for (int i = 0; i < in.size(); i += 3)
	{		
		Module module;

		std::vector<std::string> dest = splitS(in[i + 2], ",");
		for(auto&s : dest)
			s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

		module.destinations.insert(module.destinations.end(), ALL(dest));
		name = in[i + 1];
		if (name[0] == '%')
		{
			name = name.substr(1);
			module.type = ModuleType::FlipFlop;
		}
		else if (name[0] == '&')
		{
			name = name.substr(1);
			module.type = ModuleType::Conjunction;
			conjuctions.push_back(name);
		}

		modules[name] = module;
	}

	std::sort(ALL(conjuctions));
	for (auto& [name, mod] : modules)
		for (const std::string& dest : mod.destinations)
			if (std::binary_search(ALLc(conjuctions), dest))
				modules[dest].inputs[name] = false;


	uint64_t lows = 0, highs = 0;
	std::deque<Pulse> pulseQueue;
	for(int pulseCount =0; pulseCount < 1000; pulseCount++)
		pushButton(pulseQueue, modules, highs, lows, pulseCount);

	score = lows * highs;

    return score;
}

void pushButton(std::deque<Pulse>& pulseQueue, std::map<std::string, Module>& modules, std::map<std::string, uint64_t>& search, const int pulseCount)
{
	pulseQueue.emplace_back("button", "broadcaster", false); // false low, true high
	while (!pulseQueue.empty())
	{
		Pulse& pulse = pulseQueue.front();

		Module& module = modules[pulse.to];
		switch (module.type)
		{
		    case ModuleType::None:
		    	for (auto& dest : module.destinations)
		    		pulseQueue.emplace_back(pulse.to, dest, pulse.high);
		    	break;
		    case ModuleType::FlipFlop:
		    	if (!pulse.high)
		    	{
		    		module.flipflopOn = !module.flipflopOn;
		    		for (auto& dest : module.destinations)
		    			pulseQueue.emplace_back(pulse.to, dest, module.flipflopOn);
		    	}
		    	break;
		    default:
		    {
		    	module.inputs[pulse.from] = pulse.high;
		    
		    	bool allHigh = true;
		    	for (auto& [_, high] : module.inputs)
		    		allHigh = allHigh && high;
		    	
		    	if (!allHigh)
		    		if (search[pulse.to] == 0)
						search[pulse.to] = pulseCount;
		    
		    	for (auto& dest : module.destinations)
		    		pulseQueue.emplace_back(pulse.to, dest, !allHigh);
		    }
		}

		pulseQueue.pop_front();
	}
};

uint64_t adventDay20P22024(std::ifstream& input)
{
    uint64_t score = 1;

	std::vector<std::string> in = parseInputReg(input, "(.*) -> (.*)");
	std::map<std::string, Module> modules;
	std::vector<std::string> conjuctions;
	std::string name, rxInput;
	for (int i = 0; i < in.size(); i += 3)
	{
		Module module;

		std::vector<std::string> dest = splitS(in[i + 2], ",");
		for (auto& s : dest)
			s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

		module.destinations.insert(module.destinations.end(), ALL(dest));
		name = in[i + 1];
		if (name[0] == '%')
		{
			name = name.substr(1);
			module.type = ModuleType::FlipFlop;
		}
		else if (name[0] == '&')
		{
			name = name.substr(1);
			module.type = ModuleType::Conjunction;
			conjuctions.push_back(name);
		}

		if (std::find(ALLc(module.destinations), "rx") != module.destinations.cend())
			rxInput = name;

		modules[name] = module;
	}

	std::sort(ALL(conjuctions));
	for (auto& [name, mod] : modules)
		for (const std::string& dest : mod.destinations)
			if (std::binary_search(ALLc(conjuctions), dest))
				modules[dest].inputs[name] = false;

	std::map<std::string, uint64_t> search;
	for (auto& [input, _] : modules[rxInput].inputs)
		search[input] = 0;

	uint64_t pulseCount = 0;
	std::deque<Pulse> pulseQueue;
	bool hasZero= false;
	do{
		++pulseCount;
		pushButton(pulseQueue, modules, search, pulseCount);

		hasZero = false;
		for (auto& [_, cycle] : search)
			hasZero = hasZero || !cycle;
	} while (hasZero);

	for (auto& [_, cycle] : search)
		score= std::lcm(score, cycle);

	return score;
}