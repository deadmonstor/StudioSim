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
	bool isEquipped;
	int atk; // Added on to health and strength
	int def; // Added on to agility and crit 
	int manaCost;// Added on to intelligence and spell power
	int coolDown;
	int effectDuration;
	int spellAtk;  
	int crit;
};

class Inventory : public Component
{
	int max_items;
	
public:
	explicit Inventory(int max);
	std::vector<Item> items;
	std::vector<std::string> equipSlot;
	bool add_item(Item item);
	void draw_inventory();

	void getDebugInfo(std::string*) override;
	
	bool remove_item(const std::string& item_name);
	void use_item(const std::string& item_name);
	void equip_item(const std::string& item_name);
	void unequip_item(const std::string& item_name);
};

#endif
