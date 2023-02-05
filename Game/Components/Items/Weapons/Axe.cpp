#include "Axe.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "../../DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"

Axe::Axe()
{
}

void Axe::Attack(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	std::vector<glm::fvec2> attackPosAxe = { (playerPos + attackDir),
					(playerPos + attackDir + attackDir) };

	attackPositions.assign(attackPosAxe.begin(), attackPosAxe.end());
	for (glm::fvec2 attackPos : attackPositions)
	{
		const bool isWallTile = GridSystem::Instance()->isWallTile(attackPos);
		TileHolder* attackTile = GridSystem::Instance()->getTileHolder(0, attackPos);
		if (!isWallTile && attackTile->isSpawned)
		{
			createSlashGameObject(attackPos);
		}
	}
	attackPositions.clear();
}

void Axe::createSlashGameObject(glm::fvec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;

	if (gameObject != nullptr)
	{
		if (gameObject->hasComponent(typeid(Health)))
		{


			//auto* enemyInfo = gameObject->getComponent<EnemyComponent>();
			//health->setHealth(health->getHealth() - 50);
			//int newHealth = enemyInfo->getStats().currentHealth - atk;
			//gameObject->getComponent<Health>()->setHealth(newHealth);

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
