#include "ATarget.hpp"

void	ATarget::getHitBySpell(ASpell& spell) const {
	std::cout << _type << " has been " << spell.getEffects() << "!\n";
}