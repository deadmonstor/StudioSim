#pragma once
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "PauseButton.h"
#include "MasterAudioPlusButton.h"
#include "MasterAudioMinusButton.h"
#include "MasterAudioMuteButton.h"
#include "InventoryButton.h"
#include "Util/SingletonTemplate.h"

class OnPlayerControllerFSMUpdate;

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

	ButtonComponent* weaponButton;

	//Buttons
	PauseButton* pauseButton;
	InventoryButton* inventoryButton;
	MasterAudioPlusButton* plusAudioButton;
	MasterAudioMinusButton* minusAudioButton;
	MasterAudioMuteButton* muteAudioButton;

	Panel* healthIcon;
	Panel* manaIcon;
	Panel* coinsIcon;

	bool hasLoaded = false;

	int sceneChangeID = -1;
	int playerChangedID = -1;
	

public:
	void createHUD();
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);
	void onPlayerChanged(const OnPlayerControllerFSMUpdate* event);

	bool getHasLoaded() const { return hasLoaded; }
};
