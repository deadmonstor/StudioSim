#pragma once
#include <list>
#include "glm/fwd.hpp"

class Weapon
{

public:
	virtual void weaponPattern(std::list<glm::fvec2> attackPositions);

};

