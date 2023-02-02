#pragma once
#include <list>
#include "glm/fwd.hpp"

class WeaponEnum
{

public:
	virtual void weaponPattern(std::list<glm::fvec2> attackPositions);

};

