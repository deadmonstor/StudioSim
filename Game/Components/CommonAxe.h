#pragma once
#include "Axe.h"
class CommonAxe :
    public Axe
{
public:
    CommonAxe();

    void createCommonAxe();

    WeaponStats* commonAxeStats{};
};

