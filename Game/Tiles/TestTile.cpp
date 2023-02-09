#include "TestTile.h"
#include "Core/Grid/GridSystem.h"

void TestTile::init(TileHolder* curTileHolder)
{
    Griddy::Events::subscribe(this, &TestTile::ChangeTeleport);
}

bool TestTile::canInteractWith()
{
    return true;
}

void TestTile::onInteractedWith(TileHolder* curTileHolder)
{
    // change scene
    if (Teleportable)
    {
        SceneManager::Instance()->changeScene(m_SceneToChangeTo);
    }
}

void TestTile::ChangeTeleport(BossDeathEvent* event)
{
    Teleportable = true;
}
