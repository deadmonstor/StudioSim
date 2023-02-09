#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "../System/Inventory.h"
#include "Core/Renderer/ResourceManager.h"

class Item;

class ShopTile : public Tile
{
    Item* m_item;
	bool hasBeenBought = false;
	TileHolder* curTileHolder;

	int engineRenderID = -1;
    void onEngineRender(OnEngineRender*);
public:
    explicit ShopTile(const Texture& _texture, Item* item)
        : Tile(_texture) 
    {
        m_item = item;
		std::string itemToSpawn = m_item->name();
		std::ranges::transform(itemToSpawn, itemToSpawn.begin(),
			[](unsigned char c) { return std::tolower(c); });

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

	void init(TileHolder* curTileHolder) override;
	void destroy() override;
	
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
	void ChangeTexture(const TileHolder* curTileHolder);
};