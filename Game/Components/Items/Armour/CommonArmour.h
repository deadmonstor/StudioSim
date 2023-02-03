#pragma once
#include "ArmourItem.h"
class CommonArmour :
    public ArmourItem
{
public: 
    CommonArmour();

    ArmourStats* commonArmourStats{};
};

