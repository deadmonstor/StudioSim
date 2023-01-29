#include "EnemyIdleBehaviour.h"
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
		glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
		glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
		
		float distance = PathfindingMachine::Instance()->FindDiagonalDistance(myPos, playerPos);
		if (distance < 600)
		{
			if (PathfindingMachine::Instance()->LineOfSight(myPos, playerPos))
			{
				//Enemy can sense player here. engage combat.
				std::deque<TileHolder*> tiles = PathfindingMachine::Instance()->FindPath(myPos, playerPos);
				
				if (tiles.empty())
					return;

				const TileHolder* front = tiles.front();
				GridSystem* gridSystem = GridSystem::Instance();

				if (gridSystem->getWorldPosition(front->position) == playerPos)
					return;

				const Transform* transform = parentFSM->getOwner()->getTransform();
				gridSystem->resetSatOnTile(0, gridSystem->getTilePosition(transform->getPosition()));
				parentFSM->getOwner()->getTransform()->setPosition(gridSystem->getWorldPosition(tiles.front()->position));
				gridSystem->setSatOnTile(0, gridSystem->getTilePosition(transform->getPosition()), parentFSM->getOwner());
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
