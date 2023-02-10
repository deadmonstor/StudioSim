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
#include "DestroyAfterAnimation.h"

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
		playDeath();
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

void EnemyComponent::playDeath()
{
	if (stats.deathEnemyList.empty())
	{
		return;
	}

	GameObject* death = SceneManager::Instance()->createGameObject("death", getOwner()->getTransform()->getPosition());
	AnimatedSpriteRenderer* oldSpriteRenderer = getOwner()->getComponent<AnimatedSpriteRenderer>();

	death->getTransform()->setSize(getOwner()->getTransform()->getScale());
	AnimatedSpriteRenderer* spriteRender = death->addComponent<AnimatedSpriteRenderer>(stats.deathEnemyList, abs(0.9f - (stats.deathEnemyList.size() / 13.0f)));
	spriteRender->setPivot(oldSpriteRenderer->getPivot());
	spriteRender->setColor(oldSpriteRenderer->getColor());
	spriteRender->setLit(false);

	death->addComponent<DestroyAfterAnimation>();
	
}


void EnemyComponent::DropLoot()
{
	if (SceneManager::Instance()->isLoadingScene() || SceneManager::Instance()->isShuttingDown())
		return;

	if (getOwner()->getName() == "bossSpawn")
		return;
	std::string itemToSpawn;
	Texture m_ItemTexture;
	int Amount = 1;
	if (getOwner()->getName() == "Crab" || getOwner()->getName() == "Reaper")
	{
		itemToSpawn = LootTable::Instance()->RollLoot();
		if (itemToSpawn.contains("Axe"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-Axe");
		}
		else if (itemToSpawn.contains("Sword"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-Sword");
		}
		else if (itemToSpawn.contains("Dagger"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-Dagger");
		}
		else if (itemToSpawn.contains("Hammer"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-Hammer");
		}
		else if (itemToSpawn.contains("common"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-BasicArmourChest");
		}
		else if (itemToSpawn.contains("rare"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-MidArmourChest");
		}
		else if (itemToSpawn.contains("legendary"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Inventory-TopArmourChest");
		}
	}
	else
	{
		itemToSpawn = EnemyDropLootTable::Instance()->EnemyDropRollLoot();
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
				m_ItemTexture = ResourceManager::GetTexture("coin0");
				break;
			case 2:
			case 3:
				m_ItemTexture = ResourceManager::GetTexture("coin1");
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				m_ItemTexture = ResourceManager::GetTexture("coin2");
				break;
			case 16:
				m_ItemTexture = ResourceManager::GetTexture("coin4");
				break;
			default:
				m_ItemTexture = ResourceManager::GetTexture("coin3");
				break;
			}
		}
		else if (itemToSpawn.contains("health"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Potion0");
		}
		else if (itemToSpawn.contains("mana"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Potion1");
		}
		else if (itemToSpawn.contains("exp"))
		{
			m_ItemTexture = ResourceManager::GetTexture("Potion2");
		}
	}

	//std::string itemToSpawn = EnemyDropLootTable::Instance()->EnemyDropRollLoot();

	glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(getOwner()->getTransform()->getPosition());
	tileWorldSpace.x = tileWorldSpace.x / GridSystem::Instance()->getTileSize().x;
	tileWorldSpace.y = tileWorldSpace.y / GridSystem::Instance()->getTileSize().y;

	GameObject* Item = SceneManager::Instance()->createGameObject(itemToSpawn, tileWorldSpace);
	Item->getTransform()->setSize(glm::vec2(32, 32));
	
	


	Item->addComponent<SpriteComponent>();
	Item->getComponent<SpriteComponent>()->setPivot(Pivot::Center);
	Item->getComponent<SpriteComponent>()->setTexture(m_ItemTexture);
	Item->getComponent<SpriteComponent>()->setLit(true);
	Item->getComponent<SpriteComponent>()->setSortingLayer(Renderer::getSortingLayer("Background Grid"));
	Item->addComponent<PickUp>();
	Item->getComponent<PickUp>()->SetAmount(Amount);
}

