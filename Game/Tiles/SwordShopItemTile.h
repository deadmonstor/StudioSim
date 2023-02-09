#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "../Components/Items/Weapons/RareSword.h"

class SwordShopItemTile : public Tile
{
public:
    explicit SwordShopItemTile(const Texture& _texture)
        : Tile(_texture)
    {

    }
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
private:

};

