#include "PlayerMovementBehaviour.h"
#include <Util/Events/EngineEvents.h>
#include <Core/Grid/GridSystem.h>

void PlayerMovementBehaviour::Act()
{
	//move player
	GridHolder* curTileHolder = GridSystem::Instance()->getGridHolder(0, origPos + moveDir);
	glm::fvec2 gridSize = GridSystem::Instance()->getTileSize();

	if (curTileHolder->tile != nullptr && !curTileHolder->isWall)
	{
		PlayerController::Instance()->playerPTR->getTransform()->
			setPosition(gridSize * (origPos + moveDir));

		origPos += moveDir;
	}
}

void PlayerMovementBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);

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

	//if tile is moveable
	Act();
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
