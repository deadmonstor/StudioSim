#include "AttackAction.h"
#include "Core\Grid\GridSystem.h"
#include "..\EnemyComponent.h"
#include "../DestroyAfterAnimation.h"
#include "../TurnManager.h"
#include "../Flash.h"

AttackAction::AttackAction(GameObject* parentObjectArg)
	: parentObject(parentObjectArg)
{
	attackDirection = FindAttackDirection();
	currentPos = parentObject->getTransform()->getPosition();
}

void AttackAction::Act()
{
	GridSystem* gridSystem = GridSystem::Instance();
	glm::vec2 attackPosition = gridSystem->getTilePosition(currentPos) + attackDirection;
	createSlashGameObject(attackPosition);
	flashPlayer(PlayerController::Instance()->playerPTR, glm::vec3(1, 0, 0));
}

bool AttackAction::IsInRange()
{
	GridSystem* gridSystem = GridSystem::Instance();
	attackDirection = FindAttackDirection();
	glm::vec2 attackPosition = gridSystem->getTilePosition(currentPos) + attackDirection;
	TileHolder* tile = gridSystem->getTileHolder(0, attackPosition);
	if (tile != nullptr && tile->gameObjectSatOnTile != nullptr && tile->gameObjectSatOnTile->getName() == "Player")
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
	const TileHolder* tile = GridSystem::Instance()->getTileHolder(0, pos);

	if (tile != nullptr && tile->gameObjectSatOnTile->getName() == "Player")
	{
		GameObject* player = tile->gameObjectSatOnTile;
		PlayerStats* playerInfo = PlayerController::Instance()->playerStats;
		EnemyStats myStats = parentObject->getComponent<EnemyComponent>()->getStats();
		int attackDamage = myStats.attack - playerInfo->defence;

		//number betewen 0 and 1
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (r < myStats.critChance)
			attackDamage *= 2; //double damage!

		playerInfo->currentHealth -= attackDamage;
		PlayerController::Instance()->UpdateStats();
	}
	// get world position from grid position
	const glm::fvec2 worldPos = GridSystem::Instance()->getWorldPosition(pos);
	GameObject* slash = SceneManager::Instance()->createGameObject("Slash", worldPos);
	slash->getTransform()->setSize(glm::vec2(48, 48));

	AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
	slashSprite->setPivot(Pivot::Center);
	slash->addComponent<DestroyAfterAnimation>();
}
void AttackAction::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
		{
			TurnManager::Instance()->endTurn();
		});
}