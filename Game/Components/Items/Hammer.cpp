#include "Hammer.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "../DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"

void Hammer::Attack(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	glm::fvec2 firstTileinAttackDir = (playerPos + attackDir);
	glm::fvec2 secondTileinAttackDir = (playerPos + attackDir + attackDir);
	if (attackDir == glm::fvec2{ 0,1 } || attackDir == glm::fvec2{ 0,-1 })
	{
		std::vector<glm::fvec2> attackPosHammer = { firstTileinAttackDir, firstTileinAttackDir + glm::fvec2(1, 0),
		firstTileinAttackDir + glm::fvec2(-1, 0), secondTileinAttackDir, secondTileinAttackDir + glm::fvec2(1, 0),
		secondTileinAttackDir + glm::fvec2(-1, 0) };

		attackPositions.assign(attackPosHammer.begin(), attackPosHammer.end());

		for (glm::fvec2 attackPos : attackPositions)
		{
			const bool isWallTile = GridSystem::Instance()->isWallTile(attackPos);
			TileHolder* attackTile = GridSystem::Instance()->getTileHolder(0, attackPos);
			if (!isWallTile && attackTile->isSpawned)
			{
				createSlashGameObject(attackPos);
			}
		}
	}
	else
	{
		std::vector<glm::fvec2> attackPosHammer = { firstTileinAttackDir, firstTileinAttackDir + glm::fvec2(0, 1),
		firstTileinAttackDir + glm::fvec2(0, -1), secondTileinAttackDir, secondTileinAttackDir + glm::fvec2(0, 1),
		secondTileinAttackDir + glm::fvec2(0, -1) };

		attackPositions.assign(attackPosHammer.begin(), attackPosHammer.end());

		for (glm::fvec2 attackPos : attackPositions)
		{
			const bool isWallTile = GridSystem::Instance()->isWallTile(attackPos);
			TileHolder* attackTile = GridSystem::Instance()->getTileHolder(0, attackPos);
			if (!isWallTile && attackTile->isSpawned)
			{
				createSlashGameObject(attackPos);
			}
		}
	}
}

void Hammer::createSlashGameObject(glm::fvec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;

	if (gameObject != nullptr)
	{
		if (gameObject->hasComponent(typeid(Health)))
		{


			auto* health = gameObject->getComponent<Health>();
			health->setHealth(health->getHealth() - 50);

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
