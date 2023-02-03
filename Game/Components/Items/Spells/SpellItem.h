#pragma once
#include "../Stats.h"
#include "../../../System/Inventory.h"

class SpellItem :
    public Item
{
public:
    int getManaCost() { return spellStats->manaCost; }
    int getCoolDown() { return spellStats->cooldown; }
    int getSpellAtk() { return spellStats->damagePerTurn; }

    bool isEquipable() override { return true; }
	
    ItemType getItemType() override { return ItemType::SPELL; }
    EquipSlot getEquipSlot() override { return EquipSlot::SPELL; }
    
    SpellsStats* spellStats = new SpellsStats();
};

