#include "ASpell.hpp"

void ASpell::launch(ATarget &atarget_ref) {
	atarget_ref.getHitBySpell(*this);
}
