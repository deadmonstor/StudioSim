#pragma once
#include "ArmourItem.h"
class RareArmour :
    public ArmourItem
{
public:
    RareArmour();

    ArmourStats* rareArmourStats{};
};

