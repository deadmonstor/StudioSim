#include "BossAttackAction.h"
#include "Core\Grid\GridSystem.h"
#include "../../EnemyComponent.h"
#include "../../TurnManager.h"
#include "../../Flash.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "../../DestroyAfterAnimation.h"

BossAttackAction::BossAttackAction(glm::vec2 myPosArg, GameObject* parentObjectArg)
	: currentPos(myPosArg), parentObject(parentObjectArg)
{
}

void BossAttackAction::Act()
{

	//Find attack positions
	std::vector<glm::vec2> attackPositions = FindAttackPositions();
	
	//do attacks
	for (auto pos : attackPositions) 
	{
		createSlashGameObject(pos);
	}

	TurnManager::Instance()->endTurn();
}


std::vector<glm::vec2> BossAttackAction::FindAttackPositions()
{
	glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
	playerPos = GridSystem::Instance()->getTilePosition(playerPos);
	glm::vec2 directionVec = playerPos - currentPos;
	std::vector<glm::vec2> outputPositions = std::vector<glm::vec2>();

	//Horizontal
	if (abs(directionVec.x) > abs(directionVec.y))
	{
		//left
		if (directionVec.x < 0)
		{
			for (int xPos = -4; xPos <= -1; xPos++)
				for (int yPos = 1; yPos >= -1; yPos--)
				{
					glm::vec2 pos = currentPos + glm::vec2(xPos, yPos);
					outputPositions.push_back(pos);
				}
		}
			
		//right
		else
		{
			for (int xPos = 2; xPos <= 5; xPos++)
				for (int yPos = 1; yPos >= -1; yPos--)
				{
					glm::vec2 pos = currentPos + glm::vec2(xPos, yPos);
					outputPositions.push_back(pos);
				}
		}
			
	}
	//Vertical
	else {
		//down
		if (directionVec.y < 0)
		{
			for (int xPos = -1; xPos <= 2; xPos++)
				for (int yPos = -1; yPos >= -3; yPos--)
				{
					glm::vec2 pos = currentPos + glm::vec2(xPos, yPos);
					outputPositions.push_back(pos);
				}
		}
			
		//up
		else
		{
			for(int xPos = -1; xPos <=2; xPos++)
				for (int yPos = 3; yPos >= 1; yPos--)
				{
					glm::vec2 pos = currentPos + glm::vec2(xPos, yPos);
					outputPositions.push_back(pos);
				}
		}
			
	}
	return outputPositions;
}

void BossAttackAction::createSlashGameObject(glm::vec2 pos)
{
	const TileHolder* tile = GridSystem::Instance()->getTileHolder(0, pos);

	if (tile != nullptr && tile->gameObjectSatOnTile == PlayerController::Instance()->playerPTR)
	{
		PlayerStats* targetStats = PlayerController::Instance()->playerStats;
		const EnemyStats myStats = parentObject->getComponent<EnemyComponent>()->getStats();

		int attackDamage = myStats.attack - targetStats->defence;
		if (attackDamage < 0)
			attackDamage = 0;

		//number betewen 0 and 1
		const float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (r < myStats.critChance)
			attackDamage *= 2; //double damage!

		PlayerController::Instance()->hitmarkers->addHitmarker(
			"-" + std::to_string(attackDamage),
			1.0,
			PlayerController::Instance()->playerPTR->getTransform()->getPosition(),
			{ 1, 1, 1 });

		targetStats->currentHealth -= attackDamage;
		flashPlayer(PlayerController::Instance()->playerPTR, glm::vec3(1, 0, 0));
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

void BossAttackAction::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
		{
		});
}
