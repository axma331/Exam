#pragma once
#include "ASpell.hpp"

struct Fwoosh: public ASpell {
	Fwoosh() : ASpell("Fwoosh", "fwooshed") {}
	~Fwoosh() {}
	virtual ASpell*	clone() const {return new Fwoosh();}
};