#ifndef INVENTORY_H
#define INVENTORY_H

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




//struct Weapon : public Item
//{
//	int atk; // Added on to health and strength
//	int getAtk() { return atk; }
//
//	int crit;
//	int getCrit() { return crit; };
//};
//
//struct Spell : public Item
//{
//	int manaCost;// Added on to intelligence and spell power
//	int getManaCost() { return manaCost; }
//
//	int coolDown;
//	int getCoolDown() { return coolDown; }
//
//	int effectDuration;
//	int getEffectDuration() { return effectDuration; }
//
//	int spellAtk;
//	int getSpellAtk() { return spellAtk; }
//};
//
//struct Armour : public Item
//{
//	int def;  // Added on to agility and crit
//	int getDef() { return def; }
//};

//struct Item
//{
//	std::string name;
//	std::string type;
//	std::string itemDescription;
//	std::string equipSlot;
//	std::string rarity;
//	int price;
//	int getPrice() { return price; }
//	bool isUsable;
//	bool isEquipped;
//	virtual ~Item() {}; // added virtual destructor
//};

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

	WeaponStats* getWeaponEquipped() 
	{
		for ( auto item : items)
		{
			WeaponStats* weapon = dynamic_cast<WeaponStats*>(item);
			if (weapon && weapon->isEquipped)
			{
				return weapon;
			}
		}
	}

	ArmourStats* getArmourEquipped()
	{
		for (auto item : items)
		{
			ArmourStats* armour = dynamic_cast<ArmourStats*>(item);
			if (armour && armour-> isEquipped)
			{
				return armour;
			}
		}
	}

	SpellsStats* getSpellsEquipped()
	{
		for (auto item : items)
		{
			SpellsStats* spell = dynamic_cast<SpellsStats*>(item);
			if (spell && spell->isEquipped)
			{
				return spell;
			}
		}
	}
};

#endif