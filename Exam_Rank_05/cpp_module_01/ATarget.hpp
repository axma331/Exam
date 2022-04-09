#pragma once

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget {
private:
	std::string _type;

public:
	ATarget(std::string type) { _type = type; }

	virtual ~ATarget() {}

	std::string const getType() { return _type; }

	void getHitBySpell(ASpell &aspell_ref);

	virtual ATarget *clone() const = 0;
};

