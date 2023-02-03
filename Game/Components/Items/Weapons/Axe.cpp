#include "Axe.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "../../DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"
#include "../../EnemyComponent.h"

Axe::Axe()
{
	axeStats = new WeaponStats();
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
		if (gameObject->hasComponent(typeid(EnemyComponent)))
		{
			auto* enemyInfo = gameObject->getComponent<EnemyComponent>();
			int atkDamage = stats->attack - enemyInfo->getStats().defence;
			if (atkDamage < 0)
			{
				atkDamage = 0;
			}

			//number between 0 and 1
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (r < stats->crit)
			{
				atkDamage *= 2; //double damage
			}

			int newHealth = enemyInfo->getStats().currentHealth - atkDamage;
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
