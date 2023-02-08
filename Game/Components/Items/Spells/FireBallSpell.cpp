#include "FireBallSpell.h"
#include "../../DestroyAfterAnimation.h"
#include "../../FireballComponent.h"
#include "../../EnemyComponent.h"
#include "../../Player/PlayerController.h"
#include "Core/AudioEngine.h"
#include <Core/Components/Health.h>

FireBallSpell::FireBallSpell()
{

	//fireBallStats->name = "Fire Ball";
	spellStats->price = 10;
	spellStats->manaCost = 1;
	spellStats->maxCooldown = 1;
	spellStats->spellPower = 20;
	spellStats->currentCooldown = spellStats->maxCooldown;
	spellStats->range = 6;
}

void FireBallSpell::UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	AudioEngine::Instance()->playSound("Sounds\\FireBall.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
	GameObject* spell = SceneManager::Instance()->createGameObject("FireballSpell", GridSystem::Instance()->getWorldPosition(playerPos));
	spell->getTransform()->setSize(glm::vec2(48, 48));
	const std::vector textureListFireball = ResourceManager::GetTexturesContaining("Fireball");
	fireBallSprite = spell->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0.1f);
	fireBallSprite->setColor(glm::vec3(1, 1, 1));
	fireBallSprite->setSortingLayer(Renderer::getDefaultSortingLayer());
	fireBallSprite->setPivot(Pivot::Center);
	spell->addComponent<Light>();
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
			targetPos = GridSystem::Instance()->getWorldPosition(tile->position) ;
			/*lerp = spell->addComponent<LerpPosition>(GridSystem::Instance()->getWorldPosition(tile->position), 3);*/
			break;
		}
	}


	
	bool shouldHitmarker = false;
	TileHolder* lastTile = GridSystem::Instance()->getTileHolder(0, GridSystem::Instance()->getTilePosition(targetPos));
	if (lastTile != nullptr && lastTile->gameObjectSatOnTile != nullptr && lastTile->gameObjectSatOnTile->hasComponent(typeid(EnemyComponent)))
	{
		shouldHitmarker = true;
		
	}
	
	lerp = spell->addComponent<LerpPosition>(targetPos, 3);
	lerp->onLerpComplete = [lastTile, spell, this, shouldHitmarker]
	{
		LOG_INFO("FireBallSpell -> LerpPosition -> TurnManager::Instance()->endTurn()");
		if (shouldHitmarker)
		{
			EnemyStats targetStats = lastTile->gameObjectSatOnTile->getComponent<EnemyComponent>()->getStats();
			int spellDMG = spellStats->spellPower;
			float currentHealth = lastTile->gameObjectSatOnTile->getComponent<Health>()->getHealth();
			int newHealth = currentHealth -= spellDMG;
			lastTile->gameObjectSatOnTile->getComponent<Health>()->setHealth(newHealth);
			if (lastTile->gameObjectSatOnTile->isBeingDeleted())
			{
				GridSystem::Instance()->resetSatOnTile(0, GridSystem::Instance()->getTilePosition(lastTile->gameObjectSatOnTile->getTransform()->getPosition()));
			}
		}
		
		TurnManager::Instance()->endTurn();
		SceneManager::Instance()->destroyGameObject(spell);
	};
	
	//if (spell->getTransform()->getPosition() == (playerPos + glm::fvec2(attackDir.x * range, attackDir.y * range)))
	//{
	//	SceneManager::Instance()->destroyGameObject(spell);
	//}
}

//void FireBallSpell::CreateSpell(glm::fvec2 pos)
//{
//	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
//	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;
//
//	GameObject* spell = SceneManager::Instance()->createGameObject("Fireball", pos);
//	spell->getTransform()->setSize(glm::vec2(48, 48));
//	/*AnimatedSpriteRenderer* spellSprite = spell->addComponent<AnimatedSpriteRenderer>(FireBallTexture, 0.05f);*/
//	/*spellSprite->setPivot(Pivot::Center);*/
//	spell->addComponent<DestroyAfterAnimation>();
//	spell->addComponent<FireballComponent>();
//
//}