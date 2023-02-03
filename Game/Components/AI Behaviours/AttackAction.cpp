#include "AttackAction.h"
#include "Core\Grid\GridSystem.h"

AttackAction::AttackAction(GameObject* parentObjectArg)
	: parentObject(parentObjectArg)
{
	attackDirection = FindAttackDirection();
	currentPos = parentObject->getTransform()->getPosition();
}

void AttackAction::Act()
{
}

bool AttackAction::IsInRange()
{
	GridSystem* gridSystem = GridSystem::Instance();
	attackDirection = FindAttackDirection();
	glm::vec2 attackPosition = gridSystem->getTilePosition(currentPos + attackDirection);
	if (gridSystem->getTileHolder(0, attackPosition)->gameObjectSatOnTile->getName() == "Player")
		return true;
	else
		return false;
}

glm::vec2 AttackAction::FindAttackDirection()
{
	currentPos = currentPos = parentObject->getTransform()->getPosition();
	glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
	glm::vec2 directionVec = playerPos - currentPos;

	//Horizontal
	if (abs(directionVec.x) > abs(directionVec.y))
	{
		//left
		if (directionVec.x < 0)
			return glm::vec2(-1, 0);
		//right
		else
			return glm::vec2(1, 0);
	}
	//Vertical
	else {
		//down
		if (directionVec.y < 0)
			return glm::vec2(0, -1);
		//up
		else
			return glm::vec2(0, 1);
	}
}
