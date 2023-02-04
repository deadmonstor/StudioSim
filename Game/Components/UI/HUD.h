#pragma once
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "PauseButton.h"
#include "MasterAudioPlusButton.h"
#include "MasterAudioMinusButton.h"
#include "InventoryButton.h"
#include "Util/SingletonTemplate.h"

class HUD : public SingletonTemplate<HUD>
{
private:
	TextComponent* coinText;
	TextComponent* manaText;
	TextComponent* xpText;
	TextComponent* coinsText;
	TextComponent* healthText;
	TextComponent* levelText;
	TextComponent* audioText;

	//ButtonComponent* inventoryButton;
	ButtonComponent* weaponButton;
	ButtonComponent* spellsButton;
	//ButtonComponent* plusAudioButton;
	//ButtonComponent* minusAudioButton;

	//Buttons
	PauseButton* pauseButton;
	InventoryButton* inventoryButton;
	MasterAudioPlusButton* plusAudioButton;
	MasterAudioMinusButton* minusAudioButton;

	Panel* healthIcon;
	Panel* manaIcon;
	Panel* coinsIcon;

	bool hasLoaded = false;

	int sceneChangeID = -1;
	
public:
	void createHUD();
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	bool getHasLoaded() const { return hasLoaded; }
};
