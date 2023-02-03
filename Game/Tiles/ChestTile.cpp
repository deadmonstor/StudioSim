#include "ChestTile.h"
#include "../LootTable.h"
#include <string>


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
		//Pass in the item(s) name to be dropped
	}
	//else do nothing
}