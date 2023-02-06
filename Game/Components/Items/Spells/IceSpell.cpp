#include "IceSpell.h"
#include "../../EnemyComponent.h"
#include "../../DestroyAfterAnimation.h"
#include "../../Player/PlayerController.h"
#include "Core/AudioEngine.h"

IceSpell::IceSpell()
{
	spellStats->price = 15;
	spellStats->maxCooldown = 2;
	spellStats->manaCost = 2;
	spellStats->currentCooldown = spellStats->maxCooldown;
}

void IceSpell::UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir)
{
	std::vector<std::pair<glm::vec2, Tile*>> freezePos = GridSystem::Instance()->getNeighbours(0, playerPos);

	for (std::pair<glm::vec2, Tile*> neighbour : freezePos)
	{
		AudioEngine::Instance()->playSound("Sounds\\Ice.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
		GameObject* spell = SceneManager::Instance()->createGameObject("IceSpell", GridSystem::Instance()->getWorldPosition(neighbour.first));
		spell->getTransform()->setSize(glm::vec2(48, 48));
		const std::vector textureListFireball = ResourceManager::GetTexturesContaining("Fireball");
		IceSprite = spell->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0);
		IceSprite->setColor(glm::vec3(0, 1, 255));
		IceSprite->setSortingLayer(Renderer::getDefaultSortingLayer());
		IceSprite->setPivot(Pivot::Center);
		spell->addComponent<DestroyAfterAnimation>();
		spell->getTransform()->setRotation(90);

		TileHolder* affectedTile = GridSystem::Instance()->getTileHolder(0, neighbour.first);
		if (affectedTile != nullptr && affectedTile->gameObjectSatOnTile != nullptr && affectedTile->gameObjectSatOnTile->hasComponent(typeid(EnemyComponent)))
		{
			affectedTile->gameObjectSatOnTile->getComponent<EnemyComponent>()->roundsFreeze = turnsFreeze;
			affectedTile->gameObjectSatOnTile->getComponent<AnimatedSpriteRenderer>()->setColor(glm::vec3(0, 1, 255));
		}
	}
}
