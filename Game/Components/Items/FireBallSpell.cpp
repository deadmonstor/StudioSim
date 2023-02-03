#include "FireBallSpell.h"
#include "../DestroyAfterAnimation.h"
#include "../FireballComponent.h"

FireBallSpell::FireBallSpell()
{
	fireBallStats = new SpellsStats();
	//fireBallStats->name = "Fire Ball";
	fireBallStats->price = 10;
	fireBallStats->manaCost = 2;
	fireBallStats->damagePerTurn = 1;
	fireBallStats->cooldown = 1;
	fireBallStats->spellPower = 1;
	fireBallStats->spellCooldown = 1;
	fireBallStats->range = 5;
	
}

void FireBallSpell::UseSpellAt(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	
}

void FireBallSpell::CreateSpell(glm::fvec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;

	const glm::fvec2 worldPos = GridSystem::Instance()->getWorldPosition(pos);
	GameObject* spell = SceneManager::Instance()->createGameObject("Fireball", worldPos);
	spell->getTransform()->setSize(glm::vec2(48, 48));
	/*AnimatedSpriteRenderer* spellSprite = spell->addComponent<AnimatedSpriteRenderer>(FireBallTexture, 0.05f);*/
	/*spellSprite->setPivot(Pivot::Center);*/
	spell->addComponent<DestroyAfterAnimation>();
	spell->addComponent<FireballComponent>();

}