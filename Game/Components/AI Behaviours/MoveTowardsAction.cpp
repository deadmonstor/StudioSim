#include "MoveTowardsAction.h"

#include "../TurnManager.h"
#include "Core/Components/Transform.h"

MoveTowardsAction::MoveTowardsAction()
	: target(glm::vec2())
	, currentPos(glm::vec2())
	, parentObject(nullptr)
{
}

MoveTowardsAction::MoveTowardsAction(GameObject* parentObjectArg)
	: target(glm::vec2())
	, currentPos(glm::vec2())
	, parentObject(parentObjectArg)
{
}

void MoveTowardsAction::Act()
{
	if (parentObject != nullptr)
	{
		currentPos = parentObject->getTransform()->getPosition();
		const std::deque<TileHolder*> path = PathfindingMachine::Instance()->FindPath(currentPos, target);
		if (!path.empty())
		{
			const glm::vec2 tile = GridSystem::Instance()->getTilePosition(parentObject->getTransform()->getPosition());

			GridSystem::Instance()->resetSatOnTile(0, tile);
			parentObject->getTransform()->setPosition(path.front()->position * GridSystem::Instance()->getTileSize());
			GridSystem::Instance()->setSatOnTile(0, tile, parentObject);
		}

		TurnManager::Instance()->endTurn();
	}
	
}
