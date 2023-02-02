#pragma once
#include "../Items/Stats.h"
#include "Core/Components/Camera.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "../Items/Dagger.h"
#include "../Items/Axe.h"
#include "../Items/Hammer.h"
#include "../Items/Sword.h"

class Inventory;
class PlayerFSM;
class PlayerController : public SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();
	void onKeyDown(const OnKeyDown* keyDown);
	void onKeyHold(const OnKeyRepeat* keyHold);
	void onKeyUp(const OnKeyUp* keyUp);

	void UpdateStats();

	Dagger* daggerClass;
	Axe* axeClass;
	Hammer* hammerClass;
	Sword* swordClass;
	SpriteComponent* playerSprite{};
	GameObject* playerPTR{};
	PlayerFSM* playerFSM{};
	Camera* cameraComponent{};
	Inventory* myInventory{};
	PlayerStats* playerStats{};
};
