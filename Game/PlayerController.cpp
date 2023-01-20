#include "PlayerController.h"
#include "PlayerFSM.h"
#include "Core/Grid/GridSystem.h"

PlayerController::PlayerController()
{
}

void PlayerController::createPlayer()
{

	glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 30, 20 } * tileSize);
	playerPTR->getTransform()->setSize(glm::vec2{ 32,32 });

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
	playerSprite->setColor(glm::vec3(1, 1, 1));
	playerSprite->setLit(false);
	playerSprite->setPivot(Pivot::TopRight);

	playerFSM = playerPTR->addComponent<PlayerFSM>();
	cameraComponent = playerPTR->addComponent<Camera>();
	Light* light = playerPTR->addComponent<Light>();
	light->setFalloff({0.75f, 0.75f, 10.0f});
	Renderer::Instance()->setCamera(cameraComponent);
}

void PlayerController::onKeyDown(const OnKeyDown* keyDown)
{
	//find the input and send it to the state machine
	std::type_index eventType = typeid(OnKeyDown);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyDown(keyDown->key, keyDown->scancode), eventType);
	
}

void PlayerController::onKeyUp(const OnKeyUp* keyUp)
{
	std::type_index eventType = typeid(OnKeyUp);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyUp(keyUp->key, keyUp->scancode), eventType);
}
