#pragma once
#include "TextComponent.h"
#include "Util/SingletonTemplate.h"

class HUD : public SingletonTemplate<HUD>
{
private:
	TextComponent* coinText;
	TextComponent* manaText;
	TextComponent* xpText;
	TextComponent* coinsText;
	TextComponent* healthText;

	Panel* coinsIcon;
	bool hasLoaded = false;

	int sceneChangeID = -1;
	
public:
	void createHUD();
	void updateHUD();
	void onSceneChange(OnSceneChanged* event);

	bool getHasLoaded() const { return hasLoaded; }
};
