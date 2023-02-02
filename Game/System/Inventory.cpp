#include "Inventory.h"
#include <iostream>
#include "imgui/imgui.h"
#include "Util/Logger.h"


bool Inventory::add_item(Item* item)
{
	if (items.size() >= max_items)
	{
		LOG_ERROR("Inventory is full. Can't add more items.");
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
	
	LOG_INFO("Item not found in inventory.");
	return false;
}

void Inventory::draw_inventory() {
	std::cout << "Inventory:\n";
	for (int i = 0; i < items.size(); i++)
	{
		std::cout << i + 1 << ". " << items[i]->name;
		if (dynamic_cast<WeaponStats*>(items[i])) {
			auto item = dynamic_cast<WeaponStats*>(items[i]);
			std::cout << " (Atk:" << item->getAtk() << " / Crit:" << item->getCrit() << ")";
		}
		else if (dynamic_cast<ArmourStats*>(items[i])) {
			auto item = dynamic_cast<ArmourStats*>(items[i]);
			std::cout << " (Def:" << item->getDef() << " )";
		}
		else if (dynamic_cast<SpellsStats*>(items[i])) {
			auto item = dynamic_cast<SpellsStats*>(items[i]);
			std::cout << " (Spell Power:" << item->getSpellPow() << " / Mana Cost:" << item->getManaCost() << " / Effect Duration:" << item->getEffectDuration() << ")";
		}
		//if (items[i]->isEquipped) {
		//	std::cout << " (equipped) ";
		//}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Inventory::getDebugInfo(std::string* basic_string)
{
	ImGui::Indent();
	for (int i = 0; i < items.size(); i++)
	{
		/*ImGui::Text("%d. %s", i + 1, items[i].name.c_str());
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
		}*/
		ImGui::Unindent();
	}
	ImGui::Unindent();
	
	Component::getDebugInfo(basic_string);
}

void Inventory::use_item(const std::string& item_name)
{
	for (auto& item : items)
	{
		if (item->name == item_name)
		{
			if (item->type == "Potion")
			{
				LOG_INFO("You used a " + item->name + " and recovered 20 HP.");
			}
			else
			{
				LOG_INFO("You used a " + item->name + ".");
			}

			return;
		}
	}
	
	LOG_ERROR("Item not found in inventory");
}

void Inventory::equip_item(const std::string& item_name)
{
	for (auto item : items)
	{
		if (item->name == item_name)
		{
			if (dynamic_cast<WeaponStats*>(item) != nullptr) // check if item is a weapon
			{
				WeaponStats* weapon = dynamic_cast<WeaponStats*>(item);
				weapon->weaponIsEquipped = true; // set isEquipped to true for the weapon
				std::cout << weapon->name << " equipped." << std::endl;
				break;
			}
			else if (dynamic_cast<ArmourStats*>(item) != nullptr) // check if item is an armor
			{
				ArmourStats* armor = dynamic_cast<ArmourStats*>(item);
				armor->armourIsEquipped = true; // set isEquipped to true for the armor
				std::cout << armor->name << " equipped." << std::endl;
				break;
			}
			else if (dynamic_cast<SpellsStats*>(item) != nullptr)
			{
				SpellsStats* spell = dynamic_cast<SpellsStats*>(item);
				spell->spellIsEquipped = true; // set isEquipped to true for the spell
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

void Inventory::unequip_item(const std::string& item_name)
{
	for (auto item : items)
	{
		if (item->name == item_name)
		{
			if (dynamic_cast<WeaponStats*>(item) != nullptr) // check if item is a weapon
			{
				WeaponStats* weapon = dynamic_cast<WeaponStats*>(item);
				if (weapon->weaponIsEquipped) {
					weapon->weaponIsEquipped = false; // set isEquipped to false for the weapon
					std::cout << weapon->name << " unequipped." << std::endl;
				}
				else {
					std::cout << weapon->name << " was not equipped." << std::endl;
				}
				break;
			}
			else if (dynamic_cast<ArmourStats*>(item) != nullptr) // check if item is an armor
			{
				ArmourStats* armor = dynamic_cast<ArmourStats*>(item);
				if (armor->armourIsEquipped) {
					armor->armourIsEquipped = false; // set isEquipped to false for the armor
					std::cout << armor->name << " unequipped." << std::endl;
				}
				else {
					std::cout << armor->name << " was not equipped." << std::endl;
				}
				break;
			}
			else if (dynamic_cast<SpellsStats*>(item) != nullptr)
			{
				SpellsStats* spell = dynamic_cast<SpellsStats*>(item);
				if (spell->spellIsEquipped) {
					spell->spellIsEquipped = false;
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



