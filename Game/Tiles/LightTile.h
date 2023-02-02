#pragma once
#include "Core/Grid/Tiles/Tile.h"

class LightTile : public Tile
{
public:
    explicit LightTile(const Texture& _texture)
        : Tile(_texture)
    {
        
    }

    void init(TileHolder* curTileHolder) override;
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
};
