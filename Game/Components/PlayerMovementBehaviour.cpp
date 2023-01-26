#include "PlayerMovementBehaviour.h"
#include <Core/Grid/GridSystem.h>
#include <Util/Events/EngineEvents.h>
#include "PlayerAttackBehaviour.h"
#include "Core/Components/Transform.h"
#include "Core/AudioEngine.h"
#include <Core/Components/Health.h>

PlayerMovementBehaviour::PlayerMovementBehaviour()
{
	isInFSM = false; 
	map = CreateFunctionMap(); 
	origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
	AudioEngine::Instance()->loadSound("Sounds\\softStep.wav", FMOD_3D);
	attackBehaviour = new PlayerAttackBehaviour();
}

PlayerMovementBehaviour::PlayerMovementBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition())/GridSystem::Instance()->getTileSize();
	AudioEngine::Instance()->loadSound("Sounds\\softStep.wav", FMOD_3D);
	map = CreateFunctionMap();
	attackBehaviour = new PlayerAttackBehaviour();
}

void PlayerMovementBehaviour::Act()
{
	//move player
	
	TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, origPos + moveDir);
	GameObject* gameObjectOnTile = curTileHolder->gameObjectSatOnTile;
	glm::fvec2 tileSize = GridSystem::Instance()->getTileSize();
	const bool isWallTile = GridSystem::Instance()->isWallTile(origPos + moveDir);
		
	if (curTileHolder->tile != nullptr && !isWallTile)
	{
		if (gameObjectOnTile != nullptr && gameObjectOnTile->hasComponent(typeid(Health)))
		{
			attackBehaviour->AttackOnMovement(moveDir);
			canAttackWhileMoving = false;
		}
		else
		{
			PlayerController::Instance()->playerPTR->getTransform()->
				setPosition(tileSize * (origPos + moveDir));

			origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
		
			AudioEngine::Instance()->playSound("Sounds\\softStep.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
		}
	}
	canMove = false;
	attackBehaviour->canAttack = true;
}

void PlayerMovementBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);
	
	if (eventCasted->key == GLFW_KEY_Q)
	{
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerAttackBehaviour(true));
		return;
	}

	if (eventCasted->key == GLFW_KEY_W)
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
	}

	if (canMove)
	{
		Act();
	}
	moveDir = glm::fvec2(0, 0);
	//if tile is moveable
	
}

void PlayerMovementBehaviour::onKeyHoldResponse(Griddy::Event* event)
{
	OnKeyRepeat* eventCasted = static_cast<OnKeyRepeat*>(event);
	canMove = true;

	if (eventCasted->key == GLFW_KEY_W)
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
	}

	if (canMove && canAttackWhileMoving)
	{
		Act();
	}
	
	moveDir = glm::fvec2(0, 0);
	
	
}

void PlayerMovementBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	/*OnKeyUp* eventCasted = static_cast<OnKeyUp*>(event);
	
	if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x += 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x -= 1;
	}*/
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
