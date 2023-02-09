#pragma once
#include "ButtonComponent.h"
#include "Core/Renderer/ResourceManager.h"
#include "../../System/Inventory.h"
class Item;

class InventoryIconButton final : public ButtonComponent
{
	Item* item;
	
public:
	InventoryIconButton(const Texture& _texture, Item* _item);
	void onClick() override;
	void render() override;
	void setItem(Item* _item)
	{
		if (item == _item)
			return;
		
		item = _item;
		if (item == nullptr)
		{
			SetTexture(ResourceManager::GetTexture("whitetexture"));
			return;
		}

		std::string itemToSpawn = item->name();
		std::ranges::transform(itemToSpawn, itemToSpawn.begin(),
		                       [](unsigned char c){ return std::tolower(c); });
		
		if (itemToSpawn.contains("axe"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Axe"));
		}
		else if (itemToSpawn.contains("sword"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Sword"));
		}
		else if (itemToSpawn.contains("dagger"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Dagger"));
		}
		else if (itemToSpawn.contains("hammer"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Hammer"));
		}
		else if (itemToSpawn.contains("common") && itemToSpawn.contains("armour"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-BasicArmourChest"));
		}
		else if (itemToSpawn.contains("rare") && itemToSpawn.contains("armour"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-MidArmourChest"));
		}
		else if (itemToSpawn.contains("legendary") && itemToSpawn.contains("armour"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-TopArmourChest"));
		}
		else if (itemToSpawn.contains("health"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Potion0"));
		}
		else if (itemToSpawn.contains("mana"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Potion1"));
		}
		else if (itemToSpawn.contains("exp"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-Potion2"));
		}
		else if (itemToSpawn.contains("ice") && itemToSpawn.contains("spell"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-IceSpell"));
		}
		else if (itemToSpawn.contains("poison") && itemToSpawn.contains("spell"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-PoisonSpell"));
		}
		else if (itemToSpawn.contains("fire") && itemToSpawn.contains("spell"))
		{
			SetTexture(ResourceManager::GetTexture("Inventory-FireSpell"));
		}
		else
		{
			SetTexture(ResourceManager::GetTexture("whitetexture"));
			LOG_ERROR(itemToSpawn);
		}
	}
};
