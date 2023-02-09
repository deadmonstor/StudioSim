#pragma once
#include "ButtonComponent.h"
#include "InventoryIconButton.h"
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
	TextComponent* currentInventoryText;
	TextComponent* currentInventoryTextOnline;
	std::vector<InventoryIconButton*> slots;

	InventoryIconButton* weaponSlot;
	InventoryIconButton* armourSlot;
	InventoryIconButton* spellSlot;
	
public:
	void createHUD();
	InventoryIconButton* createButton(const glm::vec2& pos, Item* item);
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	[[nodiscard]] bool getHasLoaded() const { return hasLoaded; }
	bool shouldRender = false;
};
