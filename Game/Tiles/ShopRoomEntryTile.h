#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "..\Components\Player\PlayerController.h"
class ShopRoomEntryTile : public Tile
{
public:
    explicit ShopRoomEntryTile(const Texture& _texture, std::string wallStringArg, glm::vec2 teleportPosArg, std::vector<glm::vec2> shopEntryPointsArg, std::vector<glm::vec2> shopPositionsArg);
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;

private:
    glm::vec2 teleportPos;
    std::string wallString;
    std::vector<glm::vec2> shopEntryPoints;
    std::vector<glm::vec2> shopPositions;
};

