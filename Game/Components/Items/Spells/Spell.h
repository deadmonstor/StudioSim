#pragma once
#include "../../../System/Inventory.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "../Stats.h"

class SpellItem :
    public Item
{
public:
    virtual void UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir) {}
    SpellsStats* spellStats = new SpellsStats();

    bool isEquipable() override { return true; }
    ItemType getItemType() override { return ItemType::SPELL; }
    EquipSlot getEquipSlot() override { return EquipSlot::SPELL; }
};

