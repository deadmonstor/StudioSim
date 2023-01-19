#include "Inventory.h"
#include <iostream>
#include "imgui/imgui.h"

bool Inventory::add_item(Item* item)
{
	if (items.size() >= max_items)
	{
		std::cout << "Inventory is full. Can't add more items.\n";
		return false;
	}
	items.push_back(item);
	std::cout << "You added a " << item->name << std::endl;
	return true;
}
bool Inventory::remove_item(Item* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->name == item->name)
		{
			items.erase(items.begin() + i);
			std::cout << "You have removed a " << item->name << std::endl;
			return true;
		}
	}
	std::cout << "Item not found in inventory.\n";
	return false;
}

void Inventory::draw_inventory() {
	std::cout << "Inventory:\n";
	for (int i = 0; i < items.size(); i++)
	{
		std::cout << i + 1 << ". " << items[i]->name;
		if (dynamic_cast<Weapon*>(items[i])) {
			auto item = dynamic_cast<Weapon*>(items[i]);
			std::cout << " (Atk:" << item->getAtk() << " / Crit:" << item->getCrit() << ")";
		}
		else if (dynamic_cast<Armour*>(items[i])) {
			auto item = dynamic_cast<Armour*>(items[i]);
			std::cout << " (Def:" << item->getDef() << " )";
		}
		else if (dynamic_cast<Spell*>(items[i])) {
			auto item = dynamic_cast<Spell*>(items[i]);
			std::cout << " (Spell Power:" << item->getSpellAtk() << " / Mana Cost:" << item->getManaCost() << " / Effect Duration:" << item->getEffectDuration() << ")";
		}
		if (items[i]->isEquipped) {
			std::cout << " (equipped) ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Inventory::use_item(std::string item_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->name == item_name)
		{
			if (items[i]->type == "Potion")
			{
				std::cout << "You used a " << items[i]->name << " and recovered 20 HP.\n";
			}
			else
			{
				std::cout << "You can't use this item.\n";
			}
			return;
		}
	}
	std::cout << "Item not found in inventory.\n";
}

void Inventory::equip_item(std::string item_name)
{
	for (auto item : items)
	{
		if (item->name == item_name)
		{
			if (dynamic_cast<Weapon*>(item) != nullptr) // check if item is a weapon
			{
				Weapon* weapon = dynamic_cast<Weapon*>(item);
				weapon->isEquipped = true; // set isEquipped to true for the weapon
				std::cout << weapon->name << " equipped." << std::endl;
				break;
			}
			else if (dynamic_cast<Armour*>(item) != nullptr) // check if item is an armor
			{
				Armour* armor = dynamic_cast<Armour*>(item);
				armor->isEquipped = true; // set isEquipped to true for the armor
				std::cout << armor->name << " equipped." << std::endl;
				break;
			}
			else if (dynamic_cast<Spell*>(item) != nullptr)
			{
				Spell* spell = dynamic_cast<Spell*>(item);
				spell->isEquipped = true; // set isEquipped to true for the spell
				std::cout << spell->name << " equipped." << std::endl;
				break;
			}

			else
			{
				std::cout << item_name << " is not equippable." << std::endl;
				break;
			}
		}
	}
}

void Inventory::unequip_item(std::string item_name)
{
	for (auto item : items)
	{
		if (item->name == item_name)
		{
			if (dynamic_cast<Weapon*>(item) != nullptr) // check if item is a weapon
			{
				Weapon* weapon = dynamic_cast<Weapon*>(item);
				if (weapon->isEquipped) {
					weapon->isEquipped = false; // set isEquipped to false for the weapon
					std::cout << weapon->name << " unequipped." << std::endl;
				}
				else {
					std::cout << weapon->name << " was not equipped." << std::endl;
				}
				break;
			}
			else if (dynamic_cast<Armour*>(item) != nullptr) // check if item is an armor
			{
				Armour* armor = dynamic_cast<Armour*>(item);
				if (armor->isEquipped) {
					armor->isEquipped = false; // set isEquipped to false for the armor
					std::cout << armor->name << " unequipped." << std::endl;
				}
				else {
					std::cout << armor->name << " was not equipped." << std::endl;
				}
				break;
			}
			else if (dynamic_cast<Spell*>(item) != nullptr)
			{
				Spell* spell = dynamic_cast<Spell*>(item);
				if (spell->isEquipped) {
					spell->isEquipped = false;
					std::cout << spell->name << " unequipped." << std::endl;
				}
				else
				{
					std::cout << spell->name << " was not equipped." << std::endl;
				}
				break;
			}
			else
			{
				std::cout << item_name << " is not equippable." << std::endl;
				break;
			}
		}
	}
}



