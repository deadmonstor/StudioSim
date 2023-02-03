#include "ChestTile.h"
#include "../LootTable.h"
#include <string>
#include <iostream>
#include "../Engine/Core/Grid/GridSystem.h"
#include <Core/Renderer/ResourceManager.h>



bool ChestTile::canInteractWith()
{
	if (!chestOpened)
		return true;
	else
		return false;
}

void ChestTile::onInteractedWith(TileHolder* curTileHolder)
{
	
	if (chestOpened)
	{
		//Add Chest Opening and dropping item from loot table and changing it to an open chest or removing the chest.
	}
	else if (!chestOpened)
	{
		std::string itemToSpawn = LootTable::Instance()->RollLoot();
		std::cout << itemToSpawn << std::endl;
		chestOpened = true;
		ChangeTexture(curTileHolder);
		//Pass in the item(s) name to be dropped
	}
	//else do nothing
}

void ChestTile::ChangeTexture(TileHolder* curTileHolder)
{
	curTileHolder->tile->setTexture(ResourceManager::GetTexture("chest_open_2"));
}