#pragma once
#include "ArmourItem.h"
class RareArmour :
    public ArmourItem
{
public:
    RareArmour();

    std::string name() override { return "Rare Armour"; }
    std::string itemDescription() override { return "A rare armour."; }
    std::string rarity() override { return "Rare"; }
    ArmourStats* rareArmourStats{};
};

