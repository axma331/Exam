#pragma once

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell {
private:
	std::string _name;
	std::string _effects;

public:
	ASpell() {}
	ASpell(std::string name, std::string effects) {
		_name = name;
		_effects = effects;
	}

	virtual ~ASpell() {}

	std::string  getName() { return _name; }
	std::string  getEffects() { return _effects; }

	void launch(ATarget &atarget_ref);

	virtual ASpell *clone() const = 0;
};
