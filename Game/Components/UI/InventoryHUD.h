#pragma once
#include "Util/SingletonTemplate.h"

class OnSceneChanged;

class InventoryHUD : public SingletonTemplate<InventoryHUD>
{
	bool hasLoaded = false;
	int sceneChangeID = -1;
	
public:
	void createHUD();
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	[[nodiscard]] bool getHasLoaded() const { return hasLoaded; }
};
