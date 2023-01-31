#include "MoveTowardsAction.h"

void MoveTowardsAction::Act()
{
	if (parentObject != nullptr)
	{
		currentPos = parentObject->getTransform()->getPosition();
		std::deque<TileHolder*> path = PathfindingMachine::Instance()->FindPath(currentPos, target);
		if (!path.empty())
		{
			glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
			GridSystem::Instance()->resetSatOnTile(0, parentObject->getTransform()->getPosition()/tileSize);
			parentObject->getTransform()->setPosition(path.front()->position * tileSize);
			//Set grid system "satOnTile" values

			GridSystem::Instance()->setSatOnTile(0, parentObject->getTransform()->getPosition()/tileSize,parentObject);
		}
	}
	
}
