#pragma once
#include "ConsumableItem.h"
#include "../Player/PlayerController.h"

class ManaPotion :
    public ConsumableItem
{
public:
    ManaPotion();

    std::string name() override { return "Mana Potion"; }
    std::string itemDescription() override { return "A mana potion"; }

    void use() override
    {
        // ASSUMED THAT THIS IS ONLY ON THE PLAYER
        PlayerStats* stats = PlayerController::Instance()->playerStats;
        
        stats->currentMana += manaPotionStats->manaGained;
        stats->currentMana = glm::clamp(stats->currentMana, 0, stats->maxMana);
    }

    ConsumableStats* manaPotionStats{};
};

