#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "../Components/Items/Weapons/CommonAxe.h"
#include "../Components/Items/Weapons/CommonDagger.h"
#include "../Components/Items/Weapons/CommonSword.h"
#include "../Components/Items/Weapons/RareAxe.h"
#include "../Components/Items/Weapons/RareSword.h"
#include "../Components/Items/Weapons/Hammer.h"
#include "../Components/Items/Weapons/RareAxe.h"
#include "../Components/Items/Weapons/LegendaryHammer.h"

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

