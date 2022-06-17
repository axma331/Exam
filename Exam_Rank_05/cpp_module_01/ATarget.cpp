#include "ATarget.hpp"

void ATarget::getHitBySpell(ASpell &spell) {
	std::cout << _type << " has been " << spell.getEffects() << "!\n";
}
