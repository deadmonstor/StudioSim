#pragma once
#include "Core/Grid/Tiles/Tile.h"

class TestTile : public Tile
{
public:
    explicit TestTile(const Texture& _texture)
        : Tile(_texture)
    {
    }

    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
};
