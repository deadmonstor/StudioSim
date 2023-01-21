#include "PlayerMovementBehaviour.h"
#include <Util/Events/EngineEvents.h>
#include <Core/Grid/GridSystem.h>
#include "PlayerAttackBehaviour.h"

PlayerMovementBehaviour::PlayerMovementBehaviour()
{
	isInFSM = false; 
	map = CreateFunctionMap(); 
	origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
}

PlayerMovementBehaviour::PlayerMovementBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition())/GridSystem::Instance()->getTileSize();
	map = CreateFunctionMap();
}

void PlayerMovementBehaviour::Act()
{
	//move player
	if (canMove)
	{
		TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, origPos + moveDir);
		glm::fvec2 tileSize = GridSystem::Instance()->getTileSize();


		if (curTileHolder->tile != nullptr && !curTileHolder->isWall)
		{
			PlayerController::Instance()->playerPTR->getTransform()->
				setPosition(tileSize * (origPos + moveDir));

			origPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
		}

		canMove = false;
	}
	
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
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x += 1;
		Act();
	}

	
	//if tile is moveable
	
}

void PlayerMovementBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	OnKeyUp* eventCasted = static_cast<OnKeyUp*>(event);
	
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
	}

	canMove = true;
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
