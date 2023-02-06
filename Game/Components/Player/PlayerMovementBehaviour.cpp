#include "PlayerMovementBehaviour.h"
#include <Core/Grid/GridSystem.h>
#include <Util/Events/EngineEvents.h>
#include "PlayerAttackBehaviour.h"
#include "PlayerSpellBehaviour.h"
#include "../EnemyComponent.h"
#include "../TurnManager.h"
#include "Core/AudioEngine.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"

PlayerMovementBehaviour::PlayerMovementBehaviour()
{
	isInFSM = false; 
	map = CreateFunctionMap(); 
	origPos = GridSystem::Instance()->getTilePosition(PlayerController::Instance()->playerPTR->getTransform()->getPosition());
	
	if (!ResourceManager::HasSound("Sounds\\softStep.wav"))
		AudioEngine::Instance()->loadSound("Sounds\\softStep.wav", FMOD_3D);
	
	attackBehaviour = new PlayerAttackBehaviour();
}

PlayerMovementBehaviour::PlayerMovementBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	origPos = GridSystem::Instance()->getTilePosition(PlayerController::Instance()->playerPTR->getTransform()->getPosition());

	if (!ResourceManager::HasSound("Sounds\\softStep.wav"))
		AudioEngine::Instance()->loadSound("Sounds\\softStep.wav", FMOD_3D);
	
	map = CreateFunctionMap();
	attackBehaviour = new PlayerAttackBehaviour();
}

void PlayerMovementBehaviour::Act()
{
	GridSystem* gridSystem = GridSystem::Instance();
	TileHolder* curTileHolder = gridSystem->getTileHolder(0, origPos + moveDir);

	
	if (curTileHolder == nullptr)
		return;
	
	GameObject* gameObjectOnTile = curTileHolder->gameObjectSatOnTile;
	glm::fvec2 tileSize = gridSystem->getTileSize();
	const bool isWallTile = gridSystem->isWallTile(origPos + moveDir);
		
	if (curTileHolder->tile != nullptr && (!isWallTile || TurnManager::gNoclipMode))
	{
		
#if _DEBUG
		if (TurnManager::gNoclipMode)
			PlayerController::Instance()->playerPTR->getComponent<AnimatedSpriteRenderer>()->setColor({ 0.3, 0.3 , 0.3 });
		else
			PlayerController::Instance()->playerPTR->getComponent<AnimatedSpriteRenderer>()->setColor({ 1, 1, 1 });
#endif
		
		if (gameObjectOnTile != nullptr && gameObjectOnTile->hasComponent(typeid(EnemyComponent)))
		{
			attackBehaviour->AttackOnMovement(moveDir);
			canAttackWhileMoving = false;
		}
		else
		{
			PlayerController::Instance()->playerPTR->getTransform()->
				setPosition(GridSystem::Instance()->getWorldPosition(origPos + moveDir));

			//Set grid system "satOnTile" values
			gridSystem->resetSatOnTile(0, origPos);
			gridSystem->setSatOnTile(0, gridSystem->getTilePosition(PlayerController::Instance()->playerPTR->getTransform()->getPosition()),
				PlayerController::Instance()->playerPTR);


			for (int i = 0; i < gridSystem->getOrderMap().size(); i++)
			{
				TileHolder* tileHolder = gridSystem->getTileHolder(i, origPos + moveDir);

				if (tileHolder->tile->canInteractWith())
					tileHolder->tile->onInteractedWith(tileHolder);
			}

			origPos = gridSystem->getTilePosition(PlayerController::Instance()->playerPTR->getTransform()->getPosition());
		
			AudioEngine::Instance()->playSound("Sounds\\softStep.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
			
			
			if (TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
			{
				TurnManager::Instance()->endTurn();
				LOG_INFO("PlayerMovementBehaviour::Act() -> TurnManager::Instance()->endTurn()");
			}
		}
	}
	
	canMove = false;
	attackBehaviour->canAttack = true;
	moveDir = glm::fvec2(0, 0);
}

void PlayerMovementBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);
	
	if (eventCasted->key == GLFW_KEY_Q)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerAttackBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerAttackBehaviour(true));
		return;
	}

	if (eventCasted->key == GLFW_KEY_E)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerSpellBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerSpellBehaviour(true));
		return;
	}

	if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y = 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y = -1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x = -1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x = 1;
	}

	if (canMove && moveDir != glm::fvec2(0, 0))
	{
		if (TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
		{
			PlayerController::Instance()->ReduceSpellCooldown();
			Act();
		}
	}
	
	moveDir = glm::fvec2(0, 0);
}

void PlayerMovementBehaviour::onKeyHoldResponse(Griddy::Event* event)
{
	OnKeyRepeat* eventCasted = static_cast<OnKeyRepeat*>(event);
	canMove = true;

	if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y = 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y = -1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x = -1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x = 1;
	}

	if (canMove && canAttackWhileMoving)
	{
		if (TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
		{
			Act();
		}
	}
	
	moveDir = glm::fvec2(0, 0);
}

void PlayerMovementBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	canMove = true;
	attackBehaviour->canAttack = true;
	canAttackWhileMoving = true;
}

FunctionMap PlayerMovementBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerMovementBehaviour*>(pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerMovementBehaviour*>(pointer)->onKeyUpResponse(event);
	};
	map[typeid(OnKeyRepeat)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerMovementBehaviour*>(pointer)->onKeyHoldResponse(event);
	};

	return map;
	
}

//void PlayerMovementBehaviour::EventResponse(const BehaviourEvent* event)
//{
//	//Read input and find direction
//	//check tiles available to move
//	//call act at the end
//	OnKeyDown* eventCasted = (OnKeyDown*)event;
//
	/*if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x += 1;
	}*/
//}
