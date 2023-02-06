#pragma once
#include "Sword.h"
class CommonSword :
    public Sword
{
public:
    CommonSword();

    std::string name() override { return "Common Sword"; }
    std::string itemDescription() override { return "Common Sword"; }
    std::string rarity() override { return "Common"; }

    WeaponStats* commonSwordStats{};
};

