#pragma once
#include "Sword.h"
class RareSword :
    public Sword
{
public:
    RareSword();

    WeaponStats* rareSwordStats{};
};

