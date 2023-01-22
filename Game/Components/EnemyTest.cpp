#include "EnemyTest.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Health.h"
#include "Core/Renderer/ResourceManager.h"

void EnemyTest::start()
{
	getOwner()->addComponent<Health>();
	
	const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
	auto sprite = getOwner()->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(false);
	sprite->setPivot(Pivot::Center);
	
	Component::start();
}
