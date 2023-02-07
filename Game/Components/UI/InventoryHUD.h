#pragma once
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "Core/Components/UI/Panel.h"
#include "Util/SingletonTemplate.h"
#include "../../System/Inventory.h"

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
	ButtonComponent* createButton(const glm::vec2& pos, Item* item);
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	[[nodiscard]] bool getHasLoaded() const { return hasLoaded; }
	bool shouldRender = false;
};
