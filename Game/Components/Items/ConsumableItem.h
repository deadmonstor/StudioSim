#pragma once
#include "Stats.h"
#include "../../System/Inventory.h"
#include "Util/Logger.h"

class ConsumableItem :
    public Item
{
    ItemType getItemType() override { return ItemType::CONSUMABLE; }
    bool isUsable() override { return true; }

    void use() override
    {
        LOG_INFO("Used item: " + name());
    }
    
    ConsumableStats* consumables;
};

