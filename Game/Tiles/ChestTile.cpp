#include "ChestTile.h"
#include "../LootTable.h"


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
	else
	{

	}
	//else do nothing
}