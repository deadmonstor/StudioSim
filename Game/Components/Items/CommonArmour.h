#pragma once
#include "Armour.h"
class CommonArmour :
    public Armour
{
public: 
    CommonArmour();

    ArmourStats* commonArmourStats{};
};

