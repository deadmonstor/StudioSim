#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include <Util/Events/Events.h>
#include "..\GameEvents.h"
class TeleportTile : public Tile
{
public:
    explicit TeleportTile(const Texture& _texture, double x, double y)
        : Tile(_texture)
    {
        m_x = x;
        m_y = y;
    }

    void init(TileHolder* curTileHolder) override;
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
private:
    double m_x, m_y;
    bool Teleportable = false;
    void ChangeTeleport(EnterBossRoomEvent* event);
};

