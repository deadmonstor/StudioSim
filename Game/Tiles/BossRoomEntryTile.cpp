#include "BossRoomEntryTile.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core\Components\Transform.h"
#include <Util/Events/Events.h>
#include "..\GameEvents.h"

BossRoomEntryTile::BossRoomEntryTile(const Texture& _texture, std::string wallStringArg, glm::vec2 teleportPosArg, std::vector<glm::vec2> bossEntryPointsArg) : Tile(_texture)
{
	teleportPos = teleportPosArg;
	wallString = wallStringArg;
	bossEntryPoints = bossEntryPointsArg;
}

bool BossRoomEntryTile::canInteractWith()
{
	return true;
}

void BossRoomEntryTile::onInteractedWith(TileHolder* curTileHolder)
{
	for (auto tilePos : bossEntryPoints)
	{
		TileHolder* tileHolder = GridSystem::Instance()->getTileHolder(0, tilePos);
		tileHolder->tile->setTexture(ResourceManager::GetTexture(wallString));
		tileHolder->isWall = true;
		GridSystem::Instance()->resetSatOnTile(0, tileHolder->position);
	}
	glm::vec2 teleportWorldPos = GridSystem::Instance()->getWorldPosition(teleportPos);
	PlayerController::Instance()->playerPTR->getTransform()->setPosition(teleportWorldPos);
	GridSystem::Instance()->setSatOnTile(0, teleportPos, PlayerController::Instance()->playerPTR);
	
	Griddy::Events::invoke<EnterBossRoomEvent>();
}
