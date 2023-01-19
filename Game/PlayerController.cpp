#include "PlayerController.h"
#include "PlayerFSM.h"

PlayerController::PlayerController()
{
}

void PlayerController::createPlayer()
{
	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 600,600 });
	playerPTR->getTransform()->setSize(glm::vec2{ 32,32 });

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
	playerSprite->setColor(glm::vec3(1, 1, 1));
	playerSprite->setLit(false);

	playerFSM = playerPTR->addComponent<PlayerFSM>();
	cameraComponent = playerPTR->addComponent<Camera>();
	Renderer::Instance()->setCamera(cameraComponent);
}

void PlayerController::onKeyDown(const OnKeyDown* keyDown)
{
	//find the input and send it to the state machine
	std::type_index eventType = typeid(OnKeyDown);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, keyDown, eventType);
}

void PlayerController::onKeyUp(const OnKeyUp* keyUp)
{
	std::type_index eventType = typeid(OnKeyUp);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, keyUp, eventType);
}
