#include "EnemyCombatBehaviour.h"

#include "MoveTowardsAction.h"
#include "../DelayTask.h"
#include "../Player/PlayerController.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/PathfindingMachine.h"
#include "../TurnManager.h"
#include "../Flash.h"
#include "../Core/Components/AnimatedSpriteRenderer.h"

EnemyCombatBehaviour::EnemyCombatBehaviour()
	: PlannedBehaviour()
{
	isInFSM = false;
	parentFSM = nullptr;
}

EnemyCombatBehaviour::EnemyCombatBehaviour(StateMachine* parentFSMArg)
	: PlannedBehaviour()
{
	parentFSM = parentFSMArg;
	isInFSM = true;
}

void EnemyCombatBehaviour::WorldAnalysis()
{
	
}

void EnemyCombatBehaviour::ActionAnalysis()
{
	PlannedBehaviour::ActionAnalysis();

	//Set the closest available tile to the player as the target for the move towards action
	const glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
	const glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
	const glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	const TileHolder* targetTile = nullptr;
	int depth = 0;
	while (targetTile == nullptr)
	{
		//int startDepth = (depth - 1 < 0) ? 0 : depth - 1;
		const TileHolder* closestEmptyTile = PathfindingMachine::Instance()->FindClosestEmptyTile(myPos, playerPos, depth, 0);
		
		if (closestEmptyTile != nullptr)
			targetTile = closestEmptyTile;
		
		depth++;
	}
	
	static_cast<MoveTowardsAction*>(availableActions["MoveTowards"].second)->SetTarget(targetTile->position * tileSize);
}

void EnemyCombatBehaviour::GenerateBehaviourList()
{
	//Create and initialize move towards behaviour
	availableActions["MoveTowards"] = std::make_pair(0, new MoveTowardsAction(parentFSM->getOwner()));
	if (!availableActions["MoveTowards"].second->GetInitValue())
	{
		availableActions["MoveTowards"].second->start();
	}

	DelayTask::createTask(parentFSM->getOwner(), 1.0f, [this]()
	{
		TurnManager::Instance()->endTurn();
	});
}

void EnemyCombatBehaviour::GenerateEffects()
{
}

void EnemyCombatBehaviour::endTurn()
{
	TurnManager::Instance()->endTurn();
}

void EnemyCombatBehaviour::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
	{
		endTurn();
	});
}