#include "FireBallSpell.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"

void FireBallSpell::UseSpellAt(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	
}

void FireBallSpell::CreateSpell(glm::fvec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;


	const glm::fvec2 worldPos = GridSystem::Instance()->getWorldPosition(pos);
	GameObject* spell = SceneManager::Instance()->createGameObject("Spell", worldPos);
	spell->getTransform()->setSize(glm::vec2(48, 48));
	AnimatedSpriteRenderer* spellSprite = spell->addComponent<AnimatedSpriteRenderer>(FireBallTexture, 0.05f);
	spellSprite->setPivot(Pivot::Center);
	spell->addComponent<DestroyAfterAnimation>();
}