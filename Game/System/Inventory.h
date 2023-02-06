#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Core/Component.h"
#include "../Components/Items/Stats.h"

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
	PlayerStats* playerStats;

	Item* getFirstItemWithEquipSlot(EquipSlot slot);
	
	inline static std::map<std::string, std::function<Item*()>> getItemByName = {};
};