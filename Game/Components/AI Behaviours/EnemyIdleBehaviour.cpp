#include "EnemyIdleBehaviour.h"
#include "Core\Grid\PathfindingMachine.h"
#include "Core\GameObject.h"
#include "Core\Components\Transform.h"
#include "..\PlayerController.h"

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
		glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
		glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
		
		float distance = PathfindingMachine::Instance()->FindDiagonalDistance(myPos, playerPos);
		if (distance < 600)
		{
			if (PathfindingMachine::Instance()->LineOfSight(myPos, playerPos))
			{
				return;
				//Enemy can sense player here. engage combat.
			}
		}
	}
	else 
	{
		glm::vec2 myPos = this->getOwner()->getTransform()->getPosition();
		glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();

		float distance = PathfindingMachine::Instance()->FindDiagonalDistance(myPos, playerPos);
		if (distance < 600)
		{
			if (PathfindingMachine::Instance()->LineOfSight(myPos, playerPos))
			{
				return;
				//Enemy can sense player here. engage combat.
			}
		}
	}
	
}
