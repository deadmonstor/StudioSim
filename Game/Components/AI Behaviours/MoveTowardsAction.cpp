#include "MoveTowardsAction.h"

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
			GridSystem::Instance()->resetSatOnTile(0, parentObject->getTransform()->getPosition());
			parentObject->getTransform()->setPosition(path.front()->position * GridSystem::Instance()->getTileSize());
			//Set grid system "satOnTile" values

			GridSystem::Instance()->setSatOnTile(0, parentObject->getTransform()->getPosition(),parentObject);
		}
	}
	
}
