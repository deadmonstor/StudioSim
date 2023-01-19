#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/EngineEvents.h"
#include "Core/Components/Camera.h"
#include "Core/GameObject.h"

class PlayerFSM;
class PlayerController : public SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();
	void onKeyDown(const OnKeyDown* keyDown);
	void onKeyUp(const OnKeyUp* keyUp);

	SpriteComponent* playerSprite;
	GameObject* playerPTR;
	PlayerFSM* playerFSM;
	Camera* cameraComponent;
	
};

