#pragma once

#include "ASpell.hpp"
#include <map>

class SpellBook {
private:
	std::map<std::string, ASpell *> map;

public:
	SpellBook() {}
	~SpellBook() {}

	void learnSpell(ASpell *aspell_ptr) {
		map[aspell_ptr->getName()] = aspell_ptr;
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
