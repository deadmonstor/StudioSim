#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

#include "Core/Component.h"

struct Item
{
	std::string name;
	std::string type;
	std::string itemDescription;
	std::string equipSlot;
	std::string rarity;
	int price;
	int getPrice() { return price; }
	bool isUsable;
	bool isEquipped;
	virtual ~Item() {}; // added virtual destructor
};

struct TestWeapon : Item
{
	int atk; // Added on to health and strength
	int getAtk() { return atk; }

	int crit;
	int getCrit() { return crit; };
};

struct Spell : Item
{
	int manaCost;// Added on to intelligence and spell power
	int getManaCost() { return manaCost; }

	int coolDown;
	int getCoolDown() { return coolDown; }

	int effectDuration;
	int getEffectDuration() { return effectDuration; }

	int spellAtk;
	int getSpellAtk() { return spellAtk; }
};

struct Armour : Item
{
	int def;  // Added on to agility and crit
	int getDef() { return def; }
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
};

#endif