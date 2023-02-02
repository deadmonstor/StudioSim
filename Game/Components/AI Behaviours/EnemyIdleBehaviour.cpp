#include "EnemyIdleBehaviour.h"

#include "EnemyCombatBehaviour.h"
#include "../TurnManager.h"
#include "../Player/PlayerController.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Core/Components/AI/StateMachine.h"
#include "Core/Grid/PathfindingMachine.h"

EnemyIdleBehaviour::EnemyIdleBehaviour()
{
	isInFSM = false;
	parentFSM = nullptr;
}

EnemyIdleBehaviour::EnemyIdleBehaviour(StateMachine* parentFSMArg)
{
	isInFSM = true;
	parentFSM = parentFSMArg;
}

void EnemyIdleBehaviour::Act()
{
	if (parentFSM != nullptr)
	{
		const glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
		const glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();

		if (const float distance = PathfindingMachine::Instance()->EstimateDistance(myPos, playerPos); distance < 600)
		{
			if (PathfindingMachine::Instance()->LineOfSight(myPos, playerPos))
			{
				//Enemy can sense player here. engage combat.
				Griddy::Events::invoke<StateTransition>(parentFSM, new EnemyCombatBehaviour(parentFSM));
			}
		}
	}

	TurnManager::Instance()->endTurn();
}
