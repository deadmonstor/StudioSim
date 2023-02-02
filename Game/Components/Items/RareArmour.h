#pragma once
#include "Armour.h"
class RareArmour :
    public Armour
{
public:
    RareArmour();

    ArmourStats* rareArmourStats{};
};

