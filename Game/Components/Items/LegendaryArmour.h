#pragma once
#include "Armour.h"
class LegendaryArmour :
    public Armour
{
public:
    LegendaryArmour();

    ArmourStats* legendaryArmourStats{};
};

