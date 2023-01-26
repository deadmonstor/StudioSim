#pragma once
#include "Stats.h"
#include "glm/fwd.hpp"
#include <list>
#include <vector>

class Weapon
{

public:
	virtual void weaponPattern(std::list<glm::fvec2> attackPositions) {};

};

