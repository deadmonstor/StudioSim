#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "..\Components\Player\PlayerController.h"

class BossRoomEntryTile : public Tile
{
public:
	explicit BossRoomEntryTile(const Texture& _texture, std::string wallStringArg, glm::vec2 teleportPosArg, std::vector<glm::vec2> bossEntryPointsArg, std::vector<glm::vec2> bossPositionsArg);
	bool canInteractWith() override;
	void onInteractedWith(TileHolder* curTileHolder) override;
private:
	glm::vec2 teleportPos;
	std::string wallString;
	std::vector<glm::vec2> bossEntryPoints;
	std::vector<glm::vec2> bossPositions;
};

