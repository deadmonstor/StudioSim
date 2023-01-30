#pragma once
#include "Core/Grid/Tiles/Tile.h"
class TeleportTile : public Tile
{
public:
    explicit TeleportTile(const Texture& _texture, double x, double y)
        : Tile(_texture)
    {
        m_x = x;
        m_y = y;
    }

    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
    double m_x, m_y;
};

