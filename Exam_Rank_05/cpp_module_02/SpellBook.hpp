#pragma once
#include "ASpell.hpp"
#include <map>

class SpellBook {
	std::map<std::string, ASpell*> map;
public:
	SpellBook() {}
	~SpellBook() {}

	void learnSpell(ASpell* spell) {
		map[spell->getName()] = spell;
	}
	void forgetSpell(std::string name) {
		map.erase(name);
	}
	ASpell* createSpell(std::string name) {
		if (map[name] != 0)
			return map[name];
		return 0;
	};
};
