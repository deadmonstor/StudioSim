#include "PlayerController.h"
#include "PlayerFSM.h"

PlayerController::PlayerController()
{
}

void PlayerController::createPlayer()
{
	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 3000, 3000 });
	playerPTR->getTransform()->setSize(glm::vec2{ 32,32 });

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
	playerSprite->setColor(glm::vec3(1, 1, 1));
	playerSprite->setLit(false);
	playerSprite->setPivot(Pivot::BottomCenter);

	playerFSM = playerPTR->addComponent<PlayerFSM>();
	cameraComponent = playerPTR->addComponent<Camera>();
	playerPTR->addComponent<Light>();
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
