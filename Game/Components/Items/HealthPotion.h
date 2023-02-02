#pragma once
#include "Consumables.h"
class HealthPotion :
    public Consumables
{
public: 
    HealthPotion();

    ConsumableStats* healthPotionStats{};
};

