#include "EnemyComponent.h"

#include "TurnManager.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Health.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core/Grid/GridSystem.h"
#include "Util/Events/Events.h"
#include "Items/Stats.h"
#include "../Components/Player/PlayerController.h"


EnemyComponent::EnemyComponent()
{
	enemyFSM = nullptr;
	stats = EnemyStats();
	spriteName = "";
}

EnemyComponent::EnemyComponent(StateMachine* stateMachineArg, EnemyStats statsArg, std::string spriteNameArg)
{
	enemyFSM = stateMachineArg;
	stats = statsArg;
	spriteName = spriteNameArg;
}

void EnemyComponent::start()
{
	getOwner()->addComponent<Health>();
	getOwner()->addComponent<Camera>();
	const std::vector textureList = ResourceManager::GetTexturesContaining(spriteName);
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
	
	int expGained = 5;
	PlayerController::Instance()->playerStats->currentEXP += expGained;
	PlayerController::Instance()->UpdateStats();

	Component::destroy();
}

void EnemyComponent::onTurnChanged(const onStartTurn* event)
{
	if (event->objectToStart == getOwner())
	{
		enemyFSM->Act();
	}
}
