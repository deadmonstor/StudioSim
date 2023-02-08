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
#include "../ScoreSystem.h"
#include "../Components/Items/Spells/PoisonSpell.h"

EnemyComponent::EnemyComponent()
{
	enemyFSM = nullptr;
	stats = EnemyStats();
}

EnemyComponent::EnemyComponent(StateMachine* stateMachineArg, EnemyStats statsArg)
{
	enemyFSM = stateMachineArg;
	stats = statsArg;

	if (!ResourceManager::HasSound("Sounds\\Damage.wav"))
		AudioEngine::Instance()->loadSound("Sounds\\Damage.wav", FMOD_3D);
}

void EnemyComponent::start()
{
	Health* healthComponent = getOwner()->addComponent<Health>(stats.maxHealth);
	getOwner()->addComponent<Camera>();

	TurnManager::Instance()->addToTurnQueue(getOwner());

	if (onStartTurnID == -1)
		onStartTurnID = Griddy::Events::subscribe(this, &EnemyComponent::onTurnChanged);
	
	Component::start();
}

void EnemyComponent::destroy()
{
	if (onStartTurnID != -1)
		Griddy::Events::unsubscribe(this, &EnemyComponent::onTurnChanged, onStartTurnID);
	
	if (getOwner()->getComponent<Health>()->getHealth() <= 0)
	{
		int expGained = 5;
		PlayerController::Instance()->playerStats->currentEXP += expGained;
		PlayerController::Instance()->UpdateStats();
		ScoreSystem::Instance()->addEnemiesKilled(1);
	}

	DropLoot();
	Component::destroy();
}

void EnemyComponent::onTurnChanged(const onStartTurn* event)
{
	if (roundsFreeze <= 0)
	{
		if (roundsPoisoned <= 0)
		{
			if (event->objectToStart == getOwner())
			{
				getOwner()->getComponent<AnimatedSpriteRenderer>()->setColor(glm::vec3(1, 1, 1));
				if (enemyFSM != nullptr)
					enemyFSM->Act();
				else
					LOG_ERROR("EnemyComponent -> onTurnChanged -> enemyFSM is nullptr");
			}
		}
		else
		{

			if (event->objectToStart == getOwner())
			{
				roundsPoisoned -= 1;
				PoisonSpell* poison = new PoisonSpell();
				int spellDMG = poison->spellStats->damagePerTurn;
				float currentHealth = getOwner()->getComponent<Health>()->getHealth();
				int newHealth = currentHealth -= spellDMG;
				getOwner()->getComponent<Health>()->setHealth(newHealth);
				if (getOwner()->isBeingDeleted())
				{
					GridSystem::Instance()->resetSatOnTile(0, GridSystem::Instance()->getTilePosition(getOwner()->getTransform()->getPosition()));
					return;
				}

				LOG_INFO("EnemyComponent -> onTurnChanged -> TurnManager::Instance()->endTurn() -> " + std::to_string(roundsPoisoned));
				if (enemyFSM != nullptr)
					enemyFSM->Act();
				else
					LOG_ERROR("EnemyComponent -> onTurnChanged -> enemyFSM is nullptr");
			}
		}
	}
	else
	{
		if (event->objectToStart == getOwner())
		{
			roundsFreeze -= 1;
			LOG_INFO("EnemyComponent -> onTurnChanged -> TurnManager::Instance()->endTurn() -> " + std::to_string(roundsFreeze));
			TurnManager::Instance()->endTurn();
		}
	}
	
}


void EnemyComponent::DropLoot()
{
	if (SceneManager::Instance()->isLoadingScene() || SceneManager::Instance()->isShuttingDown())
		return;

	if (getOwner()->getName() == "bossSpawn")
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

