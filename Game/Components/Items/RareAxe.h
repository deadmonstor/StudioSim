#pragma once
#include "Axe.h"
class RareAxe :
    public Axe
{
public:
    RareAxe();

    void createRareAxe();

    WeaponStats* rareAxeStats{};
};

