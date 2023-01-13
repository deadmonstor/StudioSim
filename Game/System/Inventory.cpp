#include "Inventory.h"
#include <iostream>
#include "imgui/imgui.h"

Inventory::Inventory(int max) : max_items(max) {}

bool Inventory::add_item(Item item)
{
	if (items.size() >= max_items)
	{
		std::cout << "Inventory is full. Can't add more items.\n";
		return false;
	}
	items.push_back(item);
	return true;
}

bool Inventory::remove_item(std::string item_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].name == item_name)
		{
			items.erase(items.begin() + i);
			return true;
		}
	}
	std::cout << "Item not found in inventory.\n";
	return false;
}

void Inventory::draw_inventory() {
	std::cout << "Inventory:\n";
	for (int i = 0; i < items.size(); i++) {
		std::cout << i + 1 << ". " << items[i].name;
		if (items[i].type == "Weapon") {
			std::cout << " (Atk:" << items[i].atk << " / Crit:" << items[i].crit << ")";
		}
		else if (items[i].type == "Armour") {
			std::cout << " (Def:" << items[i].def <<" )";
		}
		else if (items[i].type == "Spell") {
			std::cout << " (Spell Power:" << items[i].spellAtk << " / Mana Cost:" << items[i].manaCost << " / Effect Duration:" << items[i].effectDuration << ")";
		}
		if (items[i].isEquipped) {
			std::cout << " (equipped) ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//void Inventory::draw_inventory_imgui() {
//	ImGui::Begin("Inventory");
//	ImGui::Text("There are %d items in the inventory", items.size());
//	for (int i = 0; i < items.size(); i++) {
//		ImGui::PushID(i);
//		ImGui::BulletText("%s - %s (Atk: %d / Def: %d / Matk: %d / Mdef: %d / Spd: %d / Acc: %d / Crit: %d)", items[i].name.c_str(), items[i].type.c_str(),
//			items[i].atk, items[i].def, items[i].matk, items[i].mdef, items[i].spd, items[i].acc, items[i].crit);
//		ImGui::PopID();
//	}
//	ImGui::End();
//}

void Inventory::use_item(std::string item_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].name == item_name)
		{
			if (items[i].type == "Potion")
			{
				std::cout << "You used a " << items[i].name << " and recovered 20 HP.\n";
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
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].name == item_name) // Searches to find items in vector 
		{
			if (!items[i].isEquipped) // Checks if item is already equipped
			{
				if (items[i].type == "Weapon")
				{
					for (size_t j = 0; j < items.size(); j++)
					{
						if (items[j].isEquipped && items[j].equipSlot == "Weapon")
						{
							items[j].isEquipped = false;
						}
					}
				}
				else if (items[i].type == "Armour")
				{
					for (int j = 0; j < items.size(); j++)
					{
						if (items[j].isEquipped && items[j].equipSlot == "Armour")
						{
							items[j].isEquipped = false;
						}
					}
				}
				else if (items[i].type == "Spells")
				{
					for (int j = 0; j < items.size(); j++)
					{
						if (items[j].isEquipped && items[j].equipSlot == "Spells")
						{
							items[j].isEquipped = false;
						}
					}
				}
				items[i].isEquipped = true;
				std::cout << "You have equipped a " << items[i].name << std::endl;
			}
			return;
		}
	}
	std::cout << "Item not found in inventory" << std::endl;
}

void Inventory::unequip_item(std::string item_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].name == item_name)
		{
			if (items[i].isEquipped)
			{
				items[i].isEquipped = false;
				std::cout << "You have unequipped a " << items[i].name << std::endl;
			}
			return;
		}
	}

	std::cout << "Item not found in the inventory " << std::endl;
}


