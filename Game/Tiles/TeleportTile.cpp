#include "TeleportTile.h"

#include "../Game/Components/Player/PlayerController.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"

void TeleportTile::init(TileHolder* curTileHolder)
{
	Griddy::Events::subscribe(this, &TeleportTile::ChangeTeleport);
}

bool TeleportTile::canInteractWith()
{
    return true;
}

void TeleportTile::onInteractedWith(TileHolder* curTileHolder)
{
	if (Teleportable)
	{
		glm::fvec2 test;
		test.x = m_x * GridSystem::Instance()->getTileSize().x;
		test.y = m_y * GridSystem::Instance()->getTileSize().y;
		PlayerController::Instance()->playerPTR->getTransform()->setPosition(test);
	}
}

void TeleportTile::ChangeTeleport(BossDeathEvent* event)
{
	Teleportable = true;
}
