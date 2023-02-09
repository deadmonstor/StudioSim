#pragma once
#include "Core/Grid/Tiles/Tile.h"
#include "../Components/Items/Armour/CommonArmour.h"
#include "../Components/Items/Armour/RareArmour.h"
#include "../Components/Items/Armour/LegendaryArmour.h"

class ArmourShopItemTile : public Tile
{
public:
    explicit ArmourShopItemTile(const Texture& _texture)
        : Tile(_texture)
    {

    }
    bool canInteractWith() override;
    void onInteractedWith(TileHolder* curTileHolder) override;
private:

};

