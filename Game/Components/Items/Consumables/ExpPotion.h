#pragma once
#include "ConsumableItem.h"
#include "../../Player/PlayerController.h"

class ExpPotion :
    public ConsumableItem
{
public:
    ExpPotion();
    
    std::string name() override { return "Exp Potion"; }
    std::string itemDescription() override { return "A potion that gives you experience."; }
    std::string rarity() override { return "Common"; }
public:
    ConsumableStats* expPotionStats{};
private:
    void use() override
    {
        PlayerController::Instance()->playerStats->currentEXP += expPotionStats->EXPGained;
        PlayerController::Instance()->UpdateStats();
    }
};

