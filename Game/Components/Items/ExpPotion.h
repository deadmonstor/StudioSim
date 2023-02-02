#pragma once
#include "ConsumableItem.h"
class ExpPotion :
    public ConsumableItem
{
public:
    ExpPotion();

    ConsumableStats* expPotionStats{};
};

