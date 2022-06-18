#pragma once
#include "ATarget.hpp"

struct BrickWall : ATarget {
	BrickWall() : ATarget("Inconspicuous Red-brick Wall") {}
	~BrickWall() {}
	virtual ATarget*	clone() const {return new BrickWall();}
};