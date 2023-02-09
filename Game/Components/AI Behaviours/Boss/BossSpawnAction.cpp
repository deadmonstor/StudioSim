#include "BossSpawnAction.h"
#include "../../TurnManager.h"
#include "Core\Grid\PathfindingMachine.h"
#include "../NormalEnemyFSM.h"
#include "../../EnemyComponent.h"
#include "Core/Components/AnimatedSpriteRenderer.h"

BossSpawnAction::BossSpawnAction(std::vector<glm::vec2> spawnerPositionsArg) : spawnerPositions(spawnerPositionsArg)
{
	cooldown = 0;
}

void BossSpawnAction::Act()
{
	GridSystem* gridSystem = GridSystem::Instance();
	PathfindingMachine* pathfindingMachine = PathfindingMachine::Instance();
	//for each spawner
	for (auto pos : spawnerPositions)
	{
		glm::vec2 posWorldSpace = gridSystem->getWorldPosition(pos);

		//find closest available tile
		const TileHolder* targetTile = nullptr;
		int depth = 0;
		while (targetTile == nullptr)
		{
			const TileHolder* closestEmptyTile = PathfindingMachine::Instance()->FindClosestEmptyTile(posWorldSpace, depth, 0);

			if (closestEmptyTile != nullptr)
				targetTile = closestEmptyTile;

			depth++;
		}
		posWorldSpace = gridSystem->getWorldPosition(targetTile->position);
		//spawn enemy at said tile
		auto* enemy = SceneManager::Instance()->createGameObject("bossSpawn", posWorldSpace);
		enemy->getTransform()->setSize(glm::vec2(48, 48));

		const std::vector textureList = ResourceManager::GetTexturesContaining("crab");
		auto sprite = enemy->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(true);
		sprite->setPivot(Pivot::Center);

		StateMachine* fsm = enemy->addComponent<NormalEnemyFSM>();
		EnemyStats slimeStats = EnemyStats();
		slimeStats.attack = 3;
		slimeStats.critChance = 0.0f;
		slimeStats.maxHealth = 7;
		slimeStats.currentHealth = slimeStats.maxHealth;
		slimeStats.defence = 2;
		EnemyComponent component = EnemyComponent(fsm, slimeStats);
		enemy->addComponent<EnemyComponent>(component);

		GridSystem::Instance()->setSatOnTile(0, targetTile->position, enemy);
	}

	cooldown = 12;
	TurnManager::Instance()->endTurn();
}

bool BossSpawnAction::UpdateCooldown()
{
	if (cooldown > 0)
	{
		cooldown--;
		return false;
	}
	else
		return true;
}
