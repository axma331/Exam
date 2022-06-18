#pragma once
#include "ATarget.hpp"
#include <map>

class TargetGenerator {
	std::map<std::string, ATarget*> map;
public:
	TargetGenerator() {}
	~TargetGenerator() {}
	void		learnTargetType(ATarget* target) {map[target->getType()] = target;}
	void		forgetTargetType(const std::string& name) {map.erase(name);}
	ATarget*	createTarget(const std::string& name) {return map[name] != 0 ? map[name] : 0;}
};