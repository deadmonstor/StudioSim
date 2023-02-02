#pragma once

#include <string>
#include <vector>

#include "Core/Component.h"
#include "../Components/Items/Axe.h"
#include "../Components/Items/ItemStats.h"
#include "../Components/Items/CharacterStats.h"
#include "../Components/Items/CommonArmour.h"
#include "../Components/Items/CommonAxe.h"
#include "../Components/Items/CommonDagger.h"
#include "../Components/Items/CommonSword.h"
#include "../Components/Items/Consumables.h"
#include "../Components/Items/Dagger.h"
#include "../Components/Items/ExpPotion.h"
#include "../Components/Items/Hammer.h"
#include "../Components/Items/HealthPotion.h"
#include "../Components/Items/LegendaryArmour.h"
#include "../Components/Items/LegendaryHammer.h"
#include "../Components/Items/ManaPotion.h"
#include "../Components/Items/RareArmour.h"
#include "../Components/Items/RareAxe.h"
#include "../Components/Items/RareSword.h"
#include "../Components/Items/Stats.h"
#include "../Components/Items/Weapon.h"

enum class ItemType
{
	WEAPON,
	SPELL,
	ARMOUR,
	CONSUMABLE,
	NOTSET
};

enum class EquipSlot
{
	ARMOUR,
	WEAPON,
	SPELL,
	NOTSET
};

class Item
{
public:
	virtual std::string name() { return "NOT SET"; }
	virtual std::string itemDescription() { return "NOT SET"; }
	virtual std::string rarity() { return "NOT SET"; }
	
	int price;
	int getPrice() { return price; }
	
	virtual bool isUsable() { return false; }
	virtual bool isEquipable() { return false; }
	bool isEquipped;

	virtual void use() {}
	virtual EquipSlot getEquipSlot() { return EquipSlot::NOTSET; }
	virtual ItemType getItemType() { return ItemType::NOTSET; }
};

class SpellItem : public Item
{
public:
	int manaCost;// Added on to intelligence and spell power
	int getManaCost() { return manaCost; }

	int coolDown;
	int getCoolDown() { return coolDown; }

	int effectDuration;
	int getEffectDuration() { return effectDuration; }

	int spellAtk;
	int getSpellAtk() { return spellAtk; }

	bool isEquipable() override { return true; }
	
	ItemType getItemType() override { return ItemType::SPELL; }
	EquipSlot getEquipSlot() override { return EquipSlot::SPELL; }
};

class Inventory : public Component
{
	int max_items;
	
public:
	Inventory(int max)
	{
		this->max_items = max;
	}
	
	std::vector<Item*> items;
	bool add_item(Item* item);
	bool remove_item(Item* item);
	void draw_inventory();
	void getDebugInfo(std::string*) override;
	bool remove_item(const std::string& item_name);
	void use_item(const std::string& item_name);
	void equip_item(const std::string& item_name);
	void unequip_item(const std::string& item_name);

	Item* getFirstItemWithEquipSlot(EquipSlot slot);
};