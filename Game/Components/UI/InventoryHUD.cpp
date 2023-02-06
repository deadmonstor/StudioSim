#include "InventoryHUD.h"

#include "Util/Events/Events.h"

void InventoryHUD::createHUD()
{
	if (hasLoaded)
		return;

	if (sceneChangeID == -1)
		sceneChangeID = Griddy::Events::subscribe(this, &InventoryHUD::onSceneChange);
}

void InventoryHUD::updateHUD()
{
	if (!hasLoaded)
		return;

	
}

void InventoryHUD::onSceneChange(OnSceneChanged* event)
{
	hasLoaded = false;
}
