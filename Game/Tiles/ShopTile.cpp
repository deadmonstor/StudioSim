#include "ShopTile.h"
#include "../Game/Components/Player/PlayerController.h"
#include "Core/Grid/GridSystem.h"

bool ShopTile::canInteractWith()
{
    return true;
}

void ShopTile::onInteractedWith(TileHolder* curTileHolder)
{
    int currentCoins = PlayerController::Instance()->playerStats->coinsHeld;
    int currentPrice = m_item->getPrice();
    std::cout << " Price: " << currentPrice << "\n";
    if (currentCoins >= currentPrice)
    {
        PlayerController::Instance()->playerStats->coinsHeld -= currentPrice;
        PlayerController::Instance()->myInventory->add_item(m_item);
        ChangeTexture(curTileHolder);
    }
    else
    {
        std::cout << "You are poor\n";
    }
}

void ShopTile::ChangeTexture(TileHolder* curTileHolder)
{
    Texture m_ItemTexture;
    curTileHolder->tile->setTexture(ResourceManager::GetTexture("tile26"));
    const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(curTileHolder->position);
}
