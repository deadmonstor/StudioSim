#pragma once
#include "Hammer.h"

class LegendaryHammer : public Hammer
{
public:
    LegendaryHammer();

    void createLegendaryHammer();

    WeaponStats* legendaryHammerStats{};
};

