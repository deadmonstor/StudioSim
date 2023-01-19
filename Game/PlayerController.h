#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/EngineEvents.h"

class PlayerController : SingletonTemplate<PlayerController>
{
public:
	PlayerController();

	void createPlayer();

private:
	SpriteComponent* playerSprite;
	GameObject* playerPTR;
	
};

