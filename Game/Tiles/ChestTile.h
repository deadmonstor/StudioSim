#pragma once
#include "Core/Grid/Tiles/Tile.h"


class ChestTile : public Tile
{

public:
    explicit ChestTile(const Texture& _texture)
        : Tile(_texture)
    {

    }

    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
    double m_x, m_y;
private:
    bool chestOpened = false;
};


