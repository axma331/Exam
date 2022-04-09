#pragma once

#include "ATarget.hpp"
#include <map>

class TargetGenerator {
private:
	std::map <std::string, ATarget *> map;

public:
	TargetGenerator() {}
	~TargetGenerator() {}

	void learnTargetType(ATarget *target_ptr) {
		map[target_ptr->getType()] = target_ptr;
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
