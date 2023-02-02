#pragma once
#include "Consumables.h"
class ExpPotion :
    public Consumables
{
public:
    ExpPotion();

    ConsumableStats* expPotionStats{};
};

