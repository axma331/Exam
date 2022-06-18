#pragma once
#include <iostream>
#include "ASpell.hpp"
class ASpell;

class ATarget {
	std::string _type;
public:
	ATarget() {}
	ATarget(std::string type) : _type(type) {}
	virtual ~ATarget() {}
	std::string		getType() {return _type;}
	void			getHitBySpell(ASpell& spell);
	virtual ATarget *clone() const = 0;
};
