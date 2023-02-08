#include "ShopTile.h"
#include "../Game/Components/Player/PlayerController.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "Util/Events/Events.h"

void ShopTile::init(TileHolder* _curTileHolder)
{
    Tile::init(curTileHolder);
    
    curTileHolder = _curTileHolder;
    engineRenderID = Griddy::Events::subscribe(this, &ShopTile::onEngineRender);
}

void ShopTile::destroy()
{ 
    Griddy::Events::unsubscribe(this, &ShopTile::onEngineRender, engineRenderID);
}

void ShopTile::onEngineRender(OnEngineRender*)
{
    if (hasBeenBought || m_item == nullptr) return;
    const int currentPrice = m_item->getPrice();
    
    if (currentPrice == 0) return; // INVALID cannot buy
    
    const auto worldPosition = GridSystem::Instance()->getWorldPosition(curTileHolder->position) - glm::vec2{0, GridSystem::Instance()->getTileSize().y};
    constexpr auto scale = 0.35f;
    const auto color = glm::vec3{1, 1, 1};
    
    const glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(currentPrice) + " Gold", scale);
    TextRenderer::Instance()->renderText(std::to_string(currentPrice) + " Gold",
        worldPosition.x - Renderer::Instance()->getCameraPosScreenSpace().x - sizeOfText.x / 2,
        worldPosition.y - Renderer::Instance()->getCameraPosScreenSpace().y - sizeOfText.y / 2,
        scale,
        color,
        glm::vec2{0.5f, 0.5f}
    );
}

bool ShopTile::canInteractWith()
{
    return true;
}

void ShopTile::onInteractedWith(TileHolder* curTileHolder)
{
    if (hasBeenBought) return;
    
    const int currentCoins = PlayerController::Instance()->playerStats->coinsHeld;
    const int currentPrice = m_item->getPrice();
    
    if (currentPrice == 0) return; // INVALID cannot buy
    const PlayerController* playerController = PlayerController::Instance();
    
    if (currentCoins >= currentPrice)
    {
        playerController->playerStats->coinsHeld -= currentPrice;
        playerController->myInventory->add_item(m_item);
        ChangeTexture(curTileHolder);
        hasBeenBought = true;
    }
    else
    {
        playerController->hitmarkers->addHitmarker(
        		"NOT ENOUGH COINS",
        		1.0,
        		playerController->playerPTR->getTransform()->getPosition(),
        		glm::vec3{1, 0, 0});
    }
}

void ShopTile::ChangeTexture(const TileHolder* curTileHolder)
{
    curTileHolder->tile->setTexture(ResourceManager::GetTexture("tile204"));
}
