#pragma once
#include "Core/Components/Camera.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class Inventory;
class PlayerFSM;
class PlayerController : public SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();
	void onKeyDown(const OnKeyDown* keyDown);
	void onKeyUp(const OnKeyUp* keyUp);

	SpriteComponent* playerSprite{};
	GameObject* playerPTR{};
	PlayerFSM* playerFSM{};
	Camera* cameraComponent{};
	Inventory* myInventory{};
};

