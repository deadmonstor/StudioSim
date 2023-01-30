#include "TeleportTile.h"

#include "Core/Grid/GridSystem.h"
#include "../Game/Components/PlayerController.h"
#include "Core/Components/Transform.h"

bool TeleportTile::canInteractWith()
{
    return true;
}

void TeleportTile::onInteractedWith(TileHolder* curTileHolder)
{
	glm::fvec2 test;
	test.x = m_x*48;
	test.y = m_y*48;
	PlayerController::Instance()->playerPTR->getTransform()->setPosition(test);
}