#pragma once
#include "../Items/Stats.h"
#include "Core/Components/Camera.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "../../System/Inventory.h"


class OnPlayerControllerFSMUpdate : public Griddy::Event
{
public:
	OnPlayerControllerFSMUpdate(const std::string key) : key(key) {}
	std::string key;
};

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

	SpriteComponent* playerSprite{};
	GameObject* playerPTR{};
	PlayerFSM* playerFSM{};
	Camera* cameraComponent{};
	Inventory* myInventory{};
	PlayerStats* playerStats{};
	ArmourStats* armourStats{};
};
