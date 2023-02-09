#include "ShopRoomEntryTile.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core\Components\Transform.h"
#include <Util/Events/Events.h>
#include "..\GameEvents.h"


ShopRoomEntryTile::ShopRoomEntryTile(const Texture& _texture, std::string wallStringArg, glm::vec2 teleportPosArg, std::vector<glm::vec2> shopEntryPointsArg, std::vector<glm::vec2> shopPositionsArg) : Tile(_texture)
{
	teleportPos - teleportPosArg;
	wallString = wallStringArg;
	shopEntryPoints = shopEntryPointsArg;
}

bool ShopRoomEntryTile::canInteractWith()
{
	return true;
}

void ShopRoomEntryTile::onInteractedWith(TileHolder* curTileHolder)
{
	for (auto tilePos : shopEntryPoints)
	{
		TileHolder* tileHolder = GridSystem::Instance()->getTileHolder(0, tilePos);
		tileHolder->tile->setTexture(ResourceManager::GetTexture(wallString));
		tileHolder->isWall = true;
		GridSystem::Instance()->resetSatOnTile(0, tileHolder->position);
	}
	glm::vec2 teleportWorldPos = GridSystem::Instance()->getWorldPosition(teleportPos);
	PlayerController::Instance()->playerPTR->getTransform()->setPosition(teleportWorldPos);
	GridSystem::Instance()->setSatOnTile(0, teleportPos, PlayerController::Instance()->playerPTR);

	//Griddy::Events::invoke<EnterShopRoomEvent>(teleportPos);
}
