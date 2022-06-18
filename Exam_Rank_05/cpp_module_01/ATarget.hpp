#pragma once
#include <iostream>
#include "ASpell.hpp"
class ASpell;

class ATarget {
	std::string	_type;
public:
	ATarget(const std::string& type) : _type(type) {}
	~ATarget() {}
	const std::string&	getType() const {return _type;}
	virtual ATarget*	clone() const = 0;
	void				getHitBySpell(ASpell& spell) const;
};