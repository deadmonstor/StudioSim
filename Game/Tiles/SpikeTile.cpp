#include "SpikeTile.h"
#include "../Components/Player/PlayerController.h"

bool SpikeTile::canInteractWith()
{
	return true;
}

void SpikeTile::onInteractedWith(TileHolder* curTileHolder)
{
	int damageDealt = 2;
	PlayerController::Instance()->playerStats->currentHealth -= damageDealt;
	PlayerController::Instance()->UpdateStats();
}
