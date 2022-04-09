#include "ATarget.hpp"

void ATarget::getHitBySpell(ASpell &aspell_ref) {
	std::cout << this->_type << " has been " << aspell_ref.getEffects() << "!\n";
}
