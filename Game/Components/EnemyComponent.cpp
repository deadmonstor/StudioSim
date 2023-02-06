#include "EnemyComponent.h"

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
#include "PickUp.h"
#include "Core/AudioEngine.h"

EnemyComponent::EnemyComponent()
{
	enemyFSM = nullptr;
	stats = EnemyStats();
	spriteName = "";
}

EnemyComponent::EnemyComponent(StateMachine* stateMachineArg, EnemyStats statsArg, std::string spriteNameArg)
{
	enemyFSM = stateMachineArg;
	stats = statsArg;
	spriteName = spriteNameArg;
	AudioEngine::Instance()->loadSound("Sounds\\Damage.wav", FMOD_3D);
}

void EnemyComponent::start()
{
	getOwner()->addComponent<Health>();
	getOwner()->addComponent<Camera>();
	const std::vector textureList = ResourceManager::GetTexturesContaining(spriteName);
	auto sprite = getOwner()->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(true);
	sprite->setPivot(Pivot::Center);

	TurnManager::Instance()->addToTurnQueue(getOwner());

	if (onStartTurnID == -1)
		Griddy::Events::subscribe(this, &EnemyComponent::onTurnChanged);
	
	Component::start();
}

void EnemyComponent::destroy()
{
	if (onStartTurnID != -1)
		Griddy::Events::unsubscribe(this, &EnemyComponent::onTurnChanged, onStartTurnID);
	
	int expGained = 5;
	PlayerController::Instance()->playerStats->currentEXP += expGained;
	PlayerController::Instance()->UpdateStats();


	DropLoot();
	Component::destroy();
}

void EnemyComponent::onTurnChanged(const onStartTurn* event)
{
	if (roundsFreeze == 0)
	{
		if (event->objectToStart == getOwner())
		{
			getOwner()->getComponent<AnimatedSpriteRenderer>()->setColor(glm::vec3(1, 1, 1));
			enemyFSM->Act();
		}
	}
	else
	{
		if (TurnManager::Instance()->isCurrentTurnObject(getOwner()))
		{
			roundsFreeze -= 1;
			TurnManager::Instance()->endTurn();
			LOG_INFO("EnemyComponent -> onTurnChanged -> TurnManager::Instance()->endTurn()");
		}
	}
	
}


void EnemyComponent::DropLoot()
{
	if (SceneManager::Instance()->isLoadingScene() || SceneManager::Instance()->isShuttingDown())
		return;
	
	std::string itemToSpawn = EnemyDropLootTable::Instance()->EnemyDropRollLoot();
	Texture m_ItemTexture;

	glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(getOwner()->getTransform()->getPosition());
	tileWorldSpace.x = tileWorldSpace.x / GridSystem::Instance()->getTileSize().x;
	tileWorldSpace.y = tileWorldSpace.y / GridSystem::Instance()->getTileSize().y;

	GameObject* Item = SceneManager::Instance()->createGameObject(itemToSpawn, tileWorldSpace);
	Item->getTransform()->setSize(glm::vec2(32, 32));
	int Amount = 1;
	
	if (itemToSpawn.contains("money"))
	{
		std::string delim = ",";
		std::string temp = itemToSpawn;
		std::string nameTemp;
		size_t pos = 0;
	
		while ((pos = temp.find(delim)) != std::string::npos)
		{	
			itemToSpawn = temp.substr(0, pos);
			temp.erase(0, pos + delim.length());
			Amount = std::stoi(temp);
			break;
		}
		switch (Amount)
		{
		case 1:
			m_ItemTexture = ResourceManager::LoadTexture("Sprites/Coins/coin0.png", itemToSpawn);
			break;
		case 2:
		case 3:
			m_ItemTexture = ResourceManager::LoadTexture("Sprites/Coins/coin1.png", itemToSpawn);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			m_ItemTexture = ResourceManager::LoadTexture("Sprites/Coins/coin2.png", itemToSpawn);
			break;
		case 16:
			m_ItemTexture = ResourceManager::LoadTexture("Sprites/Coins/coin4.png", itemToSpawn);
			break;
		default:
			m_ItemTexture = ResourceManager::LoadTexture("Sprites/Coins/coin3.png", itemToSpawn);
			break;
		}
		

	}
	else if (itemToSpawn.contains("health"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Potion0.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("mana"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Potion1.png", itemToSpawn);
	}
	else if (itemToSpawn.contains("exp"))
	{
		m_ItemTexture = ResourceManager::LoadTexture("Sprites/Weapons/Potion2.png", itemToSpawn);
	}


	Item->addComponent<SpriteComponent>();
	Item->getComponent<SpriteComponent>()->setPivot(Pivot::Center);
	Item->getComponent<SpriteComponent>()->setTexture(m_ItemTexture);
	Item->getComponent<SpriteComponent>()->setLit(false);
	Item->getComponent<SpriteComponent>()->setSortingLayer(Renderer::getSortingLayer("Background Grid"));
	Item->addComponent<PickUp>();
	Item->getComponent<PickUp>()->SetAmount(Amount);
}

