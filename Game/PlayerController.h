#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/EngineEvents.h"
#include "PlayerFSM.h"
#include "Core/Components/Camera.h"

class PlayerController : public SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();
	void onKeyDown(const OnKeyDown* keyDown);
	//onKeyUp

private:
	SpriteComponent* playerSprite;
	GameObject* playerPTR;
	PlayerFSM* playerFSM;
	Camera* cameraComponent;
	
};

