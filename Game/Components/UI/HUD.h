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
	
public:
	void createHUD();
	void updateHUD();
	int getRandomNumber();
};
