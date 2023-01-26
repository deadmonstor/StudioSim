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
	sprite->setLit(true);
	sprite->setPivot(Pivot::Center);

	Light* light = getOwner()->addComponent<Light>();
	light->setFalloff({2.75f, 2.75f, 55.0f});
	light->setColor({1.0f, 1.0f, 1.0f, 0.25f});
	
	Component::start();
}
