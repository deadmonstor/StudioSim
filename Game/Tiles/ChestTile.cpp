#include "ChestTile.h"

bool ChestTile::canInteractWith()
{
	return true;
}

void ChestTile::onInteractedWith(TileHolder* curTileHolder)
{
	
	if (chestOpened)
	{
		//Add Chest Opening and dropping item from loot table and changing it to an open chest or removing the chest.
	}
	//else do nothing
}