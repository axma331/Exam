#include "ASpell.hpp"

void	ASpell::launch(const ATarget& target) {
	target.getHitBySpell(*this);
}

