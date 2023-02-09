#include "ShopRoomEntryTile.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core\Components\Transform.h"
#include <Util/Events/Events.h>
#include "..\GameEvents.h"

ShopRoomEntryTile::ShopRoomEntryTile(const Texture& _texture, std::string wallStringArg, glm::vec2 teleportPosArg, std::vector<glm::vec2> bossEntryPointsArg, std::vector<glm::vec2> bossPositionsArg)
{
	teleportPos = teleportPosArg;
	wallString = wallStringArg;
	bossEntryPoints = bossEntryPointsArg;
	bossPositions = bossPositionsArg;
}

bool ShopRoomEntryTile::canInteractWith()
{
	return false;
}

void ShopRoomEntryTile::onInteractedWith(TileHolder* curTileHolder)
{
}
