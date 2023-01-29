#include "MoveTowardsAction.h"

void MoveTowardsAction::Act()
{
	if (parentObject != nullptr)
	{
		currentPos = parentObject->getTransform()->getPosition();
		std::deque<TileHolder*> path = PathfindingMachine::Instance()->FindPath(currentPos, target);
		if (!path.empty())
		{
			GridSystem::Instance()->resetSatOnTile(0, parentObject->getTransform()->getPosition());
			parentObject->getTransform()->setPosition(path.front()->position * GridSystem::Instance()->getTileSize());
			//Set grid system "satOnTile" values

			GridSystem::Instance()->setSatOnTile(0, parentObject->getTransform()->getPosition(),parentObject);
		}
	}
	
}
