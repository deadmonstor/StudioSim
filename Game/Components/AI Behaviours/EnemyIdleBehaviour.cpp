#include "EnemyIdleBehaviour.h"

#include "../Flash.h"
#include "../LerpPosition.h"
#include "../TurnManager.h"
#include "../Player/PlayerController.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
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
				{
					endTurn();
					return;
				}

				const TileHolder* front = tiles.front();
				GridSystem* gridSystem = GridSystem::Instance();

				if (gridSystem->getWorldPosition(front->position) == playerPos)
				{
					// ATTACK ME OUCH
					PlayerController::Instance()->playerStats->currentHealth -= 1;
					flashPlayer(PlayerController::Instance()->playerPTR, glm::vec3(1.0f, 0.0f, 0.0f));
					return;
				}

				const Transform* transform = parentFSM->getOwner()->getTransform();
				gridSystem->resetSatOnTile(0, gridSystem->getTilePosition(transform->getPosition()));
				lerpPosition(parentFSM->getOwner(), gridSystem->getWorldPosition(tiles.front()->position));
				gridSystem->setSatOnTile(0, tiles.front()->position, parentFSM->getOwner());
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

void EnemyIdleBehaviour::endTurn()
{
	TurnManager::Instance()->endTurn();
}

void EnemyIdleBehaviour::lerpPosition(GameObject* object, const glm::vec2 targetPosition)
{
	if (!object->hasComponent(typeid(LerpPosition)))
	{
		object->addComponent<LerpPosition>(targetPosition, 3);
	}

	LerpPosition* lerpPosition = object->getComponent<LerpPosition>();
	lerpPosition->onLerpComplete = [this]
	{
		endTurn();
	};
	lerpPosition->setSpeed(4);
	lerpPosition->setPosition(targetPosition);
}

void EnemyIdleBehaviour::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	if (!object->hasComponent(typeid(Flash)))
	{
		object->addComponent<Flash>(object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5);
	}

	auto* flash = object->getComponent<Flash>();

	flash->onFlashComplete = [this]
	{
		endTurn();
	};
	
	flash->setSpeed(5);
	flash->setColor(targetColor);
}
