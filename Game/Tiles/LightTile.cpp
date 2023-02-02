#include "LightTile.h"
#include "Core/Grid/GridSystem.h"

void LightTile::init(TileHolder* curTileHolder)
{
    const auto light = SceneManager::Instance()->createGameObject("light", GridSystem::Instance()->getWorldPosition(curTileHolder->position));
    light->addComponent<Light>();
    light->getComponent<Light>()->setFalloff({2, 6, 40});
    
    Tile::init(curTileHolder);
}

bool LightTile::canInteractWith()
{
    return false;
}

void LightTile::onInteractedWith(TileHolder* curTileHolder)
{

}
