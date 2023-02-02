#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include <string>

class TestTile : public Tile
{
public:
    explicit TestTile(const Texture& _texture, std::string SceneToChangeTo)
        : Tile(_texture)
    {
        m_SceneToChangeTo = SceneToChangeTo;
    }

    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;

private:
    std::string m_SceneToChangeTo;
};
