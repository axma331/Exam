#pragma once

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget {
private:
	std::string _type;

public:
	ATarget() {};
	ATarget(std::string type) { this->_type = type; }

	virtual ~ATarget() {}

	std::string getType() { return this->_type; }

	void getHitBySpell(ASpell &aspell_ref);

	virtual ATarget *clone() const = 0;
};
