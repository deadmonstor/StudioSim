#pragma once
#include "ConsumableItem.h"
#include "../../Player/PlayerController.h"

class HealthPotion :
    public ConsumableItem
{
public: 
    HealthPotion();
    
    std::string name() override
    {
        return "Health Potion";
    }
    
    std::string itemDescription() override
    {
        return "A health potion";
    }

    void use() override
    {
        // ASSUMED THAT THIS IS ONLY ON THE PLAYER
        PlayerStats* stats = PlayerController::Instance()->playerStats;
        
        stats->currentHealth += healthPotionStats->healthGained;
        stats->currentHealth = glm::clamp(stats->currentHealth, 0, stats->maxHealth);
        PlayerController::Instance()->UpdateStats();
    }

    ConsumableStats* healthPotionStats{};
};

