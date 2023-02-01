#include "EnemyCombatBehaviour.h"
#include "MoveTowardsAction.h"
#include "Core\Grid\PathfindingMachine.h"
#include "..\PlayerController.h"
#include "Core\Components\Transform.h"
#include "Core\Components\AI\StateMachine.h"

EnemyCombatBehaviour::EnemyCombatBehaviour()
{
	isInFSM = false;
	parentFSM = nullptr;
}

EnemyCombatBehaviour::EnemyCombatBehaviour(StateMachine* parentFSMArg)
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
	glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
	glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
	glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	TileHolder* targetTile = nullptr;
	int depth = 0;
	while (targetTile == nullptr)
	{
		//int startDepth = (depth - 1 < 0) ? 0 : depth - 1;
		TileHolder* closestEmptyTile = PathfindingMachine::Instance()->FindClosestEmptyTile(myPos, playerPos, depth, 0);
		if (closestEmptyTile != nullptr)
			targetTile = closestEmptyTile;
		depth++;
	}
	((MoveTowardsAction*)availableActions["MoveTowards"].second)->SetTarget(targetTile->position * tileSize);
}

void EnemyCombatBehaviour::GenerateBehaviourList()
{
	//Create and initialize move towards behaviour
	availableActions["MoveTowards"] = std::make_pair(0, new MoveTowardsAction(parentFSM->getOwner()));
	if (!availableActions["MoveTowards"].second->GetInitValue())
	{
		availableActions["MoveTowards"].second->start();
	}
}

void EnemyCombatBehaviour::GenerateEffects()
{
}
