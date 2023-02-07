#include "PoisonSpell.h"
#include <Core/AudioEngine.h>
#include "../../EnemyComponent.h"
#include <Core/Components/Health.h>
#include "../../DestroyAfterAnimation.h"
#include "../../Player/PlayerController.h"

PoisonSpell::PoisonSpell()
{
	spellStats->maxCooldown = 5;
	spellStats->damagePerTurn = 5;
	spellStats->range = 4;
	spellStats->manaCost = 10;
	spellStats->price = 20;
	spellStats->currentCooldown = spellStats->maxCooldown;
}

void PoisonSpell::UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	AudioEngine::Instance()->playSound("Sounds\\PoisonSpell.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
	GameObject* spell = SceneManager::Instance()->createGameObject("PoisonSpell", GridSystem::Instance()->getWorldPosition(playerPos));
	spell->getTransform()->setSize(glm::vec2(48, 48));
	const std::vector textureListPosion = ResourceManager::GetTexturesContaining("Fireball");
	poisonSprite = spell->addComponent<AnimatedSpriteRenderer>(textureListPosion, 0.1f);
	poisonSprite->setColor(glm::vec3(0, 1, 1));
	poisonSprite->setSortingLayer(Renderer::getDefaultSortingLayer());
	poisonSprite->setPivot(Pivot::Center);
	spell->addComponent<DestroyAfterAnimation>();

	if (attackDir == glm::fvec2(0, 1))
	{
		spell->getTransform()->setRotation(90);
	}
	else if (attackDir == glm::fvec2(-1, 0))
	{
		spell->getTransform()->setRotation(180);
	}
	else if (attackDir == glm::fvec2(0, -1))
	{
		spell->getTransform()->setRotation(270);
	}

	glm::fvec2 targetPos = GridSystem::Instance()->getWorldPosition(playerPos + glm::fvec2(attackDir.x * spellStats->range, attackDir.y * spellStats->range));
	std::vector<TileHolder*> tilesAffected = PathfindingMachine::Instance()->LineIntersection(GridSystem::Instance()->getWorldPosition(playerPos), targetPos);

	for (TileHolder* tile : tilesAffected)
	{
		if (tile->gameObjectSatOnTile != nullptr && tile->gameObjectSatOnTile->hasComponent(typeid(EnemyComponent)))
		{
			targetPos = GridSystem::Instance()->getWorldPosition(tile->position);
			/*lerp = spell->addComponent<LerpPosition>(GridSystem::Instance()->getWorldPosition(tile->position), 3);*/
			break;
		}
		else if (tile->isWall)
		{
			targetPos = GridSystem::Instance()->getWorldPosition(tile->position);
			/*lerp = spell->addComponent<LerpPosition>(GridSystem::Instance()->getWorldPosition(tile->position), 3);*/
			break;
		}
	}

	lerp = spell->addComponent<LerpPosition>(targetPos, 3);
	lerp->onLerpComplete = [spell]
	{
		LOG_INFO("FireBallSpell -> LerpPosition -> TurnManager::Instance()->endTurn()");
		TurnManager::Instance()->endTurn();
		SceneManager::Instance()->destroyGameObject(spell);
	};

	TileHolder* lastTile = GridSystem::Instance()->getTileHolder(0, GridSystem::Instance()->getTilePosition(targetPos));
	if (lastTile != nullptr && lastTile->gameObjectSatOnTile != nullptr && lastTile->gameObjectSatOnTile->hasComponent(typeid(EnemyComponent)))
	{
		GameObject* enemy = lastTile->gameObjectSatOnTile;
		const glm::vec3 poisonColor = glm::vec3(0, 1, 1);
		enemy->getComponent<EnemyComponent>()->roundsPoisoned = turnsPoisoned;
		enemy->getComponent<AnimatedSpriteRenderer>()->setColor(poisonColor);
		
		PlayerController::Instance()->hitmarkers->addHitmarker(
			"POISON",
			1.0,
			enemy->getTransform()->getPosition(),
			poisonColor);

		/*EnemyStats targetStats = lastTile->gameObjectSatOnTile->getComponent<EnemyComponent>()->getStats();
		int spellDMG = spellStats->damagePerTurn - targetStats.defence;
		if (spellDMG < 0)
		{
			spellDMG = 0;
		}

		float r = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
		if (r < PlayerController::Instance()->playerStats->critChance)
		{
			spellDMG *= 2;
		}*/

		/*int newHealth = targetStats.currentHealth -= spellDMG;
		lastTile->gameObjectSatOnTile->getComponent<Health>()->setHealth(newHealth);*/
	}
}
