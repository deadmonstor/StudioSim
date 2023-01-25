#include "PlayerController.h"
#include "PlayerFSM.h"
#include "../System/Inventory.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"

PlayerController::PlayerController()
{
}

void PlayerController::createPlayer()
{
	const glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
	playerPTR = SceneManager::Instance()->createGameObject("Player", glm::vec2{ 30, 20 } * tileSize);
	playerPTR->getTransform()->setSize(glm::vec2{ 32,32 });

	const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
	playerSprite = playerPTR->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
	playerSprite->setColor(glm::vec3(1, 1, 1));
	playerSprite->setLit(false);
	playerSprite->setPivot(Pivot::Center);

	playerFSM = playerPTR->addComponent<PlayerFSM>();
	cameraComponent = playerPTR->addComponent<Camera>();
	myInventory = playerPTR->addComponent<Inventory>(20);
	Light* light = playerPTR->addComponent<Light>();
	light->setFalloff({0.75f, 0.75f, 10.0f});
	Renderer::Instance()->setCamera(cameraComponent);
}

void PlayerController::onKeyDown(const OnKeyDown* keyDown)
{
	//DEBUG
	if (keyDown->key == GLFW_KEY_F11)
	{
		Item sword;
		sword.name = "Bandit sword";
		sword.type = "Weapon";
		sword.itemDescription = "A common sword";
		sword.equipSlot = "Hand";
		sword.isEquipped = false;
		sword.atk = 10;
		sword.crit = 2;
		
		myInventory->add_item(sword);

		Item armour;
		armour.name = "Bandit armor";
		armour.type = "Armour";
		armour.equipSlot = "Chest";
		armour.isEquipped = false;
		armour.def = 15;
		
		myInventory->add_item(armour);

		Item spell;
		spell.name = "Fireball";
		spell.type = "Spell";
		spell.equipSlot = "Spells";
		spell.isEquipped = false;
		spell.spellAtk = 20;
		spell.manaCost = 10;
		spell.coolDown = 4; //Secods
		spell.effectDuration = 3; //Seconds
		
		myInventory->add_item(spell);
		myInventory->equip_item("Bandit sword");
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
