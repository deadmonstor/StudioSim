#include "Inventory.h"
#include <iostream>
#include "imgui/imgui.h"
#include "Util/Logger.h"

Inventory::Inventory(int max) : max_items(max) {}

bool Inventory::add_item(const Item item)
{
	if (items.size() >= max_items)
	{
		LOG_ERROR("Inventory is full. Can't add more items.");
		return false;
	}
	
	items.push_back(item);
	return true;
}

bool Inventory::remove_item(const std::string& item_name)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].name == item_name)
		{
			items.erase(items.begin() + i);
			return true;
		}
	}
	
	LOG_INFO("Item not found in inventory.");
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

void Inventory::getDebugInfo(std::string* basic_string)
{
	ImGui::Indent();
	for (int i = 0; i < items.size(); i++)
	{
		ImGui::Text("%d. %s", i + 1, items[i].name.c_str());
		ImGui::Indent();
		if (items[i].type == "Weapon")
		{
			ImGui::Text("Atk: %d / Crit: %d", items[i].atk, items[i].crit);
		}
		else if (items[i].type == "Armour")
		{
			ImGui::Text("Def: %d", items[i].def);
		}
		else if (items[i].type == "Spell")
		{
			ImGui::Text("Spell Power: %d / Mana Cost: %d / Effect Duration: %d", items[i].spellAtk, items[i].manaCost, items[i].effectDuration);
		}
		
		if (items[i].isEquipped)
		{
			ImGui::Text("Equipped");
		}
		ImGui::Unindent();
	}
	ImGui::Unindent();
	
	Component::getDebugInfo(basic_string);
}

void Inventory::use_item(const std::string& item_name)
{
	for (auto& item : items)
	{
		if (item.name == item_name)
		{
			if (item.type == "Potion")
			{
				LOG_INFO("You used a " + item.name + " and recovered 20 HP.");
			}
			else
			{
				LOG_INFO("You used a " + item.name + ".");
			}

			return;
		}
	}
	
	LOG_ERROR("Item not found in inventory");
}

void Inventory::equip_item(const std::string& item_name)
{
	for (auto& item : items)
	{
		if (item.name == item_name) // Searches to find items in vector 
		{
			if (item.isEquipped) // Checks if item is already equipped
			{
				return;
			}
			
			if (item.type == "Weapon")
			{
				for (auto& value : items)
				{
					if (value.isEquipped && value.equipSlot == "Weapon")
					{
						value.isEquipped = false;
					}
				}
			}
			else if (item.type == "Armour")
			{
				for (int j = 0; j < items.size(); j++)
				{
					if (items[j].isEquipped && items[j].equipSlot == "Armour")
					{
						items[j].isEquipped = false;
					}
				}
			}
			else if (item.type == "Spells")
			{
				for (auto& value : items)
				{
					if (value.isEquipped && value.equipSlot == "Spells")
					{
						value.isEquipped = false;
					}
				}
			}
			
			item.isEquipped = true;
			LOG_INFO("You have equipped a " + item.name);
			return;
		}
	}
	
	LOG_ERROR("Item not found in inventory");
}

void Inventory::unequip_item(const std::string& item_name)
{
	for (auto& item : items)
	{
		if (item.name == item_name)
		{
			if (item.isEquipped)
			{
				item.isEquipped = false;
				LOG_INFO("You have unequipped a " + item.name);
			}
			
			return;
		}
	}

	LOG_ERROR("Item not found in inventory");
}


