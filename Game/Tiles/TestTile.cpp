#include "TestTile.h"
#include "Core/Grid/GridSystem.h"

bool TestTile::canInteractWith()
{
    return true;
}

void TestTile::onInteractedWith(TileHolder* curTileHolder)
{
    // change scene
    SceneManager::Instance()->changeScene(m_SceneToChangeTo);
}
