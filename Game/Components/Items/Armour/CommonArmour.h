#pragma once
#include "ArmourItem.h"
class CommonArmour :
    public ArmourItem
{
public: 
    CommonArmour();
    std::string name() override { return "Common Armour"; }
    std::string itemDescription() override { return "A common armour."; }
    std::string rarity() override { return "Common"; }

    ArmourStats* commonArmourStats{};
};

