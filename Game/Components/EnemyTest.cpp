#include "EnemyTest.h"

#include "TurnManager.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Health.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core/Grid/GridSystem.h"
#include "Util/Events/Events.h"
#include "Items/Stats.h"
#include "../Components/Player/PlayerController.h"
#include "../LootTable.h"
#include "Core/Components/Transform.h"

void EnemyTest::start()
{
	getOwner()->addComponent<Health>();
	getOwner()->addComponent<Camera>();
	enemyFSM = getOwner()->addComponent<NormalEnemyFSM>();
	
	const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
	auto sprite = getOwner()->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(true);
	sprite->setPivot(Pivot::Center);

	TurnManager::Instance()->addToTurnQueue(getOwner());

	if (onStartTurnID == -1)
		Griddy::Events::subscribe(this, &EnemyTest::onTurnChanged);
	
	Component::start();
}

void EnemyTest::destroy()
{
	if (onStartTurnID != -1)
		Griddy::Events::unsubscribe(this, &EnemyTest::onTurnChanged, onStartTurnID);
	
	int expGained = 5;
	PlayerController::Instance()->playerStats->currentEXP += expGained;
	PlayerController::Instance()->UpdateStats();


	std::string itemToSpawn = LootTable::Instance()->RollLoot();
	Texture m_ItemTexture;
	glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(getOwner()->getTransform()->getPosition());
	tileWorldSpace.x = tileWorldSpace.x / GridSystem::Instance()->getTileSize().x;
	tileWorldSpace.y = tileWorldSpace.y / GridSystem::Instance()->getTileSize().y;

	auto* Item = SceneManager::Instance()->createGameObject(itemToSpawn, tileWorldSpace);
	Item->getTransform()->setSize(glm::vec2(32, 32));
	m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Axe.png", itemToSpawn);
	Item->addComponent<SpriteComponent>();
	Item->getComponent<SpriteComponent>()->setPivot(Pivot::Center);
	Item->getComponent<SpriteComponent>()->setTexture(m_ItemTexture);
	Item->getComponent<SpriteComponent>()->setLit(false);
	Item->getComponent<SpriteComponent>()->setSortingLayer(Renderer::getSortingLayer("Background Grid"));
	Component::destroy();
}

void EnemyTest::onTurnChanged(const onStartTurn* event)
{
	if (event->objectToStart == getOwner())
	{
		enemyFSM->Act();
	}
}


/*
	Texture m_ItemTexture;
	curTileHolder->tile->setTexture(ResourceManager::GetTexture("chest_open_2"));
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(curTileHolder->position);


	auto* Item = SceneManager::Instance()->createGameObject(itemToSpawn, tileWorldSpace);
	Item->getTransform()->setSize(glm::vec2(32, 32));
	if (itemToSpawn.contains("Axe"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Axe.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("Sword"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Sword.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("Dagger"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Dagger.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("Hammer"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Hammer.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("common"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Armour/BasicArmourChest.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("rare"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Armour/MidArmourChest.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("legendary"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Armour/TopArmourChest.png", itemToSpawn);
	}

	Item->addComponent<SpriteComponent>();
	Item->getComponent<SpriteComponent>()->setPivot(Pivot::Center);
	Item->getComponent<SpriteComponent>()->setTexture(m_ItemTexture);
	Item->getComponent<SpriteComponent>()->setLit(false);
	Item->getComponent<SpriteComponent>()->setSortingLayer(Renderer::getSortingLayer("Background Grid"));
*/