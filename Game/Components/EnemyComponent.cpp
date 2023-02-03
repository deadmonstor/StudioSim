#include "EnemyComponent.h"

#include "TurnManager.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Health.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core/Grid/GridSystem.h"
#include "Util/Events/Events.h"
#include "..\Components\Items\Stats.h"

void EnemyComponent::start()
{
	getOwner()->addComponent<Health>();
	getOwner()->addComponent<Camera>();
	enemyFSM = getOwner()->addComponent<NormalEnemyFSM>();
	
	const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
	auto sprite = getOwner()->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(true);
	sprite->setPivot(Pivot::Center);

	TurnManager::Instance()->addToTurnQueue(getOwner());

	if (onStartTurnID == -1)
		Griddy::Events::subscribe(this, &EnemyComponent::onTurnChanged);
	
	Component::start();
}

void EnemyComponent::destroy()
{
	if (onStartTurnID != -1)
		Griddy::Events::unsubscribe(this, &EnemyComponent::onTurnChanged, onStartTurnID);
	
	Component::destroy();
}

void EnemyComponent::onTurnChanged(const onStartTurn* event)
{
	if (event->objectToStart == getOwner())
	{
		enemyFSM->Act();
	}
}
