#include "PlayerController.h"
#include "PlayerFSM.h"
#include "../TurnManager.h"

#include "../Items/Consumables/HealthPotion.h"
#include "../Items/Armour/LegendaryArmour.h"
#include "../Items/Weapons/LegendaryHammer.h"
#include "../Items/Weapons/RareSword.h"
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
	Griddy::Events::subscribe(this, &PlayerController::onKeyHold);
	
	AudioEngine::Instance()->loadSound("Sounds\\AirSlash.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Damage.wav", FMOD_3D);
}

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

	myInventory = playerPTR->addComponent<Inventory>(20);
	//armourStats = new ArmourStats();
	playerStats = new PlayerStats();

	
	playerStats->maxHealth = 10;
	playerStats->currentHealth = 10;
	playerStats->currentEXP = 0;
	playerStats->maxEXP = 100;
	playerStats->currentMana = 10;
	playerStats->maxMana = 10;
	playerStats->attack = 1;
	playerStats->spellPower = 1;
	playerStats->defence = 1;
	playerStats->critChance = 0.0f;
	playerStats->coinsHeld = 0;
	
	Light* light = playerPTR->addComponent<Light>();
	light->setFalloff({0.75f, 0.75f, 7.5f});
	light->setColor({1.0f, 1.0f, 1.0f, 1.0f});
	Renderer::Instance()->setCamera(cameraComponent);
}

void PlayerController::onKeyDown(const OnKeyDown* keyDown)
{
	if (keyDown->key == GLFW_KEY_P)
	{
		//Testing pathfinding
		glm::vec2 gridSize = GridSystem::Instance()->getGridSize();
		glm::vec2 start = playerPTR->getTransform()->getPosition();
		glm::vec2 goal = start + glm::vec2(0 * gridSize.x, -30 * gridSize.y);
		//PathfindingMachine::Instance()->FindPath(start, goal);
		bool sight = PathfindingMachine::Instance()->LineOfSight(start, goal);

		myInventory->add_item(new LegendaryHammer());
		myInventory->add_item(new RareSword());
		myInventory->add_item(new HealthPotion());

		LegendaryArmour* armour = new LegendaryArmour();
		myInventory->add_item(armour);
		myInventory->equip_item(armour->name());
	}
	
	//find the input and send it to the state machine
	const std::type_index eventType = typeid(OnKeyDown);
	Griddy::Events::invoke<BehaviourEvent>(playerFSM, new OnKeyDown(keyDown->key, keyDown->scancode), eventType);
}

void PlayerController::onKeyHold(const OnKeyRepeat* keyHold)
{
	std::type_index eventType = typeid(OnKeyRepeat);
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
}
