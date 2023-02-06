#pragma once
#include "TextComponent.h"
#include "Core/Components/UI/Panel.h"
#include "Util/SingletonTemplate.h"

class OnSceneChanged;

class InventoryHUD : public SingletonTemplate<InventoryHUD>
{
	bool hasLoaded = false;
	int sceneChangeID = -1;

	Panel* backgroundPanelInventory;
	Panel* backgroundPanelEquip;
	TextComponent* backgroundPanelInventoryText;
	
public:
	void createHUD();
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	[[nodiscard]] bool getHasLoaded() const { return hasLoaded; }
	bool shouldRender = false;
};
