#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

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

class Inventory
{
private:
	int max_items;
public:
	Inventory(int max);
	std::vector<Item> items;
	std::vector<std::string> equipSlot;
	bool add_item(Item item);
	bool remove_item(std::string item_name);
	void draw_inventory();
	void draw_inventory_imgui();
	void use_item(std::string item_name);
	void equip_item(std::string item_name);
	void unequip_item(std::string item_name);
};

#endif
