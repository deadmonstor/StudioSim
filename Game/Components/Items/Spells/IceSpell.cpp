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
	spellStats->currentCooldown = 0;
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

		const TileHolder* affectedTile = GridSystem::Instance()->getTileHolder(0, neighbour.first);
		if (affectedTile != nullptr && affectedTile->gameObjectSatOnTile != nullptr && affectedTile->gameObjectSatOnTile->hasComponent(typeid(EnemyComponent)))
		{
			GameObject* enemy = affectedTile->gameObjectSatOnTile;
			const glm::vec3 color = glm::vec3(0, 0, 1);
			
			enemy->getComponent<EnemyComponent>()->roundsFreeze = turnsFreeze;
			enemy->getComponent<AnimatedSpriteRenderer>()->setColor(color);

			PlayerController::Instance()->hitmarkers->addHitmarker(
			"STUNNED",
			1.0,
			enemy->getTransform()->getPosition(),
			color);
		}
	}
}
