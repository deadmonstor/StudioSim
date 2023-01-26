#pragma once
#include "Core/Components/Camera.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class PlayerFSM;
class PlayerController : public SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();
	void onKeyDown(const OnKeyDown* keyDown);
	void onKeyHold(const OnKeyRepeat* keyHold);
	void onKeyUp(const OnKeyUp* keyUp);

	SpriteComponent* playerSprite{};
	GameObject* playerPTR{};
	PlayerFSM* playerFSM{};
	Camera* cameraComponent{};
	
};

