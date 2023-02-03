#include "PlayerAttackBehaviour.h"
#include <Core/Components/Health.h>
#include "PlayerMovementBehaviour.h"
#include "PlayerSpellBehaviour.h"
#include "../DestroyAfterAnimation.h"
#include "../EnemyComponent.h"
#include "../Flash.h"
#include "../TurnManager.h"
#include "../../System/Inventory.h"
#include "../Items/Weapons/Weapon.h"
#include "Core/AudioEngine.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"

PlayerAttackBehaviour::PlayerAttackBehaviour()
{
	isInFSM = false; 
	map = CreateFunctionMap();
}

PlayerAttackBehaviour::PlayerAttackBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void PlayerAttackBehaviour::AttackOnMovement(glm::fvec2 dir)
{
	attackDir = dir;
	if (canAttack && !willFlashOnce)
	{
		if (TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
		{
			Act();
		}
	}
	
	attackDir = glm::fvec2(0, 0);
}

void PlayerAttackBehaviour::Act()
{
	if (willFlashOnce) return;
	
	currentPlayerPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, currentPlayerPos + attackDir);

	if (curTileHolder->tile != nullptr)
	{
		if (Item* weapon = PlayerController::Instance()->myInventory->getFirstItemWithEquipSlot(EquipSlot::WEAPON); weapon != nullptr)
		{
			const auto weaponCasted = dynamic_cast<WeaponItem*>(weapon);
			weaponCasted->Attack(currentPlayerPos, attackDir);
		}
		else
		{
			// TODO: This is the same as the "bad" dagger attack, very low damage
			if (const bool isWallTile = GridSystem::Instance()->isWallTile(currentPlayerPos + attackDir); !isWallTile)
			{
				createSlashGameObject(currentPlayerPos + attackDir);
			}
		}
	}
	
	if (TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR) && !willFlashOnce)
	{
		/*PlayerController::Instance()->ReduceSpellCooldown();*/
		TurnManager::Instance()->endTurn();
	}
	canAttack = false;
}

void PlayerAttackBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);

	if (eventCasted->key == GLFW_KEY_Q)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerMovementBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerMovementBehaviour(true));
		return;
	}

	if (eventCasted->key == GLFW_KEY_E)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerSpellBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerSpellBehaviour(true));
	}

	if (eventCasted->key == GLFW_KEY_W)
	{
		attackDir.y = 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		attackDir.y = -1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		attackDir.x = -1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		attackDir.x = 1;
	}

	if (canAttack && (eventCasted->key == GLFW_KEY_W || eventCasted->key == GLFW_KEY_S ||
		eventCasted->key == GLFW_KEY_A || eventCasted->key == GLFW_KEY_D))
	{
		if (TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
		{
			Act();
			PlayerController::Instance()->ReduceSpellCooldown();
		}
	}
	
	attackDir = glm::fvec2(0, 0);
}

void PlayerAttackBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	canAttack = true;
}

void PlayerAttackBehaviour::createSlashGameObject(const glm::fvec2 pos)
{
	const TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, pos);
	GameObject* gameObject = curTileHolder->gameObjectSatOnTile;
	
	if (gameObject != nullptr)
	{
		if (gameObject->hasComponent(typeid(Health)))
		{
			if (!willFlashOnce && !TurnManager::gNoclipMode)
			{
				Flash::createFlash(gameObject, gameObject->getComponent<AnimatedSpriteRenderer>(), {1, 0, 0}, 5,
				[this, gameObject, pos]
				{
					TurnManager::Instance()->endTurn();

					auto* health = gameObject->getComponent<Health>();
					// TODO: Change this
					health->setHealth(health->getHealth() - 1);

					// TODO: This is probably shitty 
					if (gameObject->isBeingDeleted())
						GridSystem::Instance()->resetSatOnTile(0, pos);

					willFlashOnce = false;
				});
				
				willFlashOnce = true;
			}
			else
			{
				auto* health = gameObject->getComponent<Health>();
				health->setHealth(health->getHealth() - 50);

				// TODO: This is probably shitty 
				if (gameObject->isBeingDeleted())
					GridSystem::Instance()->resetSatOnTile(0, pos);
			}
			
			AudioEngine::Instance()->playSound("Sounds\\Damage.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
		}
	}

	// get world position from grid position
	const glm::fvec2 worldPos = GridSystem::Instance()->getWorldPosition(pos);
	GameObject* slash = SceneManager::Instance()->createGameObject("Slash", worldPos);
	slash->getTransform()->setSize(glm::vec2(48, 48));
	AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
	slashSprite->setPivot(Pivot::Center);
	slash->addComponent<DestroyAfterAnimation>();
	
	AudioEngine::Instance()->playSound("Sounds\\AirSlash.wav", false, 0.3f, 0, 0, AudioType::SoundEffect);
}

FunctionMap PlayerAttackBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerAttackBehaviour*>(pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerAttackBehaviour*>(pointer)->onKeyUpResponse(event);
	};

	return map;
}
