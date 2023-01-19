#include "PlayerController.h"

PlayerController::PlayerController()
{
}

void PlayerController::createPlayer()
{

	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 0,0 });
	playerPTR->getTransform()->setSize(glm::vec2{ 64,64 });

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
}
