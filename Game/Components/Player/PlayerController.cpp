#include "PlayerFSM.h"
#include "../TurnManager.h"

#include "../Items/Consumables/HealthPotion.h"
#include "../Items/Armour/LegendaryArmour.h"
#include "../Items/Weapons/LegendaryHammer.h"
#include "../Items/Weapons/RareSword.h"
#include "../Items/Spells/FireBallSpell.h"
#include "../Items/Spells/IceSpell.h"
#include "../Items/Spells/PoisonSpell.h"
#include "Core/AudioEngine.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Grid/PathfindingMachine.h"
#include "Core/Renderer/ResourceManager.h"

PlayerController::PlayerController()
{
	Griddy::Events::subscribe(this, &PlayerController::onKeyDown);
	Griddy::Events::subscribe(this, &PlayerController::onKeyUp);
	Griddy::Events::subscribe(this, &PlayerController::onEngineRender);
	Griddy::Events::subscribe(this, &PlayerController::onKeyHold);
}

int lastHealth = 0;
void PlayerController::createPlayer()
{
	const glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 30, 20 } * tileSize);
	playerPTR->getTransform()->setSize(glm::vec2{ 32,32 });
	TurnManager::Instance()->addToTurnQueue(playerPTR);

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
	playerSprite->setColor(glm::vec3(1, 1, 1));
	playerSprite->setLit(false);
	playerSprite->setPivot(Pivot::Center);

	playerFSM = playerPTR->addComponent<PlayerFSM>();
	cameraComponent = playerPTR->addComponent<Camera>();
	hitmarkers = playerPTR->addComponent<Hitmarkers>();
	bool isTutorial = SceneManager::Instance()->getScene()->name == "tutorial";

	if (playerStats == nullptr ||
		SceneManager::Instance()->getScene()->name == "level1" ||
		isTutorial)
	{
		if (playerStats != nullptr && playerStats->myInventory != nullptr)
			delete playerStats->myInventory;
		
		delete playerStats;
		
		playerStats = new PlayerStats();
		playerStats->maxHealth = 25;
		playerStats->currentHealth = 25;
		lastHealth = 25;
		playerStats->currentEXP = 0;
		playerStats->maxEXP = 100;
		playerStats->currentMana = 10;
		playerStats->maxMana = 10;
		playerStats->attack = 1;
		playerStats->spellPower = 1;
		playerStats->defence = 1;
		playerStats->critChance = 0.0f;
		playerStats->coinsHeld = 0;
		playerStats->level = 1;
		
		playerStats->myInventory = new Inventory(20);
		if (isTutorial)
		{
			for(auto func : Inventory::getItemByName | std::views::values)
			{
				playerStats->myInventory->add_item(func());
			}
		}
	}
	
	myInventory = playerStats->myInventory;
	Light* light = playerPTR->addComponent<Light>();
	light->setFalloff({0.75f, 0.75f, 7.5f});
	light->setColor({1.0f, 1.0f, 1.0f, 1.0f});
	Renderer::Instance()->setCamera(cameraComponent);
}

void PlayerController::onEngineRender(const OnEngineRender* render)
{
	if (playerPTR == nullptr || playerPTR->isBeingDeleted()) return;
	
	static SpriteComponent* spriteComponent = new SpriteComponent();
	spriteComponent->setSortingOrder(1);
	spriteComponent->setTexture(ResourceManager::GetTexture("whitetexture"));
	spriteComponent->setLit(false);
	spriteComponent->setColor(TurnManager::Instance()->isCurrentTurnObject(playerPTR) ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0));
	
	const glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	const float tileWidth = tileSize.x;
	const float tileHeight = tileSize.y;

	glm::vec2 pos = playerPTR->getTransform()->getPosition();
	pos = GridSystem::Instance()->getTilePosition(pos);
	pos = GridSystem::Instance()->getWorldPosition(pos);
	
	Renderer::Instance()->renderSprite(spriteComponent,
											   pos - glm::vec2{ tileWidth / 2, tileHeight / 2 },
											   {tileWidth, tileHeight},
											   0);
}


void PlayerController::onKeyDown(const OnKeyDown* keyDown)
{
#ifdef _DEBUG
	if (keyDown->key == GLFW_KEY_P && myInventory != nullptr)
	{
		for(auto func : Inventory::getItemByName | std::views::values)
		{
			PlayerController::Instance()->myInventory->add_item(func());
		}
	}
#endif
	
	//find the input and send it to the state machine
	const std::type_index eventType = typeid(OnKeyDown);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyDown(keyDown->key, keyDown->scancode), eventType);
}

void PlayerController::onKeyHold(const OnKeyRepeat* keyHold)
{
	const std::type_index eventType = typeid(OnKeyRepeat);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyRepeat(keyHold->key, keyHold->scancode), eventType);
}

void PlayerController::onKeyUp(const OnKeyUp* keyUp)
{
	const std::type_index eventType = typeid(OnKeyUp);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyUp(keyUp->key, keyUp->scancode), eventType);
}

void PlayerController::UpdateStats()
{
	if (playerStats->currentHealth <= 0)
	{
		SceneManager::Instance()->changeScene("defeatScreen");
	}

	// get difference
	const int difference = playerStats->currentHealth - lastHealth;
	lastHealth = playerStats->currentHealth;

	if (Item* equippedItemp = myInventory->getFirstItemWithEquipSlot(EquipSlot::ARMOUR))
	{

	}

	if (difference != 0)
		hitmarkers->addHitmarker(std::to_string(difference), 1, playerPTR->getTransform()->getPosition(), {1, 1, 1}, 25);

	while (playerStats->currentEXP >= 100)
	{
		playerStats->level++;
		playerStats->currentEXP = playerStats->currentEXP - 100;
		playerStats->maxHealth += 5;
		playerStats->maxMana += 5;
		playerStats->currentHealth = playerStats->maxHealth;
		playerStats->currentMana = playerStats->maxMana;

		lastHealth = playerStats->currentHealth;
	}

	if (SceneManager::Instance()->getScene()->name == "tutorial")
	{
		// GODMODE + Other stuff
		playerStats->currentHealth = playerStats->maxHealth;
		playerStats->currentMana = playerStats->maxMana;
	}
}

void PlayerController::AddCoins(int Amount)
{
	playerStats->coinsHeld += Amount;
}

void PlayerController::ReduceSpellCooldown()
{
	if (Item* spell = PlayerController::Instance()->myInventory->getFirstItemWithEquipSlot(EquipSlot::SPELL); spell != nullptr)
	{
		const auto spellCasted = dynamic_cast<SpellItem*>(spell);
		if (spellCasted->spellStats->currentCooldown != spellCasted->spellStats->maxCooldown)
		{
			spellCasted->spellStats->currentCooldown += 1;
		}
	}
}
