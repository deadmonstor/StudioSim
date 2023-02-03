#include "Inventory.h"
#include <iostream>
#include "../Components/Items/ArmourItem.h"
#include "../Components/Items/Weapon.h"
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
	LOG_INFO("You added a " + item->name());
	return true;
}

bool Inventory::remove_item(Item* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		// TODO: Check if item is the same as the one in the inventory
		// This could fail and remove two of the same item but with different stats?
		// Probably a good idea to do some hash code lookup here
		
		if (items[i]->name() == item->name())
		{
			items.erase(items.begin() + i);
			LOG_INFO("You have removed a " + item->name());
			return true;
		}
	}
	
	LOG_INFO("Item not found in inventory.");
	return false;
}

<<<<<<< HEAD
void Inventory::draw_inventory() {
	//std::cout << "Inventory:\n";
	//for (int i = 0; i < items.size(); i++)
	//{
	//	std::cout << i + 1 << ". " << items[i]->name;
	//	if (dynamic_cast<WeaponStats*>(items[i])) {
	//		auto item = dynamic_cast<WeaponStats*>(items[i]);
	//		std::cout << " (Atk:" << item->attack;
	//	}
	//	else if (dynamic_cast<ArmourStats*>(items[i])) {
	//		auto item = dynamic_cast<ArmourStats*>(items[i]);
	//		std::cout << " (Def:" << item->getDef() << " )";
	//	}
	//	else if (dynamic_cast<SpellsStats*>(items[i])) {
	//		auto item = dynamic_cast<SpellsStats*>(items[i]);
	//		std::cout << " (Spell Attack:" << item->getSpellDamage() << " / Mana Cost:" << item->getManaCost() <</* " / Effect Duration:" << item->getEffectDuration() << */")";
	//	}
	//	//if (items[i]->isEquipped) {
	//	//	std::cout << " (equipped) ";
	//	//}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

//void Inventory::draw_inventory()
//{
//	std::cout << "Inventory:\n";
//	for (int i = 0; i < items.size(); i++)
//	{
//		std::cout << i + 1 << ". " << items[i]->name();
//		
//		switch(items[i]->getItemType())
//		{
//			case ItemType::WEAPON:
//			{
//				const auto item = dynamic_cast<WeaponItem*>(items[i]);
//				std::cout << " (Atk:" << item->getAtk() << " / Crit:" << item->getCrit() << ")";
//				break;
//			}
//			case ItemType::SPELL:
//			{
//				const auto item = dynamic_cast<SpellItem*>(items[i]);
//				std::cout << " (Spell Power:" << item->getSpellAtk() << " / Mana Cost:" << item->getManaCost() << " / Effect Duration:" << item->getEffectDuration() << ")";
//				break;
//			}
//			case ItemType::ARMOUR:
//			{
//				const auto item = dynamic_cast<ArmourItem*>(items[i]);
//				std::cout << " (Def:" << item->armour->defence << " )";
//				break;
//			}
//			case ItemType::CONSUMABLE:
//			case ItemType::NOTSET:
//			{
//				break;
//			}
//		}
//		
//		if (items[i]->isEquipped)
//		{
//			std::cout << " (equipped) ";
//		}
//		
//		std::cout << std::endl;
//	}
//	
//	std::cout << std::endl;
//
//}

//void Inventory::getDebugInfo(std::string* basic_string)
//{
//	ImGui::Indent();
//	for (int i = 0; i < items.size(); i++)
//	{
//		ImGui::PushID(i);
//		
//		ImGui::Text("%d. %s", i + 1, items[i]->name().c_str());
//		ImGui::Indent();
//		
//		if (items[i]->getItemType() == ItemType::WEAPON)
//		{
//			const auto item = dynamic_cast<WeaponItem*>(items[i]);
//			ImGui::Text("Atk: %d / Crit: %d", item->atk, item->crit);
//		}
//		else if (items[i]->getItemType() == ItemType::ARMOUR)
//		{
//			const auto item = dynamic_cast<ArmourItem*>(items[i]);
//			ImGui::Text("Def: %d", item->armour->defence);
//		}
//		else if (items[i]->getItemType() == ItemType::SPELL)
//		{
//			const auto item = dynamic_cast<SpellItem*>(items[i]);
//			ImGui::Text("Spell Power: %d / Mana Cost: %d / Effect Duration: %d", item->spellAtk, item->manaCost, item->effectDuration);
//		}
//		
//		if (items[i]->isEquipped)
//		{
//			ImGui::Text("Equipped");
//			
//			if (ImGui::Button("Un-equip"))
//			{
//				unequip_item(items[i]->name());
//			}
//		}
//		else if (items[i]->isEquipable())
//		{
//			if (ImGui::Button("Equip"))
//				equip_item(items[i]->name());
//		}
//
//		if (items[i]->isUsable())
//		{
//			if (ImGui::Button("Use Item"))
//			{
//				use_item(items[i]->name());
//			}
//		}
//		
//		ImGui::PopID();
//		
//		ImGui::Unindent();
//	}
//	
//	ImGui::Unindent();
//	
//	Component::getDebugInfo(basic_string);
//}

void Inventory::use_item(const std::string& item_name)
{
	for (const auto& item : items)
	{
		if (item->name() == item_name)
		{
			if (item->isUsable())
			{
				item->use();
				remove_item(item);
			}
			else
			{
				LOG_ERROR(item_name + " is not usable.");
			}
			
			return;
		}
	}
	
	LOG_ERROR("Item not found in inventory");
}

void Inventory::equip_item(const std::string& item_name)
{
	for (const auto item : items)
	{
		if (item->name() == item_name)
		{
			if (item->getEquipSlot() != EquipSlot::NOTSET)
			{
				if (Item* equippedItem = getFirstItemWithEquipSlot(item->getEquipSlot()); equippedItem != nullptr)
					unequip_item(equippedItem->name());
			}
			
			item->isEquipped = true;

			if (!item->isEquipable())
			{
				LOG_INFO(item->name() + " is not equippable.");
				break;
			}
			
			switch(item->getItemType())
			{
				case ItemType::WEAPON:
				case ItemType::SPELL:
				case ItemType::ARMOUR:
				case ItemType::CONSUMABLE:
				{
					LOG_INFO(item->name() + " equipped.");
					break;
				}
				case ItemType::NOTSET:
				{
					std::cout << item_name << " is not equippable." << std::endl;
					break;
				}
			}

			break;
		}
	}
}

void Inventory::unequip_item(const std::string& item_name)
{
	for (const auto item : items)
	{
		if (item->name() == item_name)
		{
			if (!item->isEquipped)
			{
				LOG_INFO(item->name() + " is not equipped");
				break;
			}
			
			switch(item->getItemType())
			{
				case ItemType::WEAPON:
				case ItemType::SPELL:
				case ItemType::ARMOUR:
				case ItemType::CONSUMABLE:
				{
					item->isEquipped = false;
					LOG_INFO(item->name() + " unequipped");
					break;
				}
				case ItemType::NOTSET:
				{
					LOG_INFO(item->name() + " is not unequipable.");
					break;
				}
			}

			break;
		}
	}
}

Item* Inventory::getFirstItemWithEquipSlot(const EquipSlot slot)
{
	for (const auto item : items)
	{
		if (item->isEquipped && item->getEquipSlot() == slot)
		{
			return item;
		}
	}
	
	return nullptr;
}



