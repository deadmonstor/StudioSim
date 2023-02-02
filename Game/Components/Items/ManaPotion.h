#pragma once
#include "Consumables.h"
class ManaPotion :
    public Consumables
{
public:
    ManaPotion();

    ConsumableStats* manaPotionStats{};
};

