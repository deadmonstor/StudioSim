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
	GridSystem* gridSystem = GridSystem::Instance();
	glm::vec2 attackPosition = gridSystem->getTilePosition(currentPos + attackDirection);
	createSlashGameObject(attackPosition);
}

bool AttackAction::IsInRange()
{
	GridSystem* gridSystem = GridSystem::Instance();
	attackDirection = FindAttackDirection();
	glm::vec2 attackPosition = gridSystem->getTilePosition(currentPos + attackDirection);
	TileHolder* tile = gridSystem->getTileHolder(0, attackPosition);
	if (tile != nullptr && tile->gameObjectSatOnTile->getName() == "Player")
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

void AttackAction::createSlashGameObject(glm::vec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;

	if (gameObject != nullptr)
	{
		if (gameObject->hasComponent(typeid(PlayerStats)))
		{


			PlayerStats playerInfo = 
			//health->setHealth(health->getHealth() - 50);
			int newHealth = enemyInfo->getStats().currentHealth - atk; //or something like this, use the defence and crit values too.
			gameObject->getComponent<Health>()->setHealth(newHealth);

			// TODO: This is probably shitty 
			if (gameObject->isBeingDeleted())
				GridSystem::Instance()->resetSatOnTile(0, pos);
		}
	}

	// get world position from grid position
	const glm::fvec2 worldPos = GridSystem::Instance()->getWorldPosition(pos);
	GameObject* slash = SceneManager::Instance()->createGameObject("Slash", worldPos);
	slash->getTransform()->setSize(glm::vec2(48, 48));
	AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
	slashSprite->setPivot(Pivot::Center);
	slash->addComponent<DestroyAfterAnimation>();
}
