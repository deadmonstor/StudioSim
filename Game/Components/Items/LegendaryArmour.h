#pragma once
#include "ArmourItem.h"
class LegendaryArmour :
    public ArmourItem
{
public:
    LegendaryArmour();
    
    std::string name() override { return "Legendary Armour"; }
    std::string itemDescription() override { return "Legendary Armour"; }
    std::string rarity() override { return "Legendary"; }

    ArmourStats* legendaryArmourStats{};
};

