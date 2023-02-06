#include "EnemyIdleBehaviour.h"

#include "EnemyCombatBehaviour.h"
#include "../TurnManager.h"
#include "../Player/PlayerController.h"
#include "../DelayTask.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Core/Components/AI/StateMachine.h"
#include "Core/Grid/PathfindingMachine.h"
#include "AttackAction.h"

EnemyIdleBehaviour::EnemyIdleBehaviour(StateMachine* parentFSMArg)
{
	isInFSM = true;
	parentFSM = parentFSMArg;
}

void EnemyIdleBehaviour::Act()
{
	bool shouldEndTurn = true;
	
	if (parentFSM != nullptr)
	{
		const glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
		const glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();

		if (const float distance = PathfindingMachine::Instance()->EstimateDistance(myPos, playerPos); distance < 600)
		{
			if (PathfindingMachine::Instance()->LineOfSight(myPos, playerPos))
			{
				shouldEndTurn = false;
				//Enemy can sense player here. engage combat.
				Griddy::Events::invoke<StateTransition>(parentFSM, new EnemyCombatBehaviour(parentFSM));
				TurnManager::Instance()->endTurn();
				LOG_INFO("Enemy Idle Behaviour -> Act -> TurnManager::Instance()->endTurn()");
			}
		}
	}

	if (shouldEndTurn)
	{
		TurnManager::Instance()->endTurn();
		LOG_INFO("Enemy Idle Behaviour -> DelayTask::createTask -> TurnManager::Instance()->endTurn()");
	}
}
