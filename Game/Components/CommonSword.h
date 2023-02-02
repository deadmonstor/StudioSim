#pragma once
#include "Sword.h"
class CommonSword :
    public Sword
{
public:
    CommonSword();

    void createCommonSword();

    WeaponStats* commonSwordStats{};
};

