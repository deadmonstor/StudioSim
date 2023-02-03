#pragma once
#include "Sword.h"

class RareSword :
    public Sword
{
public:
    RareSword();
    std::string name() override { return "Rare Sword"; }
    std::string itemDescription() override { return "Rare Sword"; }
    std::string rarity() override { return "Rare"; }

    WeaponStats* rareSwordStats{};
};

