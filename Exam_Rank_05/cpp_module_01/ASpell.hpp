#pragma once
#include <iostream>
#include "ATarget.hpp"
class ATarget;

class ASpell {
	std::string	_name;
	std::string	_effects;
public:
	ASpell(const std::string& name, const std::string& effects) : _name(name), _effects(effects) {}
	virtual ~ASpell() {}
	std::string	getName() {return _name;}
	std::string	getEffects() {return _effects;}
	void		launch(const ATarget& target);
	virtual ASpell*	clone() const = 0;
};
