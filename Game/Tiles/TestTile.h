#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include <string>
#include <Util/Events/Events.h>
#include "..\GameEvents.h"

class TestTile : public Tile
{
public:
    explicit TestTile(const Texture& _texture, std::string SceneToChangeTo, bool FromTutorial)
        : Tile(_texture)
    {
        Teleportable = FromTutorial;
        m_SceneToChangeTo = SceneToChangeTo;
    }

    void init(TileHolder* curTileHolder) override;
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;

    

private:
    std::string m_SceneToChangeTo;
    bool Teleportable = false;
    void ChangeTeleport(BossDeathEvent* event);

};
