#include "FireBallSpell.h"
#include "../../DestroyAfterAnimation.h"
#include "../../FireballComponent.h"

FireBallSpell::FireBallSpell()
{

	//fireBallStats->name = "Fire Ball";
	spellStats->cost = 10;
	spellStats->manaCost = 1;
	spellStats->damagePerTurn = 1;
	spellStats->maxCooldown = 1;
	spellStats->spellPower = 1;
	spellStats->currentCooldown = spellStats->maxCooldown;
	spellStats->range = 3;
}

void FireBallSpell::UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir)
{

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
	
	const auto lerpComponent = spell->addComponent<LerpPosition>(targetPos, 3);
	lerpComponent->onLerpComplete = [spell]
	{
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