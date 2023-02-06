#include "Dagger.h"
#include <Core/Components/Health.h>
#include "../../DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "../../EnemyComponent.h"

Dagger::Dagger()
{
}

void Dagger::Attack(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	const bool isWallTile = GridSystem::Instance()->isWallTile(playerPos + attackDir);
	
	if (!isWallTile)
	{
		createSlashGameObject(playerPos + attackDir);

	}
}

void Dagger::createSlashGameObject(glm::fvec2 pos)
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
