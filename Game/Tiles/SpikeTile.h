#pragma once
#include "Core/Grid/Tiles/Tile.h"
class SpikeTile : public Tile
{
public:
    explicit SpikeTile(const Texture& _texture)
        : Tile(_texture) {}

    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
};

