#pragma once
#include "Axe.h"
class RareAxe :
    public Axe
{
public:
    RareAxe();

    std::string name() override { return "Rare Axe"; }
    std::string itemDescription() override { return "A rare axe"; }
    std::string rarity() override { return "Rare"; }

    WeaponStats* rareAxeStats{};
};

