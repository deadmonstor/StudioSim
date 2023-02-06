#include "MoveTowardsAction.h"

#include "../TurnManager.h"
#include "Core/Components/Transform.h"
#include "../Flash.h"
#include "../DelayTask.h"
#include "../LerpPosition.h"

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
	bool shouldLerp = false;
	
	if (parentObject != nullptr)
	{
		currentPos = parentObject->getTransform()->getPosition();
		
		PathfindingData data = PathfindingData();
		PathfindingMachine::Instance()->FindPath(data, currentPos, target);

		if (const std::deque<TileHolder*> path = data.tiles; !path.empty())
		{
			shouldLerp = true;
			
			GridSystem* instance = GridSystem::Instance();
			instance->resetSatOnTile(0,  instance->getTilePosition(parentObject->getTransform()->getPosition()));
			lerpPosition(parentObject, instance->getWorldPosition(path.front()->position));
			instance->setSatOnTile(0, path.front()->position, parentObject);
		}
	}


	if (!shouldLerp)
	{
		DelayTask::createTask(parentObject, 1.0f, [this]()
		{
			TurnManager::Instance()->endTurn();
			LOG_INFO("!shouldLerp -> DelayTask::createTask() -> TurnManager::Instance()->endTurn()");
		});
	}
}

void MoveTowardsAction::endTurn()
{
	TurnManager::Instance()->endTurn();
	LOG_INFO("MoveTowardsAction::endTurn() -> TurnManager::Instance()->endTurn()");
}

void MoveTowardsAction::lerpPosition(GameObject* object, const glm::vec2 targetPosition)
{
	if (!object->hasComponent(typeid(LerpPosition)))
	{
		object->addComponent<LerpPosition>(targetPosition, 3);
	}

	const auto lerpPosition = object->getComponent<LerpPosition>();
	lerpPosition->onLerpComplete = [this]
	{
		DelayTask::createTask(parentObject, 1.0f, [this]()
		{
			endTurn();
		});
	};
	lerpPosition->setSpeed(3);
	lerpPosition->setPosition(targetPosition);
}