#pragma once
#include "Stats.h"
#include "../../System/Inventory.h"

class ArmourItem :
    public Item
{
public:
    bool isEquipable() override { return true; }
    ItemType getItemType() override { return ItemType::ARMOUR; }
    EquipSlot getEquipSlot() override { return EquipSlot::ARMOUR; }
    
    ArmourStats* armour = new ArmourStats();
};

