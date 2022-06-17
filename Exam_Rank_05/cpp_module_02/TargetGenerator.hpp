#pragma once
#include "ATarget.hpp"
#include <map>

class TargetGenerator {
	std::map <std::string, ATarget*> map;
public:
	TargetGenerator() {}
	~TargetGenerator() {}

	void learnTargetType(ATarget *target) {
		map[target->getType()] = target;
	}
	void forgetTargetType(std::string name) {
		map.erase(name);
	}

	ATarget* createTarget(std::string name) {
		if (map[name] != 0)
			return map[name];
		return 0;
	}
};
