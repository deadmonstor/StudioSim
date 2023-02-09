#include "SwordShopItemTile.h"
#include "../Components/Player/PlayerController.h"

bool SwordShopItemTile::canInteractWith()
{
	return true;
}

void SwordShopItemTile::onInteractedWith(TileHolder* curTileHolder)
{
    RareSword* sword = new RareSword();

    // Access the shop and purchase the RareSword
    std::vector<Item*> items = { sword };
    std::string currency = "Gold";
    Inventory& playerInventory = *PlayerController::Instance()->myInventory;
    Shop shop(items, currency, playerInventory);
    //shop.purchase(sword, PlayerController::Instance()->playerStats->coinsHeld);
    shop.purchase(sword, *PlayerController::Instance()->playerStats);
}
