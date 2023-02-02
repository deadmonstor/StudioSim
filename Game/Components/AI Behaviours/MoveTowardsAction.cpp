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
			GridSystem* instance = GridSystem::Instance();
			instance->resetSatOnTile(0,  instance->getTilePosition(parentObject->getTransform()->getPosition()));
			parentObject->getTransform()->setPosition(instance->getWorldPosition(path.front()->position));
			instance->setSatOnTile(0, instance->getTilePosition(parentObject->getTransform()->getPosition()), parentObject);
		}
	}

	TurnManager::Instance()->endTurn();
}
